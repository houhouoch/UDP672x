#include "gui_custom.h"
#include <string.h>
#include <stdio.h>
#include <lvgl.h>

/* ========= 你工程里已有的 group 和 ui ========= */
extern lv_group_t * encoder_group;

/* ========= 你自定义的键值（来自你的 enum） =========
 * 这里不去包含你那个枚举头，直接用名字。若编译器报未定义，
 * 就说明你没把该枚举放到全局头文件里，让此处可见。
 */

/* ========= 模块内部参数 ========= */
static lv_group_t *s_group   = NULL;
static lv_obj_t   *s_label   = NULL;

static int32_t  s_val        = 0;      // 内部整数值（两位小数时 1234 → 12.34）
static int32_t  s_min        = -1000;
static int32_t  s_max        =  5000;
static int32_t  s_step       =  1;     // 基础步进
static int32_t  s_accel_mul  = 10;     // 加速倍数（用于 *_LONGP）
static uint8_t  s_dec_places =  2;     // 小数位
static char     s_unit[12]   = " ";

/* ========= 小工具 ========= */
static inline int32_t pow10_u8(uint8_t n){ int32_t p=1; while(n--) p*=10; return p; }

static void make_focusable(lv_obj_t *obj)
{
    // 用你有的 flags：点击即可获得焦点；滚动时自动带入视野
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
}

static void label_update_text(void)
{
    if(!s_label) return;
    char buf[64];

    if(s_dec_places == 0) {
        lv_snprintf(buf, sizeof(buf), "%ld%s", (long)s_val, s_unit);
    } else {
        int32_t base = pow10_u8(s_dec_places);
        int32_t v = s_val;
        int neg = v < 0;
        int32_t absv = neg ? -v : v;
        int32_t ip = absv / base;
        int32_t fp = absv % base;

        char frac_fmt[8];
        lv_snprintf(frac_fmt, sizeof(frac_fmt), "%%0%uld", (unsigned)s_dec_places);

        char frac_buf[16];
        lv_snprintf(frac_buf, sizeof(frac_buf), frac_fmt, (long)fp);

        if(neg) lv_snprintf(buf, sizeof(buf), "-%ld.%s%s", (long)ip, frac_buf, s_unit);
        else    lv_snprintf(buf, sizeof(buf),  "%ld.%s%s", (long)ip, frac_buf, s_unit);
    }
    lv_label_set_text(s_label, buf);
}

/* ========= 事件回调：吃键盘/编码器键 ========= */
static void label_key_cb(lv_event_t *e)
{
    if(!s_label || !s_group) return;
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    uint32_t key = lv_event_get_key(e);
    bool changed = false;

    // 根据键位决定步进，支持 *_LONGP 加速
    int32_t step = s_step;
    switch(key){
        case LV_KEY_ENCODER:
            if(s_accel_mul > 1) {
                if(step > INT32_MAX / s_accel_mul) step = INT32_MAX;
                else step *= s_accel_mul;
            }
            break;
        default:
            break;
    }

    // 小数放大处理（内部整数单位）
    if(s_dec_places > 0) {
        int32_t base = pow10_u8(s_dec_places);
        if(step > INT32_MAX / base) step = INT32_MAX;
        else step *= base;
    }

    switch(key)
    {
        // 进入编辑态/选中（用你的 M1 作为“实体编辑键”）
        case LV_KEY_M1:
            lv_group_focus_obj(s_label);
            lv_group_set_editing(s_group, true);
            break;

        // 加
        case LV_KEY_UP:
        {
            if(s_val < s_max) {
                int32_t nv = s_val + step;
                s_val = (nv > s_max) ? s_max : nv;
                changed = true;
            }
        } break;

        // 减
        case LV_KEY_DOWN:
        {
            if(s_val > s_min) {
                int32_t nv = s_val - step;
                s_val = (nv < s_min) ? s_min : nv;
                changed = true;
            }
        } break;

        // 确认/退出
        case LV_KEY_ENTER:
            lv_group_set_editing(s_group, false);
            // TODO: 在这里提交 s_val 给业务层（如需）
            break;

        case LV_KEY_ESC:
            lv_group_set_editing(s_group, false);
            // TODO: 若想“取消恢复原值”，自己加个备份值，退出时还原
            break;

        default:
            break;
    }

    if(changed) label_update_text();
}

/* ========= 对外 API ========= */
void label_encoder_init_bind(lv_group_t *group, lv_obj_t *label)
{
    s_group = group;
    s_label = label;
    if(!s_group || !s_label) return;

    make_focusable(s_label);
    lv_obj_add_event_cb(s_label, label_key_cb, LV_EVENT_KEY, NULL);

    // 确保目标在组里
    lv_group_add_obj(s_group, s_label);

    // 初次刷新
    label_update_text();
}

void label_encoder_rebind(lv_obj_t *new_label)
{
    if(!s_group || !new_label) return;
    s_label = new_label;
    make_focusable(s_label);
    lv_obj_add_event_cb(s_label, label_key_cb, LV_EVENT_KEY, NULL);
    lv_group_add_obj(s_group, s_label);
    label_update_text();
}

void label_encoder_set_range(int32_t vmin, int32_t vmax)
{
    s_min = vmin; s_max = vmax;
    if(s_val < s_min) s_val = s_min;
    if(s_val > s_max) s_val = s_max;
    label_update_text();
}

void label_encoder_set_step(int32_t base_step, int32_t accel_factor)
{
    if(base_step <= 0) base_step = 1;
    if(accel_factor < 1) accel_factor = 1;
    s_step = base_step;
    s_accel_mul = accel_factor;
}

void label_encoder_set_format(uint8_t dec_places, const char *unit_suffix)
{
    s_dec_places = dec_places;
    if(unit_suffix){
        strncpy(s_unit, unit_suffix, sizeof(s_unit)-1);
        s_unit[sizeof(s_unit)-1] = '\0';
    }
    label_update_text();
}

void label_encoder_set_value(int32_t v)
{
    s_val = v;
    if(s_val < s_min) s_val = s_min;
    if(s_val > s_max) s_val = s_max;
    label_update_text();
}

int32_t label_encoder_get_value(void)
{
    return s_val;
}
