#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_
#include <stdbool.h>
#include "main.h"
#include "lvgl.h"
#include "numedit.h"

/* 主页生命周期*/
void HomePage_GroupCreate(void);
void HomePage_Enter(void);
void HomePage_Exit(void);


extern void toggle_img_and_flag(lv_obj_t *img, bool *flag);
extern bool s_click_mute ;
extern bool handle_lock_keys(uint32_t key, lv_event_t *e);
extern numedit_t g_outV;
extern numedit_t g_outA;
extern numedit_t g_out_prt_V;
extern numedit_t g_out_prt_A;
extern numedit_t g_out_put;
extern  bool s_click_mute ; 
//**********************保护值 ****************************/
/* === 保护值锁定：对 GUI 暴露的极简接口 === */
/* 初始化：在 UI 构建完、numedit 初始化后调用一次（会备份原始 vmax 等）。 */
void HomePage_ProtectInit(void);

/* 编辑态按键处理：当“当前正在编辑的 numedit”和按键传进来时，
   由主页模块内部决定是否切换锁图标、刷新 vmax 等。
   若本函数已经处理了事件，会返回 true（记得 stop bubbling）；否则返回 false。 */
bool HomePage_ProtectHandleEditingKey(uint32_t key, numedit_t *cur, lv_event_t *e);

/* 如果你在别处修改了保护值本身（而非只切换开/关），可调用这个函数让限制立刻生效。 */
void HomePage_ProtectRefreshCaps(void);



//**********************上锁函数 ****************************/
/* 初始化：UI构建完后调用（创建隐藏定时器等） */
void HomePage_LockInit(void);

/* 切换/设置锁屏状态（会处理提示图标显示和按键提示音静音） */
void HomePage_LockToggle(void);
void HomePage_LockSet(bool on);

/* 查询当前是否锁屏 */
bool HomePage_IsLocked(void);

/* 让GUI路由按键：若该键被锁屏逻辑处理（比如触发解锁/上锁显示等），返回true并应停止冒泡 */
bool HomePage_LockHandleKey(uint32_t key, lv_event_t *e);



#endif
