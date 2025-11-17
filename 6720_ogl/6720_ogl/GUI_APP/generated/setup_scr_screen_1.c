/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


typedef struct {
    lv_obj_t *led;
    bool on;
} led_blink_ctx_t;



static void led_blink_cb(lv_timer_t *t)
{
    led_blink_ctx_t *ctx = (led_blink_ctx_t *)t->user_data;
    ctx->on = !ctx->on;
    if(ctx->on) {
        lv_led_set_brightness(ctx->led, 255);
        lv_led_set_color(ctx->led, lv_color_hex(0x00FF5A)); // 强制保持绿色
    } else {
        lv_led_set_brightness(ctx->led, 100);
        lv_led_set_color(ctx->led, lv_color_hex(0x00FF5A));  // 保持颜色一致
        // 可选：也可以不改颜色，只改亮度
    }
}




void setup_scr_screen_1(lv_ui *ui)
{
    //Write codes screen_1
    ui->screen_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_body
    ui->screen_1_body = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_body, 0, 0);
    lv_obj_set_size(ui->screen_1_body, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_1_body, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_body, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_body, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_body, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_body, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_body, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_cont_1
    ui->screen_1_cont_1 = lv_obj_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_1_cont_1, 320, 30);
    lv_obj_set_scrollbar_mode(ui->screen_1_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_border
    ui->screen_1_label_border = lv_label_create(ui->screen_1_cont_1);
    lv_label_set_text(ui->screen_1_label_border, "");
    lv_label_set_long_mode(ui->screen_1_label_border, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_border, 0, 0);
    lv_obj_set_size(ui->screen_1_label_border, 320, 32);

    //Write style for screen_1_label_border, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_border, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_label_border, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_label_border, lv_color_hex(0x252525), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_label_border, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_border, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_border, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_border, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_border, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_border, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_label_border, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_label_border, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_Beep_on
    ui->screen_1_Beep_on = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_Beep_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_Beep_on, &_BeepOn_alpha_25x25);
    lv_img_set_pivot(ui->screen_1_Beep_on, 50,50);
    lv_img_set_angle(ui->screen_1_Beep_on, 0);
    lv_obj_set_pos(ui->screen_1_Beep_on, 5, 3);
    lv_obj_set_size(ui->screen_1_Beep_on, 25, 25);

    //Write style for screen_1_Beep_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_Beep_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_Beep_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->screen_1_Beep_on, 252, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_1_Beep_on, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_Beep_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_led_1
    ui->screen_1_led_1 = lv_led_create(ui->screen_1_cont_1);
    lv_led_set_brightness(ui->screen_1_led_1, 255);
    lv_led_set_color(ui->screen_1_led_1, lv_color_hex(0x9fff00));
    lv_obj_set_pos(ui->screen_1_led_1, 297, 9);
    lv_obj_set_size(ui->screen_1_led_1, 12, 12);

    //Write codes screen_1_Beep_off
    ui->screen_1_Beep_off = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_Beep_off, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_Beep_off, &_BeepOff_alpha_25x25);
    lv_img_set_pivot(ui->screen_1_Beep_off, 50,50);
    lv_img_set_angle(ui->screen_1_Beep_off, 0);
    lv_obj_set_pos(ui->screen_1_Beep_off, 5, 3);
    lv_obj_set_size(ui->screen_1_Beep_off, 25, 25);
    lv_obj_add_flag(ui->screen_1_Beep_off, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_Beep_off, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_Beep_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_1_Beep_off, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_Beep_off, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_Beep_off, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_Beep_off, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_img_unlock
    ui->screen_1_img_unlock = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_img_unlock, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_img_unlock, &_unlock_alpha_28x28);
    lv_img_set_pivot(ui->screen_1_img_unlock, 50,50);
    lv_img_set_angle(ui->screen_1_img_unlock, 0);
    lv_obj_set_pos(ui->screen_1_img_unlock, 37, 0);
    lv_obj_set_size(ui->screen_1_img_unlock, 28, 28);

    //Write style for screen_1_img_unlock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_img_unlock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_1_img_unlock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_img_unlock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_img_unlock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_img_unlock, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_lock_on
    ui->screen_1_lock_on = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_lock_on, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_lock_on, &_Lock_alpha_28x28);
    lv_img_set_pivot(ui->screen_1_lock_on, 50,50);
    lv_img_set_angle(ui->screen_1_lock_on, 0);
    lv_obj_set_pos(ui->screen_1_lock_on, 33, 0);
    lv_obj_set_size(ui->screen_1_lock_on, 28, 28);
    lv_obj_add_flag(ui->screen_1_lock_on, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_1_lock_on, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_lock_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_1_lock_on, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_lock_on, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_lock_on, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_lock_on, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_img_cat
    ui->screen_1_img_cat = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_img_cat, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_img_cat, &_miaomiao_alpha_32x32);
    lv_img_set_pivot(ui->screen_1_img_cat, 50,50);
    lv_img_set_angle(ui->screen_1_img_cat, 0);
    lv_obj_set_pos(ui->screen_1_img_cat, 259, -2);
    lv_obj_set_size(ui->screen_1_img_cat, 32, 32);

    //Write style for screen_1_img_cat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_img_cat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_img_cat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_img_cat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_img_cat, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_img_otp
    ui->screen_1_img_otp = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_img_otp, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_img_otp, &_OTP_alpha_37x23);
    lv_img_set_pivot(ui->screen_1_img_otp, 50,50);
    lv_img_set_angle(ui->screen_1_img_otp, 0);
    lv_obj_set_pos(ui->screen_1_img_otp, 71, 3);
    lv_obj_set_size(ui->screen_1_img_otp, 37, 23);

    //Write style for screen_1_img_otp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_img_otp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_img_otp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_img_otp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_img_otp, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_img_mem
    ui->screen_1_img_mem = lv_img_create(ui->screen_1_cont_1);
    lv_obj_add_flag(ui->screen_1_img_mem, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_img_mem, &_mem_alpha_23x23);
    lv_img_set_pivot(ui->screen_1_img_mem, 50,50);
    lv_img_set_angle(ui->screen_1_img_mem, 0);
    lv_obj_set_pos(ui->screen_1_img_mem, 198, 3);
    lv_obj_set_size(ui->screen_1_img_mem, 23, 23);

    //Write style for screen_1_img_mem, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_img_mem, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_1_img_mem, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_img_mem, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_img_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_img_mem, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_men_border
    ui->screen_1_label_men_border = lv_label_create(ui->screen_1_cont_1);
    lv_label_set_text(ui->screen_1_label_men_border, "");
    lv_label_set_long_mode(ui->screen_1_label_men_border, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_men_border, 195, 0);
    lv_obj_set_size(ui->screen_1_label_men_border, 62, 28);

    //Write style for screen_1_label_men_border, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_men_border, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_label_men_border, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_label_men_border, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_label_men_border, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_men_border, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_men_border, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_men_border, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_men_border, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_men_border, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_men_border, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_mem_num
    ui->screen_1_label_mem_num = lv_label_create(ui->screen_1_cont_1);
    lv_label_set_text(ui->screen_1_label_mem_num, "001");
    lv_label_set_long_mode(ui->screen_1_label_mem_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_mem_num, 213, 6);
    lv_obj_set_size(ui->screen_1_label_mem_num, 53, 16);

    //Write style for screen_1_label_mem_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_mem_num, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_mem_num, &myFont_weiruanyahei, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_mem_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_mem_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_mem_num, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_label_KEEP
    ui->screen_1_label_KEEP = lv_label_create(ui->screen_1_cont_1);
    lv_label_set_text(ui->screen_1_label_KEEP, "KEEP");
    lv_label_set_long_mode(ui->screen_1_label_KEEP, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_KEEP, 129, 2);
    lv_obj_set_size(ui->screen_1_label_KEEP, 60, 24);

    //Write style for screen_1_label_KEEP, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_KEEP, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_label_KEEP, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_label_KEEP, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_label_KEEP, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_KEEP, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_KEEP, lv_color_hex(0xb4ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_KEEP, &myFont_weiruanyahei, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_KEEP, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_KEEP, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_KEEP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_1.
    static led_blink_ctx_t g_led_ctx;   // 放静态，全局都行
    g_led_ctx.led = ui->screen_1_led_1;
    g_led_ctx.on  = true;                // 初始点亮
    
    lv_timer_create(led_blink_cb, 220, &g_led_ctx);

    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

}


//    //The custom code of screen_1.
//    static led_blink_ctx_t g_led_ctx;   // 放静态，全局都行
//    g_led_ctx.led = ui->screen_1_led_1;
//    g_led_ctx.on  = true;                // 初始点亮
//    
//    lv_timer_create(led_blink_cb, 220, &g_led_ctx);

//typedef struct {
//    lv_obj_t *led;
//    bool on;
//} led_blink_ctx_t;



//static void led_blink_cb(lv_timer_t *t)
//{
//    led_blink_ctx_t *ctx = (led_blink_ctx_t *)t->user_data;
//    ctx->on = !ctx->on;
//    if(ctx->on) {
//        lv_led_set_brightness(ctx->led, 255);
//        lv_led_set_color(ctx->led, lv_color_hex(0x00FF5A)); // 强制保持绿色
//    } else {
//        lv_led_set_brightness(ctx->led, 100);
//        lv_led_set_color(ctx->led, lv_color_hex(0x00FF5A));  // 保持颜色一致
//        // 可选：也可以不改颜色，只改亮度
//    }
//}

