#include "lvgl.h"
#include "Gui_Task.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "HomePage.h"
#include "setup.h"
#include "lv_port_indev.h"   // extern lv_group_t *encoder_group; 以及 lv_port_indev_init()
#include "numedit.h"
#include "SET_Page.h"
#include "lv_port_indev.h"
#include "main.h"
#include "power_ctrl.h"
#include "ADC_Task.h"
extern lv_ui guider_ui;  /* 你的全局 ui */

/* ========= 工具：停止冒泡并返回 true ========= */
extern inline bool stop_and_true(lv_event_t *e){
    lv_event_stop_bubbling(e);
    return true;
}

static uint32_t real_value_ms;
static inline void ui_click_beep(uint32_t key){ 
    if(!s2_beep_state) return;      // 用户关闭蜂鸣器
    if(s_click_mute)   return;      // 锁屏期间静音
    switch(key){
    case LV_KEY_ENTER:
    case LV_KEY_ENCODER:
    case LV_KEY_ENCODER_LONGP:
    case LV_KEY_MENU:
    case LV_KEY_LOCK:
    case LV_KEY_LOCK_LONGP:
    case LV_KEY_ESC:
    case LV_KEY_V:
    case LV_KEY_V_LONGP:
    case LV_KEY_A:
    case LV_KEY_A_LONGP:
    case LV_KEY_M1:
    case LV_KEY_M2:
    case LV_KEY_M3:
    case LV_KEY_M1_LONGP:
    case LV_KEY_M2_LONGP:
    case LV_KEY_M3_LONGP:
    case LV_KEY_OUTPUT:
    case LV_KEY_OUTPUT_LONGP:
    case LV_KEY_LEFT:
    case LV_KEY_LEFT_LONGP:
    case LV_KEY_RIGHT:
    case LV_KEY_RIGHT_LONGP:
        BEEP_OK();
        break;
    default: break; // 旋钮上下不响
    }
}



/* ===== OUTPUT 键逻辑：只切换输出，设定值不变 ===== */
 bool OUT_ONOFF_led_on = false;
static inline void ui_onoff_update(bool on)
{
    lv_label_set_text(guider_ui.screen_label_ON_OFF, on ? "ON" : "OFF");
    lv_obj_set_style_text_color(
        guider_ui.screen_label_ON_OFF,
        on ? lv_color_hex(0xddff00) : lv_color_hex(0x858585),0);
  
    lv_obj_set_style_text_opa(
    guider_ui.screen_label_ON_OFF ,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealVal_V,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealVal_A,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealVal_W,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealUnit_V,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealUnit_A,
    on ? LV_OPA_COVER : LV_OPA_60,  // 100% vs 50%
    0
    );
    lv_obj_set_style_text_opa(
    guider_ui.screen_RealUnit_W,
    on ? LV_OPA_COVER : LV_OPA_60, // 100% vs 50%
    0); 

            
            
}







extern bool handle_OUT_ONOFF_hotkey(uint32_t key, lv_event_t *e)
{
    //只在homepage处调用 其余界面不调用
    if(g_nav.current != PAGE_HOME) return false;
    if(key != LV_KEY_OUTPUT && key != LV_KEY_OUTPUT_LONGP) return false;
    OUT_ONOFF_led_on = !OUT_ONOFF_led_on; 
    // 同步电源控制模块的“输出状态”
    power_set_output(OUT_ONOFF_led_on);

    if(OUT_ONOFF_led_on){
        HAL_GPIO_WritePin(OUT_ONOFF_GPIO_Port, OUT_ONOFF_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_ONOFF_GPIO_Port, LED_ONOFF_Pin, GPIO_PIN_RESET);     
        // 可留可去：同步一次目标（不写PWM）
        power_apply_voltage_from_label();      
       ui_onoff_update(OUT_ONOFF_led_on);  
    }else{
        HAL_GPIO_WritePin(OUT_ONOFF_GPIO_Port, OUT_ONOFF_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_ONOFF_GPIO_Port, LED_ONOFF_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_CC_GPIO_Port, LED_CC_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_CV_GPIO_Port, LED_CV_Pin, GPIO_PIN_RESET); 
        lv_label_set_text(guider_ui.screen_RealVal_V, "00.00");
        lv_label_set_text(guider_ui.screen_RealVal_A, "0.000");
        lv_label_set_text(guider_ui.screen_RealVal_W, "00.00");        
        // 别再直接清 PWM，交给 power_tick_20ms() 平滑到 0
      ui_onoff_update(OUT_ONOFF_led_on); 
    }
    
   
    return stop_and_true(e);
}



ui_nav_t g_nav = {0};
typedef struct {
    numedit_t *ed;
    uint32_t   trig;   // 进入/退出该编辑器的触发键
} EditBind;

static EditBind s_bind[] = {
    { &g_outV,      LV_KEY_V        },   // 设置 V
    { &g_outA,      LV_KEY_A        },   // 设置 A
    { &g_out_prt_V, LV_KEY_V_LONGP  },   // 保护 V
    { &g_out_prt_A, LV_KEY_A_LONGP  },   // 保护 A
};
#define BIND_N (sizeof(s_bind)/sizeof(s_bind[0]))

static int find_active_idx(void){
    for (int i=0;i<BIND_N;i++) if (s_bind[i].ed && s_bind[i].ed->editing) return i;
    return -1;
}
static int find_idx_by_key(uint32_t key){
    for (int i=0;i<BIND_N;i++) if (s_bind[i].trig == key) return i;
    return -1;
}



/**********************************************/
/* ——— 页面显示隐藏 ——— */
static inline void hide_all_pages(void)
{
    if(guider_ui.screen_cont_Set)  lv_obj_add_flag(guider_ui.screen_cont_Set,  LV_OBJ_FLAG_HIDDEN);
    if(guider_ui.screen_cont_Out)  lv_obj_add_flag(guider_ui.screen_cont_Out,  LV_OBJ_FLAG_HIDDEN);
    if(guider_ui.screen_Msg_lock)  lv_obj_add_flag(guider_ui.screen_Msg_lock,  LV_OBJ_FLAG_HIDDEN);
    if(guider_ui.screen_2_SetupContainer)  lv_obj_add_flag(guider_ui.screen_2_SetupContainer,  LV_OBJ_FLAG_HIDDEN);
    if(guider_ui.screen_2_cont_1)  lv_obj_add_flag(guider_ui.screen_2_cont_1,  LV_OBJ_FLAG_HIDDEN);

}
//绑定容器：重要关键点
void pages_build(lv_ui *ui)
{
    g_nav.content = ui->screen_1_body;

    /* Home 页 */
    setup_scr_screen(ui);
    if(ui->screen_cont_Set) lv_obj_set_parent(ui->screen_cont_Set, g_nav.content);
    if(ui->screen_cont_Out) lv_obj_set_parent(ui->screen_cont_Out, g_nav.content);
    if(ui->screen_Msg_lock) lv_obj_set_parent(ui->screen_Msg_lock, g_nav.content);
    /* Setup 页 */
    setup_scr_screen_2(ui);
    if(ui->screen_2_SetupContainer) lv_obj_set_parent(ui->screen_2_SetupContainer, g_nav.content);
    if(ui->screen_2_cont_1) lv_obj_set_parent(ui->screen_2_cont_1, g_nav.content);
    if(ui->screen_2_InterfaceIfoContainer) lv_obj_set_parent(ui->screen_2_InterfaceIfoContainer, g_nav.content);  
    if(ui->screen_2_AboutIfoContainer) lv_obj_set_parent(ui->screen_2_AboutIfoContainer, g_nav.content);  
    if(ui->screen_2_cont_outStateIfoContainer) lv_obj_set_parent(ui->screen_2_cont_outStateIfoContainer, g_nav.content);   
    /* 这里初始化 screen_2 的按钮列表 */
    SET_Page_init(ui);
    hide_all_pages();
}

void show_page(page_id_t id)
{
    if(id >= PAGE_MAX) return;
    hide_all_pages();
    switch(id){
    case PAGE_HOME:
        /* 显示首页容器 */
        if(guider_ui.screen_cont_Set) lv_obj_clear_flag(guider_ui.screen_cont_Set,  LV_OBJ_FLAG_HIDDEN);
        if(guider_ui.screen_cont_Out) lv_obj_clear_flag(guider_ui.screen_cont_Out,  LV_OBJ_FLAG_HIDDEN);

        /* 关闭 screen_2 导航，并把 focuser 加回组、聚焦 */
        SET_Page_leave(g_nav.group, NULL);
        if (g_nav.group && g_nav.focuser) {
            lv_obj_add_flag(g_nav.focuser, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_group_add_obj(g_nav.group, g_nav.focuser);
            lv_group_focus_obj(g_nav.focuser);
        }
        break;
    case PAGE_SETUP: /* 界面2 */
        /* 显示界面2容器 */
        if(guider_ui.screen_2_cont_1) lv_obj_clear_flag(guider_ui.screen_2_cont_1,  LV_OBJ_FLAG_HIDDEN);
        if(guider_ui.screen_2_SetupContainer) lv_obj_clear_flag(guider_ui.screen_2_SetupContainer,  LV_OBJ_FLAG_HIDDEN);
     //   if(guider_ui.screen_2_InterfaceIfoContainer) lv_obj_clear_flag(guider_ui.screen_2_InterfaceIfoContainer,  LV_OBJ_FLAG_HIDDEN);
        /* 把 focuser 临时移出组，避免旋钮跳到它 */
        if (g_nav.group && g_nav.focuser) {
            lv_group_remove_obj(g_nav.focuser);
            lv_obj_clear_flag(g_nav.focuser, LV_OBJ_FLAG_CLICK_FOCUSABLE);
        }
        /* 启用按钮导航（默认聚焦第一个按钮） */
        SET_Page_enter(g_nav.group);
        break;
    default: break;
    }
    g_nav.current = id;
    if(g_nav.content) lv_obj_invalidate(g_nav.content);
}

static void show_page_toggle(void)
{
    show_page(g_nav.current == PAGE_HOME ? PAGE_SETUP : PAGE_HOME);
}







/* ========= 模块二：编辑态逻辑（numedit 优先） ========= */
static bool handle_editing_keys(uint32_t key, lv_event_t *e){
    int ia = find_active_idx();
    if(ia < 0) return false;   /* 不在编辑态，交给下一模块 */
    numedit_t *cur = s_bind[ia].ed;  
    /*  让 HomePage 模块决定是否切换保护图标并刷新约束 */
    if(HomePage_ProtectHandleEditingKey(key, cur, e)) return true;

    /* 编辑中按 MENU：结束编辑并切到设置页 */
    if(key == LV_KEY_MENU){
        numedit_switch_edit(cur, NULL);
        if(cur == &g_out_prt_V || cur == &g_out_prt_A) 
        /* 保护值可能刚被编辑过，这里统一刷新一次（稳妥） */
        HomePage_ProtectRefreshCaps();
        show_page(PAGE_SETUP);
        return stop_and_true(e);
    }
    
    /* 随按随切：按触发键在不同编辑器间切换/透传到当前编辑器 */
    int it = find_idx_by_key(key);
    if(it >= 0){
        if(it == ia) (void)numedit_key(s_bind[ia].ed, e, s_bind[ia].trig);
        else         numedit_switch_edit(s_bind[ia].ed, s_bind[it].ed);
        return stop_and_true(e);
    }

    (void)numedit_key(s_bind[ia].ed, e, s_bind[ia].trig);

    /* 若编辑的是保护值，实时刷新一次约束 */
    if(cur == &g_out_prt_V || cur == &g_out_prt_A)
       HomePage_ProtectRefreshCaps();
 
    return stop_and_true(e);
}

/* ========= 模块三：空闲态逻辑（进入编辑 / 菜单切页 / 焦点维护） ========= */
static bool handle_idle_keys(uint32_t key, lv_event_t *e){
    /* 空闲态：按对应触发键，启动相应 numedit */
    int it = find_idx_by_key(key);
    if(it >= 0){
        (void)numedit_key(s_bind[it].ed, e, s_bind[it].trig);
        return stop_and_true(e);
    }
    
    /* 全局 MENU：切换页面 */
    if(key == LV_KEY_MENU){
        show_page_toggle();
        if(!SET_Page_is_active() && g_nav.group && g_nav.focuser)
            lv_group_focus_obj(g_nav.focuser);
        /* MENU 不一定要 stop_bubbling，但为了统一，这里返回 true */
        return stop_and_true(e);
    }

    /* 其它：若当前不在设置页，确保焦点回到占位 focuser，旋钮可继续工作 */
    if(!SET_Page_is_active() && g_nav.group && g_nav.focuser)
        lv_group_focus_obj(g_nav.focuser);

    return false;  /* 未强制处理 */
}



/* ——— 全局键：优先交给 numedit；否则 MENU 切页 ——— */
static void global_key_event(lv_event_t *e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_event_get_key(e);

    /* 按键蜂鸣 */
    ui_click_beep(key);

    /* 1) 先处理锁屏：锁了就拦截一切 */
    if (HomePage_LockHandleKey(key, e))
        return;

    /* 2) 然后处理 OUTPUT 热键：无论是否在编辑，都能触发 */
    if (handle_OUT_ONOFF_hotkey(key, e))
        return;

    /* 3) 再处理编辑态逻辑（V/A 切换、数值输入等） */
    if (handle_editing_keys(key, e))
        return;

    /* 4) 最后是空闲态处理（进编辑 / MENU 换页等） */
    (void)handle_idle_keys(key, e);
}




/* 绑定 group + 焦点占位 */
void bind_global_keys(lv_obj_t *root)
{
    if(!encoder_group) lv_port_indev_init();  /* 确保输入初始化 */
    g_nav.group = encoder_group;
    if(!g_nav.group) return;

    if(!g_nav.focuser){
        g_nav.focuser = lv_obj_create(root);
        lv_obj_set_size(g_nav.focuser, 1, 1);
        lv_obj_set_pos(g_nav.focuser, 0, 0);
        lv_obj_add_flag(g_nav.focuser, LV_OBJ_FLAG_CLICK_FOCUSABLE);
        lv_obj_add_event_cb(g_nav.focuser, global_key_event, LV_EVENT_KEY, NULL);
        lv_group_add_obj(g_nav.group, g_nav.focuser);
    }
    lv_group_focus_obj(g_nav.focuser);
}

/* ——— UI 构建 & GUI 任务 ——— */
void ui_build(void)
{
    lv_ui *ui = &guider_ui;

    setup_scr_screen_1(ui);
    lv_scr_load(ui->screen_1);

    pages_build(ui);
    show_page(PAGE_HOME);
  
    //定义按键标签
    /* 绑定数值编辑：标签 ui->screen_OutSetVal_V，小数2位，范围0~500.00（内部0~50000），整数至少2位 */
    numedit_init(&g_outV, ui->screen_OutSetVal_V, 2, 0, 6000, 2);
    numedit_init(&g_outA, ui->screen_OutSetVal_A, 2, 0, 800, 2);
    numedit_init(&g_out_prt_V, ui->screen_SetVal_V, 2, 0, 6000, 2);
    numedit_init(&g_out_prt_A, ui->screen_SetVal_A, 2, 0, 800, 2);
   
    /* 这里统一初始化保护逻辑（备份 vmax、读取图标初始显隐等） */
    HomePage_ProtectInit();
  
     /*  锁屏初始化 */
    HomePage_LockInit();
  
    /* 把V*A 标签进行一个绑定  绑定给W标签   */
    numedit_bind_product_cap(&g_outV, &g_outA, guider_ui.screen_OutSetVal_W, -1, 180);
    bind_global_keys(ui->screen_1);
 
    lv_obj_clear_flag(guider_ui.screen_1_img_otp, LV_OBJ_FLAG_HIDDEN);
    events_init(ui);  /* 你工程里已有的事件初始化（可留可去） */
}


void app_init(void)
{
    power_init();
    power_set_linear_map(1000.0f, 0.0f, false);

}

void GuiTask(void *argument)
{
    app_init();
    ui_build();

    uint32_t real_value_ms = 0;
    uint32_t ui_ms = 0;

    for(;;){
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));

        real_value_ms += 5;
        ui_ms         += 5;

        if(real_value_ms >= 20){
            real_value_ms = 0;
            power_tick_20ms();   // 20ms 电源心跳
        }

        // ★ UI 刷新：只在输出开着的时候刷，50ms一帧，够顺滑又不占CPU
        if (ui_ms >= 50) {
            ui_ms = 0;
            if (power_get_output()) {
                // 读快照并刷新：放 GUI 线程里，不卡
                // 这函数放 Gui_Task.c 里（或静态局部），用整数拼接避免浮点乱码
                extern void ui_update_real_labels(void);
                ui_update_real_labels();
            }
        }
    }
}



