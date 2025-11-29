#ifndef _STYLE_H_
#define _STYLE_H_

#include "lvgl/lvgl.h"

extern lv_style_t style_btn_focus;
extern lv_style_t style_btn_defocus;

void ICON_StyleInit(lv_obj_t *img);

void UI_Label_Value_Style_Load(lv_obj_t *label);

void UI_BtnMatrix_Style_Load(lv_obj_t *btnm);

void Tabel_Btn_Style_Init(lv_obj_t *label);




/*
 * @brief       void ListTempPge_TypeImg_StyleInit(lv_obj_t* button)
 * @details     波形图片风格Style设置(浅蓝色外边框)
 */
void ListTempPge_TypeImg_StyleInit(lv_obj_t *button);

/*
 * @brief       void ListTempPage_btnStyle_Init(lv_obj_t *label)
 * @details     编辑参数 按键风格初始化(无边框,标签蓝色,参数白色)
 */
void ListTempPage_btnStyle_Init(lv_obj_t *label);

/*
 * @brief       void DelayTempPage_btnStyle_Init(lv_obj_t *label)
 * @details     编辑参数 按键风格初始化(无边框,标签浅蓝色,参数白色)
 */
void DelayTempPage_btnStyle_Init(lv_obj_t *label);

#endif
