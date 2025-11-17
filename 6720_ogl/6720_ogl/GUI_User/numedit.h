#ifndef NUMEDIT_H
#define NUMEDIT_H

#include "lvgl.h"
#include "lv_port_indev.h"   // 提供 extern lv_group_t *encoder_group;

#ifdef __cplusplus
extern "C" {
#endif
//数值编辑器模块
typedef struct {
    lv_obj_t  *lab;            /* 目标标签 */

    int32_t    val;            /* 内部整数：真实值 * 10^dec */
    int32_t    vmin, vmax;     /* 上下限（内部整数单位） */

    uint8_t    dec;            /* 小数位 */
    uint8_t    int_min_digits; /* 整数最少显示位（前导0） */

    int8_t     digits_cnt;     /* 纯数字位数（不含小数点/符号） */
    int16_t    char_idx_map[16];
    int32_t    pow10_map[16];

    int32_t    sel_pow;        /* 当前选中位的 10^n */
    int8_t     sel_idx;        /* 当前选中位索引 */
    bool       editing;
} numedit_t;

/* 绑定标签与参数；会把 label 加入 encoder_group */
void numedit_init(numedit_t *ed,
                  lv_obj_t *label,
                  uint8_t dec,
                  int32_t vmin,
                  int32_t vmax,
                  uint8_t int_min_digits);

/* 内部整数的 get/set（会刷新标签显示） */
void     numedit_set_value(numedit_t *ed, int32_t v);
int32_t  numedit_get_value(const numedit_t *ed);

/* 键处理：非编辑态只有 trigger_key 会拉起编辑；编辑态吃掉左右上下/回车/ESC
   返回 true=已消费（不要再让外层处理），false=未消费 */
bool numedit_key(numedit_t *ed, lv_event_t *e, uint32_t trigger_key);

void numedit_bind_product(numedit_t *v, numedit_t *a, lv_obj_t *labW, int w_show_dec);
void numedit_unbind_product(void);
void numedit_bind_product_cap(numedit_t *v, numedit_t *a, lv_obj_t *labW, int w_show_dec, int32_t w_cap_real);


/* 结束 from 的编辑并立即开始 to 的编辑（to 可为 NULL，仅结束） */
void numedit_switch_edit(numedit_t *from, numedit_t *to);


#ifdef __cplusplus
}
#endif
#endif /* NUMEDIT_H */
