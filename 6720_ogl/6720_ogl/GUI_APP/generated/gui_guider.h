/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_body;
	lv_obj_t *screen_1_cont_1;
	lv_obj_t *screen_1_label_border;
	lv_obj_t *screen_1_Beep_on;
	lv_obj_t *screen_1_led_1;
	lv_obj_t *screen_1_Beep_off;
	lv_obj_t *screen_1_img_unlock;
	lv_obj_t *screen_1_lock_on;
	lv_obj_t *screen_1_img_cat;
	lv_obj_t *screen_1_img_otp;
	lv_obj_t *screen_1_img_mem;
	lv_obj_t *screen_1_label_men_border;
	lv_obj_t *screen_1_label_mem_num;
	lv_obj_t *screen_1_label_KEEP;
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_cont_Set;
	lv_obj_t *screen_SetVal_A;
	lv_obj_t *screen_SetUnit_A;
	lv_obj_t *screen_SetUnit_V;
	lv_obj_t *screen_SetVal_V;
	lv_obj_t *screen_LimtSet_Title;
	lv_obj_t *screen_OutSetUnit_W;
	lv_obj_t *screen_OutSetVal_W;
	lv_obj_t *screen_OutSetVal_A;
	lv_obj_t *screen_OutSetUnit_A;
	lv_obj_t *screen_OutSetUnit_V;
	lv_obj_t *screen_OutSet_Title;
	lv_obj_t *screen_OutSetVal_V;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_cont_Out;
	lv_obj_t *screen_RealVal_V;
	lv_obj_t *screen_RealUnit_V;
	lv_obj_t *screen_RealUnit_A;
	lv_obj_t *screen_RealUnit_W;
	lv_obj_t *screen_RealVal_W;
	lv_obj_t *screen_RealVal_A;
	lv_obj_t *screen_CvText;
	lv_obj_t *screen_CcText;
	lv_obj_t *screen_label_ON_OFF;
	lv_obj_t *screen_Msg_lock;
	lv_obj_t *screen_label_lock;
	lv_obj_t *screen_label_unlock;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_SetupContainer;
	lv_obj_t *screen_2_btn_Beep;
	lv_obj_t *screen_2_btn_Beep_label;
	lv_obj_t *screen_2_btn_BackLight;
	lv_obj_t *screen_2_btn_BackLight_label;
	lv_obj_t *screen_2_btn_About;
	lv_obj_t *screen_2_btn_About_label;
	lv_obj_t *screen_2_btn_MemGroup;
	lv_obj_t *screen_2_btn_MemGroup_label;
	lv_obj_t *screen_2_btn_Lang;
	lv_obj_t *screen_2_btn_Lang_label;
	lv_obj_t *screen_2_btn_Ato;
	lv_obj_t *screen_2_btn_Ato_label;
	lv_obj_t *screen_2_btn_IoIfo;
	lv_obj_t *screen_2_btn_IoIfo_label;
	lv_obj_t *screen_2_BeepVal;
	lv_obj_t *screen_2_LightVal;
	lv_obj_t *screen_2_GroupVal;
	lv_obj_t *screen_2_AtoVal;
	lv_obj_t *screen_2_LangVal;
	lv_obj_t *screen_2_cont_1;
	lv_obj_t *screen_2_AboutIfoContainer;
	lv_obj_t *screen_2_label_12;
	lv_obj_t *screen_2_label_11;
	lv_obj_t *screen_2_label_10;
	lv_obj_t *screen_2_label_9;
	lv_obj_t *screen_2_label_7;
	lv_obj_t *screen_2_InterfaceIfoContainer;
	lv_obj_t *screen_2_label_1;
	lv_obj_t *screen_2_label_2;
	lv_obj_t *screen_2_label_3;
	lv_obj_t *screen_2_label_4;
	lv_obj_t *screen_2_label_5;
	lv_obj_t *screen_2_label_6;
	lv_obj_t *screen_2_cont_outStateIfoContainer;
	lv_obj_t *screen_2_label_state_off;
	lv_obj_t *screen_2_label_state_on;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
LV_IMG_DECLARE(_BeepOn_alpha_25x25);
LV_IMG_DECLARE(_BeepOff_alpha_25x25);
LV_IMG_DECLARE(_unlock_alpha_28x28);
LV_IMG_DECLARE(_Lock_alpha_28x28);
LV_IMG_DECLARE(_miaomiao_alpha_32x32);
LV_IMG_DECLARE(_OTP_alpha_37x23);
LV_IMG_DECLARE(_mem_alpha_23x23);
LV_IMG_DECLARE(_dischecked_alpha_20x20);
LV_IMG_DECLARE(_dischecked_alpha_20x20);
LV_IMG_DECLARE(_checked_alpha_18x18);
LV_IMG_DECLARE(_checked_alpha_18x18);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_19)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_48)
LV_FONT_DECLARE(lv_font_arial_48)
LV_FONT_DECLARE(lv_font_arial_16)
LV_FONT_DECLARE(lv_font_montserratMedium_25)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_15)


LV_FONT_DECLARE(myFont_weiruanyahei)
LV_FONT_DECLARE(myFont_bold48)

#ifdef __cplusplus
}
#endif
#endif
