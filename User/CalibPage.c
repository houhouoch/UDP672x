#include "CalibPage.h"
#include "btnTree.h"

#include "SettingData.h"



static lv_obj_t *UI_calibNode = NULL;


uint8_t CalibPage_isVisable(void)
{
    return (UI_calibNode != NULL);
}


/*
 * @brief       void CalibPage_Enter(void)
 * @details     进入Menu页面
 */
void CalibPage_Enter(void)
{
    if(UI_calibNode == NULL) {
        UI_calibNode = lv_table_create(ui.Back_cont_back, NULL);
        lv_obj_t *table = UI_calibNode;
        lv_obj_clean_style_list(table, LV_TABLE_PART_BG);
        lv_obj_clean_style_list(table, LV_TABLE_PART_CELL1);
        lv_obj_clean_style_list(table, LV_TABLE_PART_CELL2);
        lv_obj_clean_style_list(table, LV_TABLE_PART_CELL3);
        //设置表格行
        lv_table_set_col_cnt(table, 3);
        lv_table_set_col_width(table, 0, 120);
        lv_table_set_col_width(table, 1, 120);
        lv_table_set_col_width(table, 2, 120);
        {
            lv_obj_set_style_local_bg_opa(table, LV_TABLE_PART_BG, LV_STATE_DEFAULT, 255);
            lv_obj_set_style_local_bg_color(table, LV_TABLE_PART_BG, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
            lv_obj_set_style_local_border_width(table, LV_TABLE_PART_BG, LV_STATE_DEFAULT, 0);
            //标题
            {
                lv_obj_set_style_local_text_font(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, &lv_font_montserrat_16);
                lv_obj_set_style_local_text_letter_space(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 0);
                lv_obj_set_style_local_text_color(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
                //设置表格线
                lv_obj_set_style_local_border_side(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);
                lv_obj_set_style_local_border_width(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_border_color(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
                lv_obj_set_style_local_pad_left(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_right(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_top(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_bottom(table, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 1);
            }
            //电压
            {
                lv_obj_set_style_local_text_font(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, &lv_font_montserrat_16);
                lv_obj_set_style_local_text_letter_space(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 0);
                lv_obj_set_style_local_text_color(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, lv_color_make(0xff, 0x96, 0x00));
                //设置表格线
                lv_obj_set_style_local_border_side(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);
                lv_obj_set_style_local_border_width(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_border_color(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
                lv_obj_set_style_local_pad_left(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_right(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_top(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_bottom(table, LV_TABLE_PART_CELL2, LV_STATE_DEFAULT, 1);
            }
            //电流
            {
                lv_obj_set_style_local_text_font(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, &lv_font_montserrat_16);
                lv_obj_set_style_local_text_letter_space(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 0);
                lv_obj_set_style_local_text_color(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
                //设置表格线
                lv_obj_set_style_local_border_side(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, LV_BORDER_SIDE_FULL);
                lv_obj_set_style_local_border_width(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_border_color(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
                lv_obj_set_style_local_pad_left(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_right(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_top(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 1);
                lv_obj_set_style_local_pad_bottom(table, LV_TABLE_PART_CELL3, LV_STATE_DEFAULT, 1);
            }
        }
        lv_table_set_cell_value_fmt(table, 0, 0, "true");
        lv_table_set_cell_value_fmt(table, 0, 1, "read");
        lv_table_set_cell_value_fmt(table, 0, 2, "dac");
        lv_table_set_row_cnt(table, 30);
        uint8_t lineCount = 0;
        uint8_t i = 0;
        for(i = 0; i < ARRAY_COUNT(systemInfo.calib.vol); ++i) {
            if(systemInfo.calib.vol[i].valib != CALIB_VALIB) {
                break;
            }
            lv_table_set_cell_align(table, lineCount + i + 1, 0, LV_ALIGN_CENTER);
            lv_table_set_cell_align(table, lineCount + i + 1, 1, LV_ALIGN_CENTER);
            lv_table_set_cell_align(table, lineCount + i + 1, 2, LV_ALIGN_CENTER);
            lv_table_set_cell_type(table, lineCount + i + 1, 0, LV_TABLE_PART_CELL2);
            lv_table_set_cell_type(table, lineCount + i + 1, 1, LV_TABLE_PART_CELL2);
            lv_table_set_cell_type(table, lineCount + i + 1, 2, LV_TABLE_PART_CELL2);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 0, VOL_CALIB_FORM"V", systemInfo.calib.vol[i].trueVal_x);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 1, VOL_CALIB_FORM"V", systemInfo.calib.vol[i].adcVal_y);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 2, "%ld", systemInfo.calib.vol[i].dacVal_y);
        }
        lineCount += i;
        for(i = 0; i < ARRAY_COUNT(systemInfo.calib.amp); ++i) {
            if(systemInfo.calib.amp[i].valib != CALIB_VALIB) {
                break;
            }
            lv_table_set_cell_align(table, lineCount + i + 1, 0, LV_ALIGN_CENTER);
            lv_table_set_cell_align(table, lineCount + i + 1, 1, LV_ALIGN_CENTER);
            lv_table_set_cell_align(table, lineCount + i + 1, 2, LV_ALIGN_CENTER);
            lv_table_set_cell_type(table, lineCount + i + 1, 0, LV_TABLE_PART_CELL3);
            lv_table_set_cell_type(table, lineCount + i + 1, 1, LV_TABLE_PART_CELL3);
            lv_table_set_cell_type(table, lineCount + i + 1, 2, LV_TABLE_PART_CELL3);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 0, AMP_CALIB_FORM"A", systemInfo.calib.amp[i].trueVal_x);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 1, AMP_CALIB_FORM"A", systemInfo.calib.amp[i].adcVal_y);
            lv_table_set_cell_value_fmt(table, lineCount + i + 1, 2, "%ld", systemInfo.calib.amp[i].dacVal_y);
        }
        lineCount += i;
        lv_table_set_row_cnt(table, lineCount + 1);
        //设置大小与对齐
        lv_obj_set_size(UI_calibNode, 360, 200);
        lv_obj_align(UI_calibNode, ui.Back_cont_back, LV_ALIGN_CENTER, 0, 0);
    }
}

/*
 * @brief       void CalibPage_Exit(void)
 * @details     退出Menu页面
 */
void CalibPage_Exit(void)
{
    if(UI_calibNode != NULL) {
        lv_obj_del(UI_calibNode);
        UI_calibNode = NULL;
    }
}

