#ifndef _PRESET_PAGE_H_
#define _PRESET_PAGE_H_

#include "Commd.h"


/*
 * @brief       void PresetPage_Enter(void)
 * @details     进入OutOption页面
 */
void PresetPage_Enter(void);

/*
 * @brief       void PresetPage_Exit(void)
 * @details     退出OutOption页面
 */
void PresetPage_Exit(void);

void PresetPage_GroupCreate(void);

void PresetCont_handler(lv_obj_t *obj, lv_event_t event);

void Preset_Volt_Set_handler(lv_obj_t *obj, lv_event_t event);
void Preset_Curr_Set_handler(lv_obj_t *obj, lv_event_t event);
void Preset_OVP_Set_handler(lv_obj_t *obj, lv_event_t event);
void Preset_OCP_Set_handler(lv_obj_t *obj, lv_event_t event);
void Preset_Time_Set_handler(lv_obj_t *obj, lv_event_t event);


#include "BtnTree.h"
extern Tree_Def *tree_preset;

#endif
