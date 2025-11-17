#ifndef gui_custom
#define gui_custom

#include "lvgl.h"
#include <stdint.h>
#include <stdbool.h>

/** 用法
 * 1) GUI创建完成后：
 *      label_encoder_init_bind(encoder_group, target_label);
 * 2) 可选参数：
 *      label_encoder_set_range(-5000, 5000);   // 内部整数范围（两位小数→ -50.00~50.00）
 *      label_encoder_set_step(1, 10);          // 基础步进=1，加速倍数=10（用于 LONGP）
 *      label_encoder_set_format(2, " V");      // 两位小数+单位
 *      label_encoder_set_value(1234);          // 初始显示 12.34 V
 * 3) 键值（用你的自定义）：
 *      进入编辑/选中：LV_KEY_M1
 *      加/减：LV_KEY_UP/DOWN 或 LV_KEY_LEFT/RIGHT
 *      快速加/减：LV_KEY_RIGHT_LONGP / LV_KEY_LEFT_LONGP / LV_KEY_UP_LONGP / LV_KEY_DOWN_LONGP
 *      确认/退出：LV_KEY_ENTER / LV_KEY_ESC
 */

void     label_encoder_init_bind(lv_group_t *group, lv_obj_t *label);
void     label_encoder_rebind(lv_obj_t *new_label);

void     label_encoder_set_range(int32_t vmin, int32_t vmax);
void     label_encoder_set_step(int32_t base_step, int32_t accel_factor);
void     label_encoder_set_format(uint8_t dec_places, const char *unit_suffix);
void     label_encoder_set_value(int32_t v);
int32_t  label_encoder_get_value(void);

#endif // LABEL_ENCODER_EDIT_H
