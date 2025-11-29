#ifndef _MONITOR_PAGE_H_
#define _MONITOR_PAGE_H_

#include "Commd.h"




/*!
 * @brief   void Monitor_Vol_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电压设置
 */
void Monitor_Vol_Protect_handler(lv_obj_t *obj, lv_event_t event);

/*!
 * @brief   void Monitor_Amp_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电流设置
 */
void Monitor_Amp_Protect_handler(lv_obj_t *obj, lv_event_t event);

/*!
 * @brief   void Monitor_Wat_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电流设置
 */
void Monitor_Wat_Protect_handler(lv_obj_t *obj, lv_event_t event);

/*!
 * @brief   void Monitor_Dvm_Protect_handler(lv_obj_t *obj, lv_event_t event)
 *          保护电流设置
 */
void Monitor_Dvm_Protect_handler(lv_obj_t *obj, lv_event_t event);

/*!
 * @brief   void Monitor_Logic_handler(lv_obj_t *obj, lv_event_t event)
 *          保护逻辑设置
 */
void Monitor_Logic_handler(lv_obj_t *obj, lv_event_t event);



void Monitor_Sensitivity_handler(lv_obj_t *obj, lv_event_t event);
void Monitor_PowerOFF_handler(lv_obj_t *obj, lv_event_t event);
void Monitor_Beep_handler(lv_obj_t *obj, lv_event_t event);
void Monitor_Tips_handler(lv_obj_t *obj, lv_event_t event);

void Monitor_handler(lv_obj_t *obj, lv_event_t event);

/*
 * @brief       void Monitor_Enter(void)
 * @details     进入Monitor页面
 */
void MonitorPage_Enter(void);

/*
 * @brief       void MonitorPage_Exit(void)
 * @details     退出Monitor页面
 */
void MonitorPage_Exit(void);

void MonitorPage_GroupCreate(void);

void MonitorTable_handler(lv_obj_t *obj, lv_event_t event);


#include "BtnTree.h"
extern Tree_Def *tree_monitor;

#endif
