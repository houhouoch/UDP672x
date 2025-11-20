#include "HomePage.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "events_init.h"
#include "Beep_Device.h"
#include <stdio.h>
#include "power_ctrl.h"
extern lv_ui guider_ui; // 如果你在别处定义了全局 ui
/* ——— 主页：数值编辑控件 ——— */
numedit_t g_outV;
numedit_t g_outA;
numedit_t g_out_prt_V;
numedit_t g_out_prt_A;
numedit_t g_out_put;
/* ---------- 保护值锁定：内部实现细节（不对外暴露） ---------- */
#define IMG3 (guider_ui.screen_img_3)   /* 保护V 的 √ 图标 */
#define IMG4 (guider_ui.screen_img_4)   /* 保护A 的 √ 图标 */

/* ================== UI 锁屏================== */
#define UI_ICON_LOCKED         (guider_ui.screen_1_lock_on)       /* 上锁图标对象，可为NULL */
#define UI_ICON_UNLOCKED       (guider_ui.screen_1_img_unlock)     /* 解锁图标对象，可为NULL */
#define UI_HINT_PANEL          (guider_ui.screen_Msg_lock)        /* 弹出提示面板，可为NULL */
#define UI_HINT_LABEL_LOCKED   (guider_ui.screen_label_lock)      /* “已锁定”标签，可为NULL */
#define UI_HINT_LABEL_UNLOCKED (guider_ui.screen_label_unlock)    /* “已解锁”标签，可为NULL */

/* 提示显示时长：毫秒，设 0 表示不显示提示框 */
#ifndef LOCK_HINT_MS
#define LOCK_HINT_MS           (1200)
#endif

/* ================== 内部状态 ================== */
static bool s_kbd_locked = false;             /* 当前锁态 */
bool s_click_mute = false;             /* 锁屏时临时禁用按键音（内部用，不对外暴露） */
static lv_timer_t *s_lock_hide_timer = NULL;  /* 提示隐藏定时器 */

/* ================== 内部工具 ================== */
static inline void _show(lv_obj_t *o){ if(o) lv_obj_clear_flag(o, LV_OBJ_FLAG_HIDDEN); }
static inline void _hide(lv_obj_t *o){ if(o) lv_obj_add_flag(o, LV_OBJ_FLAG_HIDDEN);  }


/* 同步锁/解锁图标显隐 */
static void lock_icons_refresh(void)
{
    if (s_kbd_locked) {
        _show(UI_ICON_LOCKED);
        _hide(UI_ICON_UNLOCKED);
    } else {
        _hide(UI_ICON_LOCKED);
        _show(UI_ICON_UNLOCKED);
    }
}

/* 提示隐藏回调 */
static void lock_hide_cb(lv_timer_t *t)
{
    (void)t;
    if (UI_HINT_PANEL) _hide(UI_HINT_PANEL);
    if (s_lock_hide_timer) lv_timer_pause(s_lock_hide_timer);
}

/* 弹出提示并定时隐藏：show_unlock=true 显示“已解锁”，false 显示“已锁定” */
static void lock_msg_pop_variant(bool show_unlock, uint32_t ms)
{
    if (!UI_HINT_PANEL || ms == 0) return;

    /* 先全部隐藏，再只开需要的那一行 */
    if (UI_HINT_LABEL_LOCKED)   _hide(UI_HINT_LABEL_LOCKED);
    if (UI_HINT_LABEL_UNLOCKED) _hide(UI_HINT_LABEL_UNLOCKED);
    if (show_unlock) _show(UI_HINT_LABEL_UNLOCKED);
    else             _show(UI_HINT_LABEL_LOCKED);

    _show(UI_HINT_PANEL);

    if (!s_lock_hide_timer) s_lock_hide_timer = lv_timer_create(lock_hide_cb, ms, NULL);
    lv_timer_set_period(s_lock_hide_timer, ms);
    lv_timer_reset(s_lock_hide_timer);
    lv_timer_resume(s_lock_hide_timer);
}

/* ================== 对外 API（给 Gui_Task 用） ================== */

void HomePage_LockInit(void)
{
    /* 初始：解锁、取消静音、隐藏提示、同步图标 */
    s_kbd_locked = false;
    s_click_mute = false;

    if (UI_HINT_PANEL) _hide(UI_HINT_PANEL);
    lock_icons_refresh();

    /* 创建定时器（先暂停），有需要时再启用 */
    if (!s_lock_hide_timer) {
        s_lock_hide_timer = lv_timer_create(lock_hide_cb, LOCK_HINT_MS ? LOCK_HINT_MS : 1000, NULL);
        lv_timer_pause(s_lock_hide_timer);
    }
}

void HomePage_LockSet(bool on)
{
    s_kbd_locked = on;
    s_click_mute = on;    /* 锁屏时临时关闭按键提示音 */

    lock_icons_refresh();
    lock_msg_pop_variant(/*show_unlock=*/!on, LOCK_HINT_MS);
}

void HomePage_LockToggle(void)
{
    HomePage_LockSet(!s_kbd_locked);
}

bool HomePage_IsLocked(void)
{
    return s_kbd_locked;
}

/* 在全局按键事件里优先调用：
   - 返回 true：该键已被锁屏逻辑处理（要停止冒泡）
   - 返回 false：未处理，外层继续分发 */
bool HomePage_LockHandleKey(uint32_t key, lv_event_t *e)
{
    /* 1) 先看是否触发上/解锁键 */
    if (key == LV_KEY_LOCK) {
        HomePage_LockSet(true);
        if (e) lv_event_stop_bubbling(e);
        return true;
    }
    if (key == LV_KEY_LOCK_LONGP) {
        HomePage_LockSet(false);
        if (e) lv_event_stop_bubbling(e);
        return true;
    }

    /* 2) 已锁屏则屏蔽其它键 */
    if (s_kbd_locked) {
        if (e) lv_event_stop_bubbling(e);
        return true;
    }

    /* 3) 未处理，交给外层 */
    return false;
}





#if 0//上锁函数
//**********************上锁函数 START****************************/
extern bool stop_and_true(lv_event_t *e);

/* ===== —— 仅用于“临时静音点击音”，不影响用户设置 ===== */
bool s_click_mute = false;   // true=临时禁用按键提示音（锁屏中）
/* 短按刚锁住后，忽略紧随其后的 LONGP（同一次物理长按） */
static uint32_t s_lock_ignore_long_until = 0;  // ms, lv_tick_get() 基准
/* ===== 锁屏状态 ===== */
static bool s_kbd_locked = false;
/* ===== 键盘提示，仅弹出容器 ===== */

/* 锁图标刷新：locked=true 显示“锁住”图标；false 隐藏。
   兼容可选的“解锁”图标，如果没放这个对象也没关系（判空跳过）。 */
static inline void lock_icons_refresh(void){
    if (guider_ui.screen_1_lock_on){
        if (s_kbd_locked) lv_obj_clear_flag(guider_ui.screen_1_lock_on, LV_OBJ_FLAG_HIDDEN);
        else              lv_obj_add_flag  (guider_ui.screen_1_lock_on, LV_OBJ_FLAG_HIDDEN);
    }
    /* 可选：如果你在 screen_1 里还放了一个“解锁”图标，比如 ui->screen_1_unlock */
    if (guider_ui.screen_1_img_unlock){
        if (s_kbd_locked) lv_obj_add_flag  (guider_ui.screen_1_img_unlock, LV_OBJ_FLAG_HIDDEN);
        else              lv_obj_clear_flag(guider_ui.screen_1_img_unlock, LV_OBJ_FLAG_HIDDEN);
    }
}

static lv_timer_t *s_lock_hide_timer = NULL;

/* 到时隐藏，并暂停计时器（等待下次按键再启动） */
static void lock_hide_cb(lv_timer_t *t){
    (void)t;
    if (guider_ui.screen_Msg_lock)
        lv_obj_add_flag(guider_ui.screen_Msg_lock, LV_OBJ_FLAG_HIDDEN);
    if (s_lock_hide_timer) lv_timer_pause(s_lock_hide_timer);
}


/* 显示容器；show_unlock=false 显示 label_lock，true 显示 label_unlock */
static void lock_msg_pop_variant(bool show_unlock, uint32_t ms){
    if (!guider_ui.screen_Msg_lock) return;

    /* 切换容器内两个标签的显隐（名字按你界面里的来；这里假设这两个名字） */
    if (guider_ui.screen_label_lock) {
        if (show_unlock) lv_obj_add_flag(guider_ui.screen_label_lock, LV_OBJ_FLAG_HIDDEN);
        else              lv_obj_clear_flag(guider_ui.screen_label_lock, LV_OBJ_FLAG_HIDDEN);
    }
    if (guider_ui.screen_label_unlock) {
        if (show_unlock) lv_obj_clear_flag(guider_ui.screen_label_unlock, LV_OBJ_FLAG_HIDDEN);
        else              lv_obj_add_flag(guider_ui.screen_label_unlock, LV_OBJ_FLAG_HIDDEN);
    }

    /* 显示容器并启动/重置持久定时器 */
    lv_obj_clear_flag(guider_ui.screen_Msg_lock, LV_OBJ_FLAG_HIDDEN);

    if (!s_lock_hide_timer){
        s_lock_hide_timer = lv_timer_create(lock_hide_cb, ms, NULL);
        lv_timer_pause(s_lock_hide_timer);
    }
    lv_timer_set_period(s_lock_hide_timer, ms);
    lv_timer_reset(s_lock_hide_timer);
    lv_timer_resume(s_lock_hide_timer);
 }

bool handle_lock_keys(uint32_t key, lv_event_t *e){
    if(s_kbd_locked){
        /* 已锁定：仅允许长按解锁；其余一律拦截 */
        if(key == LV_KEY_LOCK_LONGP){
            if(lv_tick_get() < s_lock_ignore_long_until) return stop_and_true(e);
            s_kbd_locked  = false;
            s_click_mute  = false;               /* 仅恢复临时静音 */
            lock_icons_refresh();
            lock_msg_pop_variant(true, 1200);    /* 显示“解锁” */
            HAL_GPIO_WritePin(LED_LOCK_GPIO_Port, LED_LOCK_Pin, GPIO_PIN_SET);
            BEEP_OK();
            return stop_and_true(e);
        }
        return stop_and_true(e);
    }

    /* 未锁定：短按上锁（并忽略本次后的长按抖动） */
    if(key == LV_KEY_LOCK){
        s_kbd_locked  = true;
        s_click_mute  = true;                    /* 锁屏时临时静音 */
        lock_icons_refresh();
        s_lock_ignore_long_until = lv_tick_get() + 600;
        lock_msg_pop_variant(false, 1200);       /* 显示“锁定” */
        HAL_GPIO_WritePin(LED_LOCK_GPIO_Port, LED_LOCK_Pin, GPIO_PIN_RESET);
        BEEP_OK();
        return stop_and_true(e);
    }

    /* 单独上报的 LONGP 也拦掉，避免穿透 */
    if(key == LV_KEY_LOCK_LONGP){
        return stop_and_true(e);
    }

    return false; /* 未处理 */
}

//**********************上锁函数 END****************************/
#endif

/* ===== 原始 vmax 备份（初始化后赋值） ===== */
static int32_t vmaxV_orig = 0;
static int32_t vmaxA_orig = 0;

/* ===== 保护开关（由图片显隐控制） ===== */
static bool protV_enabled = false;   // IMG3 显示 = true
static bool protA_enabled = false;   // IMG4 显示 = true

/* ===== 10^n & 刻度换算（向零截断） ===== */
static int32_t p10_i(int n){ int32_t p=1; while(n-- > 0) p*=10; return p; }

static int32_t scale_value_i32(int32_t val, int from_dec, int to_dec){
    if(from_dec == to_dec) return val;
    if(from_dec < to_dec)  return val * p10_i(to_dec - from_dec);
    else                   return val / p10_i(from_dec - to_dec); // 向零截断
}

/* 切换显隐并同步保护标志 */
void toggle_img_and_flag(lv_obj_t *img, bool *flag){
    if (lv_obj_has_flag(img, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN); *flag = true;
    } else {
        lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);   *flag = false;
    }
}




/* ===== 根据保护开关&保护值，动态设置 set_ed->vmax，并必要时夹住当前值 ===== */
static void apply_protect_to_set(numedit_t *set_ed,
                                 numedit_t *prt_ed,
                                 bool prot_enabled,
                                 int32_t vmax_orig)
{
    if(!set_ed) return;

    if(!prot_enabled || !prt_ed){
        /* 关闭保护：恢复原始 vmax */
        set_ed->vmax = vmax_orig;
        /* 当前值如果 > 恢复后的 vmax，按你的需求通常无需下调；若需要可解注释： */
        // if(numedit_get_value(set_ed) > set_ed->vmax) numedit_set_value(set_ed, set_ed->vmax);
        return;
    }

    /* 启用保护：把 vmax 改成“保护值（换到 set 的刻度）” */
    int32_t prt_v   = numedit_get_value(prt_ed);
    int32_t cap_on_set = scale_value_i32(prt_v, prt_ed->dec, set_ed->dec);

    if(cap_on_set < set_ed->vmin) cap_on_set = set_ed->vmin;
    set_ed->vmax = cap_on_set;

    /* 若当前设置值已大于新 vmax，立刻夹到 vmax（=保护值） */
    int32_t cur = numedit_get_value(set_ed);
    if(cur > set_ed->vmax) numedit_set_value(set_ed, set_ed->vmax);
}

/* 便捷：两路一起更新（每次保护开关/保护值变化后都调它） */
static inline void update_all_set_vmax_from_protect(void){
    apply_protect_to_set(&g_outV, &g_out_prt_V, protV_enabled, vmaxV_orig);
    apply_protect_to_set(&g_outA, &g_out_prt_A, protA_enabled, vmaxA_orig);
}

void HomePage_ProtectInit(void)
{
    /* 备份“未受保护时”的原始 vmax（在 numedit_init 之后调用） ** */
    vmaxV_orig = g_outV.vmax;
    vmaxA_orig = g_outA.vmax;

    /* 根据默认图标显示状态，初始化 prot* 标志 */
    if(IMG3) protV_enabled = !lv_obj_has_flag(IMG3, LV_OBJ_FLAG_HIDDEN);
    if(IMG4) protA_enabled = !lv_obj_has_flag(IMG4, LV_OBJ_FLAG_HIDDEN);

    update_all_set_vmax_from_protect();
}

bool HomePage_ProtectHandleEditingKey(uint32_t key, numedit_t *cur, lv_event_t *e)
{
    if(!cur) return false;

    /* 只有旋钮“短按”才切换保护开关（你原逻辑） */
    if(cur == &g_out_prt_V && key == LV_KEY_ENCODER){
        toggle_img_and_flag(IMG3, &protV_enabled);
        update_all_set_vmax_from_protect();
        lv_event_stop_bubbling(e);
        return true;
    }
    if(cur == &g_out_prt_A && key == LV_KEY_ENCODER){
        toggle_img_and_flag(IMG4, &protA_enabled);
        update_all_set_vmax_from_protect();
        lv_event_stop_bubbling(e);
        return true;
    }

    /* 若正在编辑保护值且发生其它按键（数值改变），也可在外面调用 Refresh */
    return false;
}

void HomePage_ProtectRefreshCaps(void)
{
    update_all_set_vmax_from_protect();
}


/* 进入主页：显示并刷新 */
void HomePage_Enter(void)
{
    lv_obj_clear_flag(guider_ui.screen_cont_Set,   LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(guider_ui.screen_cont_Out,   LV_OBJ_FLAG_HIDDEN);
}

/* 退出主页：隐藏 */
void HomePage_Exit(void)
{
    lv_obj_add_flag(guider_ui.screen_cont_Set,   LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_cont_Out,   LV_OBJ_FLAG_HIDDEN);

}

void HomePage_GroupCreate(void)
{ 
    lv_ui *ui = &guider_ui;
  
    setup_scr_screen(ui);
    lv_obj_set_parent(guider_ui.screen_cont_Set,guider_ui.screen_1_body);
    lv_obj_set_parent(guider_ui.screen_cont_Out,guider_ui.screen_1_body);

    HomePage_Enter();
    HomePage_Exit();

}



