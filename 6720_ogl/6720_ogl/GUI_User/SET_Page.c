#include "SET_Page.h"
#include "Gui_Task.h"  
#include "lv_port_disp.h"
#include "Beep_Device.h"
#include "Gui_Task.h"
#include "st7789.h"
#include "SystemSetting.h"  // 引入头文件
/* —— 内部状态 —— */
static lv_obj_t *s2_btns[7];
static uint8_t   s2_cnt = 0;
static bool      s2_active = false;

/* 聚焦高亮（可选） */
static lv_style_t s2_focus_style;
static bool s2_style_inited = false;
static void s2_init_focus_style_once(void){
    if(s2_style_inited) return;
    s2_style_inited = true;
    lv_style_init(&s2_focus_style);
    lv_style_set_outline_width(&s2_focus_style, 2);
    lv_style_set_outline_color(&s2_focus_style, lv_color_hex(0x33CCFF));
    lv_style_set_outline_opa(&s2_focus_style, LV_OPA_COVER);
    lv_style_set_outline_pad(&s2_focus_style, 2);
    lv_style_set_bg_opa(&s2_focus_style, LV_OPA_80);
    lv_style_set_bg_color(&s2_focus_style, lv_color_hex(0xFF6D00));
}

/* —— 输出状态信息容器 —— */
static lv_obj_t *s2_outstate_cont = NULL;  // 指向 ui->cont_outStateIfoContainer
/* —— Interface Info 容器 —— */
static lv_obj_t *s2_iface_cont = NULL;  // 指向 ui->screen_2_InterfaceIfoContainer
/* —— screen_2_AboutIfoContainer —— */
/* —— About 容器 —— */
static lv_obj_t *s2_about_cont = NULL;  // 指向 ui->screen_2_AboutIfoContainer

/* 可见性判断   容器4&6&7的互斥*/
/* —— 显隐互斥：只显示 target，其余容器全部隐藏 —— */
/* —— 显隐互斥：只显示 target（连父级一起 un-hide），其余容器隐藏 —— */
static inline void s2_show_only(lv_obj_t *target){
    lv_obj_t *all[] = { s2_iface_cont, s2_about_cont, s2_outstate_cont };
    for (uint32_t i = 0; i < sizeof(all)/sizeof(all[0]); i++){
        if (!all[i]) continue;
        if (all[i] == target){
            lv_obj_clear_flag(all[i], LV_OBJ_FLAG_HIDDEN);
            lv_obj_move_foreground(all[i]);
        }else{
            lv_obj_add_flag(all[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
}
//***********************封装函数*************************************
//事件回调和样式设置函数
void add_event_and_style(lv_obj_t *obj, lv_event_cb_t event_cb, lv_group_t *group, bool *in_group_flag) {
    if (!obj || !event_cb) return;

    // 添加事件回调
    lv_obj_add_event_cb(obj, event_cb, LV_EVENT_KEY, NULL);
    // 添加样式
    lv_obj_add_style(obj, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);

    // 将控件添加到 group 中（如果还没有添加）
    if (!(*in_group_flag)) {
        lv_group_add_obj(group, obj);
        *in_group_flag = true;
    }
}

// 退出编辑模式
static void exit_edit_mode(lv_group_t *g, lv_obj_t *label, bool *in_group_flag, lv_obj_t *focus_obj) {
    if (g) lv_group_set_editing(g, false);  // 退出编辑态

    // 如果有标签对象，移出 group
    if (label && *in_group_flag) {
        lv_group_remove_obj(label);
        *in_group_flag = false;
    }

    // 焦点回到指定的对象
    if (focus_obj) {
        lv_group_focus_obj(focus_obj);
    }

    lv_event_stop_bubbling(NULL);  // 停止事件冒泡
}


//***********************封装函数 END*************************************

//1.蜂蜜器
/* —— Beep 值编辑相关 —— */
static bool      s2_beep_cb_added = false;
static bool s2_beep_in_group = false;   // BeepVal 是否已加入 group
static lv_obj_t *s2_beep_val = NULL;   //蜂鸣器标签

static inline void ui_click_beep(uint32_t key){ 
    if(!current_settings.beep_state) return;      // 用户关闭蜂鸣器
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





static inline void s2_set_topbar_beep_icon(bool on)
{
    if(guider_ui.screen_1_Beep_on && guider_ui.screen_1_Beep_off){
        if(on){
            lv_obj_clear_flag(guider_ui.screen_1_Beep_on,  LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag  (guider_ui.screen_1_Beep_off, LV_OBJ_FLAG_HIDDEN);
        }else{
            lv_obj_add_flag  (guider_ui.screen_1_Beep_on,  LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(guider_ui.screen_1_Beep_off, LV_OBJ_FLAG_HIDDEN);
        }
    }
}


/* 刷新标签文本 */
static void s2_beep_refresh(void){
if (!s2_beep_val) return;
  //鎵撳紑:打开   鍏抽棴：关闭
  lv_label_set_text(s2_beep_val, current_settings.beep_state ? "鎵撳紑" : "鍏抽棴");  
  printf("Beeps state updated: %d\n",  current_settings.beep_state);  // 打印蜂鸣器状态更新
  s2_set_topbar_beep_icon( current_settings.beep_state); // 同步屏幕1顶栏图标
}


/* 在 BeepVal 上的按键处理：UP/DOWN 切换文字；ENTER 退出编辑；MENU 回首页 */
static void s2_beep_edit_key_cb(lv_event_t *e){
  
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
  
    uint32_t   key = lv_event_get_key(e);  
    lv_obj_t  *obj = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(obj);

    // 如果按下回车或编码器，退出编辑模式
    if (key == LV_KEY_ENTER || key == LV_KEY_ENCODER) {
        exit_edit_mode(g, s2_beep_val, &s2_beep_in_group, s2_btns[0]);
        return;
    }
    // 如果按下菜单键，返回首页
    if (key == LV_KEY_MENU) {
        exit_edit_mode(g, s2_beep_val, &s2_beep_in_group, NULL);
        show_page(PAGE_HOME);
        return;
    }

    if (key == LV_KEY_UP || key == LV_KEY_DOWN){
         current_settings.beep_state = ! current_settings.beep_state;  // 每转一次就翻转
        save_settings_to_eeprom(&current_settings); // 保存到 EEPROM
        s2_beep_refresh();//刷新beep
        lv_event_stop_bubbling(e);
        return;
    }
}


/* 进入 BeepVal 的编辑模式 */
/* 进入 BeepVal 的编辑模式 */
static void s2_enter_beep_edit(lv_group_t *g) {
    if (!s2_beep_val || !g) return;

    // 直接为控件添加事件回调和样式，不再检查是否已添加
    add_event_and_style(s2_beep_val, s2_beep_edit_key_cb, g, &s2_beep_in_group);

    s2_beep_refresh();  // 进入时先把文字刷新到当前状态

    lv_group_focus_obj(s2_beep_val);  // 焦点给标签
    lv_group_set_editing(g, true);    // 切到“编辑态”：编码器键交给标签
}



//2.背光亮度
/* —— BackLight 亮度编辑相关 —— */
static lv_obj_t *s2_light_val = NULL;   // 指向 ui->screen_2_LightVal
static int16_t   s2_light = 100;        // 0~100，初始化 100
static bool      s2_light_cb_added = false;
static bool      s2_light_in_group = false;  // 是否已加入 group

static const int16_t s2_light_min = 20, s2_light_max = 100, s2_light_step = 1;

static void s2_light_apply(void){
    uint8_t pct = (uint8_t)s2_light;
    if(pct < s2_light_min) pct = s2_light_min;   // 20
    if(pct > s2_light_max) pct = s2_light_max;   // 100
    SetBackLight(pct);
}

static void s2_light_refresh(void){
    if (!s2_light_val) return;
    if (s2_light < s2_light_min) s2_light = s2_light_min;  // 30
    if (s2_light > s2_light_max) s2_light = s2_light_max;  // 100
    lv_label_set_text_fmt(s2_light_val, "%d%%", (int)s2_light);  // 想带百分号就用 "%d%%"
    s2_light_apply();  // ★ 每次刷新都把数值同步到背光
}


/* 在 LightVal 上的按键处理：UP/DOWN 调整数值；ENTER/ENCODER 退出；MENU 回首页 */
static void s2_light_edit_key_cb(lv_event_t *e){
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t   key = lv_event_get_key(e);
    lv_obj_t  *obj = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(obj);

    if (key == LV_KEY_UP || key == LV_KEY_NEXT){
        s2_light += s2_light_step;
        s2_light_refresh();
        lv_event_stop_bubbling(e);
        return;
    }
    if (key == LV_KEY_DOWN || key == LV_KEY_PREV){
        s2_light -= s2_light_step;
        s2_light_refresh();
        lv_event_stop_bubbling(e);
        return;
    }

    /* 退出编辑：旋钮按下在你的平台可能是 LV_KEY_ENCODER */
    if (key == LV_KEY_ENTER || key == LV_KEY_ENCODER){
        if (g) lv_group_set_editing(g, false);
        /* 退出后焦点回到“背光亮度”按钮（数组 1 号） */
        if (g) lv_group_focus_obj(s2_btns[1]);
        if (s2_light_in_group){
            lv_group_remove_obj(s2_light_val);
            s2_light_in_group = false;
        }
        lv_event_stop_bubbling(e);
        return;
    }

    if (key == LV_KEY_MENU){
        if (g) lv_group_set_editing(g, false);
        if (s2_light_in_group){
            lv_group_remove_obj(s2_light_val);
            s2_light_in_group = false;
        }
        show_page(PAGE_HOME);
        lv_event_stop_bubbling(e);
        return;
    }
}

/* 进入 LightVal 的编辑模式 */
static void s2_enter_light_edit(lv_group_t *g){
    if (!s2_light_val || !g) return;
    if (!s2_light_cb_added){
        lv_obj_add_event_cb(s2_light_val, s2_light_edit_key_cb, LV_EVENT_KEY, NULL);
        lv_obj_add_style(s2_light_val, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        s2_light_cb_added = true;
    }
    s2_light_refresh();  // 进入时刷新显示
    if (!s2_light_in_group){
        lv_group_add_obj(g, s2_light_val);
        s2_light_in_group = true;
    }
    lv_group_focus_obj(s2_light_val);  // 焦点给 LightVal
    lv_group_set_editing(g, true);     // 切到“编辑态”
}


//3.存储组
/* —— 存储组（0~200）编辑相关 —— */
static lv_obj_t *s2_mem_val = NULL;     // 指向 ui->screen_2_GroupVal
static lv_obj_t *label_mem_num = NULL;     // 指向 ui->screen_1_label_mem_num
static int16_t   s2_mem = 0;            // 0~30，初始化 0（需要别的初值就改这里）
static bool      s2_mem_cb_added = false;
static bool      s2_mem_in_group = false;
static const int16_t s2_mem_min = 0, s2_mem_max = 200, s2_mem_step = 1;

static void s2_mem_refresh(void){
    if (!s2_mem_val) return;
    if (s2_mem < s2_mem_min) s2_mem = s2_mem_min;
    if (s2_mem > s2_mem_max) s2_mem = s2_mem_max;
    lv_label_set_text_fmt(label_mem_num, "%03d",(int)s2_mem); 
    lv_label_set_text_fmt(s2_mem_val, "%03d", (int)s2_mem);
}

/* 在 Memscreen_2_GroupVal 上的键处理：UP/DOWN 调整数值；ENTER/ENCODER 退出；MENU 回首页 */
static void s2_mem_edit_key_cb(lv_event_t *e){
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t   key = lv_event_get_key(e);
    lv_obj_t  *obj = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(obj);

    if (key == LV_KEY_UP || key == LV_KEY_NEXT){
        s2_mem += s2_mem_step;
        s2_mem_refresh();
        lv_event_stop_bubbling(e);
        return;
    }
    if (key == LV_KEY_DOWN || key == LV_KEY_PREV){
        s2_mem -= s2_mem_step;
        s2_mem_refresh();
        lv_event_stop_bubbling(e);
        return;
    }

    if (key == LV_KEY_ENTER || key == LV_KEY_ENCODER){
        if (g) lv_group_set_editing(g, false);
        if (g) lv_group_focus_obj(s2_btns[2]);  // 2号 = screen_2_btn_MemGroup
        if (s2_mem_in_group){
            lv_group_remove_obj(s2_mem_val);
            s2_mem_in_group = false;
        }
        lv_event_stop_bubbling(e);
        return;
    }

    if (key == LV_KEY_MENU){
        if (g) lv_group_set_editing(g, false);
        if (s2_mem_in_group){
            lv_group_remove_obj(s2_mem_val);
            s2_mem_in_group = false;
        }
        show_page(PAGE_HOME);
        lv_event_stop_bubbling(e);
        return;
    }
}

/* 进入 Memscreen_2_GroupVal 的编辑模式 */
static void s2_enter_mem_edit(lv_group_t *g){
    if (!s2_mem_val || !g) return;
    if (!s2_mem_cb_added){
        lv_obj_add_event_cb(s2_mem_val, s2_mem_edit_key_cb, LV_EVENT_KEY, NULL);
        lv_obj_add_style(s2_mem_val, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        s2_mem_cb_added = true;
    }
    s2_mem_refresh();
    if (!s2_mem_in_group){
        lv_group_add_obj(g, s2_mem_val);
        s2_mem_in_group = true;
    }
    lv_group_focus_obj(s2_mem_val);
    lv_group_set_editing(g, true);
}



//4.输出状态

static bool      s2_ato_on  = false;    // true=打开, false=关闭
static bool      s2_ato_cb_added = false;
static bool      s2_ato_in_group = false;
/* —— Ato（自动）编辑相关 —— */
static lv_obj_t *s2_ato_val = NULL;     // 指向 ui->screen_2_AtoVal



/* —— 顶栏 Keep 图标显隐 —— */
static inline void s2_set_topbar_keep_icon(bool on)
{
    /* 注意：把“screen_1_label_KEEP”替换成你工程里 img_keep 的真实变量名 */
    if (guider_ui.screen_1_label_KEEP){
        if (on)  lv_obj_clear_flag(guider_ui.screen_1_label_KEEP, LV_OBJ_FLAG_HIDDEN);
        else     lv_obj_add_flag  (guider_ui.screen_1_label_KEEP, LV_OBJ_FLAG_HIDDEN);
    }
}

/* 刷新 Ato 标签文本 */
static void s2_ato_refresh(void){
    if(!s2_ato_val) return;
    lv_label_set_text(s2_ato_val, s2_ato_on ? "ON" : "OFF");  // 如担心中文，可改 "ON"/"OFF"
    s2_set_topbar_keep_icon(s2_ato_on);
  
}

/* 在 AtoVal 上的键处理：UP/DOWN/NEXT/PREV 切换；ENTER/ENCODER 退出；MENU 回首页 */
static void s2_ato_edit_key_cb(lv_event_t *e){
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t   key = lv_event_get_key(e);
    lv_obj_t  *obj = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(obj);
  /* ★ 无论什么键，只要在 AtoVal 的编辑回调里，就把容器亮出来 */
    s2_show_only(s2_outstate_cont);
    switch(key){
    case LV_KEY_UP:
    case LV_KEY_DOWN:
    case LV_KEY_NEXT:
    case LV_KEY_PREV:
        s2_ato_on = !s2_ato_on;
        s2_ato_refresh();
   //     s2_show_only(s2_outstate_cont);   // 切换时显示“输出状态”容器，并隐藏其它容器
        lv_event_stop_bubbling(e);
        return;

    case LV_KEY_ENTER:
    case LV_KEY_ENCODER:
        if (g) lv_group_set_editing(g, false);
        if (g) lv_group_focus_obj(s2_btns[3]);  // 3号按钮是 Ato
        if (s2_ato_in_group){
            lv_group_remove_obj(s2_ato_val);
            s2_ato_in_group = false;
        }
        lv_event_stop_bubbling(e);
        return;

    case LV_KEY_MENU:
        if (g) lv_group_set_editing(g, false);
        if (s2_ato_in_group){
            lv_group_remove_obj(s2_ato_val);
            s2_ato_in_group = false;
        }
        show_page(PAGE_HOME);
        lv_event_stop_bubbling(e);
        return;

    default:
        break;
    }
}

/* 进入 AtoVal 的编辑模式 */
static void s2_enter_ato_edit(lv_group_t *g){
    if (!s2_ato_val || !g) return;
    if (!s2_ato_cb_added){
        lv_obj_add_event_cb(s2_ato_val, s2_ato_edit_key_cb, LV_EVENT_KEY, NULL);
        lv_obj_add_style(s2_ato_val, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        s2_ato_cb_added = true;
    }
    s2_ato_refresh();
    if (!s2_ato_in_group){
        lv_group_add_obj(g, s2_ato_val);
        s2_ato_in_group = true;
    }
    lv_group_focus_obj(s2_ato_val);
    lv_group_set_editing(g, true);
}

//5.Language
/* —— 语言切换 —— */
/* —— 语言（Lang）编辑相关 —— */
static lv_obj_t *s2_lang_val = NULL;   // 指向 ui->screen_2_LangVal
static bool      s2_lang_is_cn = true; // true=简体中文，false=English
static bool      s2_lang_cb_added = false;
static bool      s2_lang_in_group = false;

/* 刷新标签文本（UTF-8 安全） */
static void s2_lang_refresh(void){
    if (!s2_lang_val) return;
    lv_label_set_text(s2_lang_val, s2_lang_is_cn ? "绠�浣撲腑鏂?" : "");
}

/* 在 LangVal 上的按键处理：UP/DOWN/NEXT/PREV 切换；ENTER/ENCODER 退出；MENU 回首页 */
static void s2_lang_edit_key_cb(lv_event_t *e){
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t   key = lv_event_get_key(e);
    lv_obj_t  *obj = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(obj);

    switch (key){
    case LV_KEY_UP:
    case LV_KEY_DOWN:
    case LV_KEY_NEXT:
    case LV_KEY_PREV:
        s2_lang_is_cn = !s2_lang_is_cn;   // 每转一次就翻转
        s2_lang_refresh();
        lv_event_stop_bubbling(e);
        return;

    case LV_KEY_ENTER:
    case LV_KEY_ENCODER:                  // 旋钮按下可能映射成 ENCODER
        if (g) lv_group_set_editing(g, false);      // 退出编辑态
        if (g) lv_group_focus_obj(s2_btns[4]);      // 焦点回“语言”按钮（索引4）
        if (s2_lang_in_group){
            lv_group_remove_obj(s2_lang_val);       // 可选：移出 group，避免后续导航再跳到它
            s2_lang_in_group = false;
        }
        lv_event_stop_bubbling(e);
        return;

    case LV_KEY_MENU:
        if (g) lv_group_set_editing(g, false);
        if (s2_lang_in_group){
            lv_group_remove_obj(s2_lang_val);
            s2_lang_in_group = false;
        }
        show_page(PAGE_HOME);
        lv_event_stop_bubbling(e);
        return;

    default:
        break;
    }
}
/* 进入 LangVal 的编辑模式 */
static void s2_enter_lang_edit(lv_group_t *g){
    if (!s2_lang_val || !g) return;

    if (!s2_lang_cb_added){
        lv_obj_add_event_cb(s2_lang_val, s2_lang_edit_key_cb, LV_EVENT_KEY, NULL);
        lv_obj_add_style(s2_lang_val, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        s2_lang_cb_added = true;
    }

    s2_lang_refresh();                           // 进入时先刷新显示

    if (!s2_lang_in_group) {                     // 确保标签在 group 里，否则无法聚焦
        lv_group_add_obj(g, s2_lang_val);
        s2_lang_in_group = true;
    }

    lv_group_focus_obj(s2_lang_val);             // 焦点给标签
    lv_group_set_editing(g, true);               // 切到“编辑态”：编码器键交给标签
}




/* 让按钮自己处理 MENU/UP/DOWN：UP=上一项，DOWN=下一项 */
/* 按钮键盘回调：MENU 返回首页；UP/DOWN 在按钮间移动焦点 */
static void s2_btn_key_cb(lv_event_t *e){
    if (lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t   key = lv_event_get_key(e);
  
      ui_click_beep(key);  // ← 放最前面
    lv_obj_t  *btn = lv_event_get_target(e);
    lv_group_t *g  = lv_obj_get_group(btn);
 
      // ? 在这里加 OUTPUT 热键处理    
  if (key == LV_KEY_OUTPUT || key == LV_KEY_OUTPUT_LONGP) {
        handle_OUT_ONOFF_hotkey(key, e);
        return;    // 已经在 handle_OUT_ONOFF_hotkey 里 stop 事件了
    }
  
    if (key == LV_KEY_MENU){
        show_page(PAGE_HOME);
        lv_event_stop_bubbling(e);
        return;
    }

    /* 新增：当焦点在“蜂鸣器”按钮上，按 ENTER 进入 BeepVal 编辑 */
    if (key == LV_KEY_ENTER || key == LV_KEY_ENCODER){
      if (btn == s2_btns[0]){          // 蜂鸣器
        s2_enter_beep_edit(g);
        lv_event_stop_bubbling(e);
        return;
      }
      if (btn == s2_btns[1]){          // 背光亮度
        s2_enter_light_edit(g);
        lv_event_stop_bubbling(e);
        return;
      }
      if (btn == s2_btns[2]){          // 存储组
        s2_enter_mem_edit(g);
        lv_event_stop_bubbling(e);
        return;
      }              
      if (btn == s2_btns[3]){            // 3号 = screen_2_btn_Ato
        s2_enter_ato_edit(g);          // 进入 Ato 编辑
        s2_show_only(s2_outstate_cont);// 同时显示“输出状态”，并隐藏其它互斥容器
        lv_event_stop_bubbling(e);
        return;
      }             
      if (btn == s2_btns[4]){              // 4号 = screen_2_btn_Lang
        s2_enter_lang_edit(g);  
        lv_event_stop_bubbling(e);
        return;
      } 
      if (btn == s2_btns[5]){          // 5号 = screen_2_btn_IoIfo（接口信息）
        s2_show_only(s2_iface_cont);
        lv_event_stop_bubbling(e);
        return;
      }       
      if (btn == s2_btns[6]){          // 6号 = screen_2_btn_About（关于本机）
        s2_show_only(s2_about_cont);
        lv_event_stop_bubbling(e);
        return;
      } 
       /* 其它按钮… */
    }



    /* 旋钮 UP/DOWN 在按钮之间移动焦点（按你当前方向保持不变） */
    if ((key == LV_KEY_UP   || key == LV_KEY_PREV) && g){
        lv_group_focus_next(g);
        lv_event_stop_bubbling(e);
        return;
    }
    if ((key == LV_KEY_DOWN || key == LV_KEY_NEXT) && g){
        lv_group_focus_prev(g);
        lv_event_stop_bubbling(e);
        return;
    }
}


/* 1) 记录 7 个按钮指针 */
void SET_Page_init(lv_ui *ui)
{
    /* 采集 7 个按钮指针 */
    s2_cnt = 0;
    s2_btns[s2_cnt++] = ui->screen_2_btn_Beep;
    s2_btns[s2_cnt++] = ui->screen_2_btn_BackLight;
    s2_btns[s2_cnt++] = ui->screen_2_btn_MemGroup;
    s2_btns[s2_cnt++] = ui->screen_2_btn_Ato;
    s2_btns[s2_cnt++] = ui->screen_2_btn_Lang;
    s2_btns[s2_cnt++] = ui->screen_2_btn_IoIfo;
    s2_btns[s2_cnt++] = ui->screen_2_btn_About;

      printf("UI Buttons Initialized\n");


  
  
    /* 聚焦样式初始化一次 */
    s2_init_focus_style_once();

    /* 只在初始化时：给每个按钮绑定键盘回调 & 聚焦样式 */
    for(uint8_t i=0;i<s2_cnt;i++){
        lv_obj_t *btn = s2_btns[i];
        if(!btn) continue;
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICK_FOCUSABLE);
        lv_obj_add_style(btn, &s2_focus_style, LV_PART_MAIN | LV_STATE_FOCUSED);

        /* 先移除可能已有的同回调，再绑定一次，保证不会重复 */
        lv_obj_remove_event_cb(btn, s2_btn_key_cb);
        lv_obj_add_event_cb(btn, s2_btn_key_cb, LV_EVENT_KEY, NULL);
    }
    //1.BEEP
    /* 记录 BeepVal 标签对象，并初始化显示文字 */
    s2_beep_val = ui->screen_2_BeepVal;
    s2_beep_refresh();
    //2.背光
    s2_light_val = ui->screen_2_LightVal;
    s2_light_refresh();
    //3.存储器   
    s2_mem_val = ui->screen_2_GroupVal;   //    
    label_mem_num =ui->screen_1_label_mem_num;    
    s2_mem_refresh();
    //4.输出状态         
    /* 记录 AtoVal 标签对象并刷新一次 */
    s2_ato_val = ui->screen_2_AtoVal;
    s2_ato_refresh();
    s2_set_topbar_keep_icon(s2_ato_on);
    /* 记录“输出状态信息”容器（默认隐藏） */
    s2_outstate_cont = ui->screen_2_cont_outStateIfoContainer;
    if (s2_outstate_cont) lv_obj_add_flag(s2_outstate_cont, LV_OBJ_FLAG_HIDDEN);
    
    //5.语言  
      s2_lang_val = ui->screen_2_LangVal;   // 
//    s2_lang_refresh();
    //6.接口消息   
    s2_iface_cont = ui->screen_2_InterfaceIfoContainer;  //
    // 可选：确保初始隐藏
    if (s2_iface_cont) lv_obj_add_flag(s2_iface_cont, LV_OBJ_FLAG_HIDDEN);
    //7.关于本机    
    /* 记录 About 容器（默认隐藏） */
    s2_about_cont = ui->screen_2_AboutIfoContainer;    // 
    if (s2_about_cont) lv_obj_add_flag(s2_about_cont, LV_OBJ_FLAG_HIDDEN);
    
    
    
}

/* 2) 进入 screen_2：加入组 & 聚焦第一个 */
void SET_Page_enter(lv_group_t *group)
{
    if(!group) return;

    /* 只把按钮加入 group */
    for(uint8_t i=0;i<s2_cnt;i++){
        lv_obj_t *btn = s2_btns[i];
        if(!btn) continue;
        lv_group_add_obj(group, btn);
    }

    /* 默认聚焦第一个按钮；旋钮用于对象切换 */
    if(s2_cnt && s2_btns[0]) lv_group_focus_obj(s2_btns[0]);
    lv_group_set_editing(group, false);
    lv_group_set_wrap(group, true);

    
    s2_active = true;
}

void SET_Page_leave(lv_group_t *group, lv_obj_t *fallback_focus)
{
    if(!group) return;

    /* ★ 若标签仍在组里，移除它 */
    if (s2_beep_in_group) {
        lv_group_remove_obj(s2_beep_val);
        s2_beep_in_group = false;
    }

   if (s2_light_in_group){
    lv_group_remove_obj(s2_light_val);
    s2_light_in_group = false;
    } 
        
    if (s2_mem_in_group){
        lv_group_remove_obj(s2_mem_val);
        s2_mem_in_group = false;
    }
    
    if (s2_ato_in_group){
      lv_group_remove_obj(s2_ato_val);
      s2_ato_in_group = false;
    }
    
    if (s2_outstate_cont){
    lv_obj_add_flag(s2_outstate_cont, LV_OBJ_FLAG_HIDDEN);
    }   
    
    if (s2_lang_in_group){
        lv_group_remove_obj(s2_lang_val);
        s2_lang_in_group = false;
    }  
    
      if (s2_iface_cont){
        lv_obj_add_flag(s2_iface_cont, LV_OBJ_FLAG_HIDDEN);
      }

    if (s2_about_cont) {
      lv_obj_add_flag(s2_about_cont, LV_OBJ_FLAG_HIDDEN);
    }

    
    for(uint8_t i=0;i<s2_cnt;i++){
        lv_obj_t *btn = s2_btns[i];
        if(btn) lv_group_remove_obj(btn);
    }
    s2_active = false;       
    if(fallback_focus) lv_group_focus_obj(fallback_focus);
}


bool SET_Page_is_active(void)
{
    return s2_active;
}


