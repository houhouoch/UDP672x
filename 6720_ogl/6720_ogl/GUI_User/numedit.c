#include "numedit.h"
#include <string.h>
#include <stdio.h>
#include "power_ctrl.h"
#include "Gui_Task.h"
/* Forward declaration for product auto-update */
static inline void numedit__product_try_update_cap(void);
static int32_t cap_adjust_candidate(numedit_t *ed, int32_t cand);


//高亮样式
static lv_style_t style_sel_bg;
static void init_sel_style_once(void){
    static bool inited=false; if(inited) return; inited=true;
    lv_style_init(&style_sel_bg);
    lv_style_set_bg_opa(&style_sel_bg, LV_OPA_50);
    lv_style_set_bg_color(&style_sel_bg, lv_color_hex(0xFF6D00));
    lv_style_set_text_color(&style_sel_bg, lv_color_hex(0xFFFFFF));
    lv_style_set_border_width(&style_sel_bg, 0);
    lv_style_set_outline_width(&style_sel_bg, 0);
    lv_style_set_shadow_width(&style_sel_bg, 0);
}


static inline int32_t p10_u8(uint8_t n){ int32_t p=1; while(n--) p*=10; return p; }

//如果不在编辑或索引越界：清除选区；
static void apply_selection(numedit_t *ed){
    if(!ed || !ed->lab) return;
    if(!ed->editing || ed->digits_cnt<=0 || ed->sel_idx<0 || ed->sel_idx>=ed->digits_cnt){
        lv_label_set_text_sel_start(ed->lab, LV_LABEL_TEXT_SELECTION_OFF);
        lv_label_set_text_sel_end  (ed->lab, LV_LABEL_TEXT_SELECTION_OFF);
        return;
    }
    int16_t ch = ed->char_idx_map[ed->sel_idx];
    lv_label_set_text_sel_start(ed->lab, ch);
    lv_label_set_text_sel_end  (ed->lab, ch+1);
}


static void render_plain_and_map(numedit_t *ed){
    if(!ed || !ed->lab) return;

    char out[64]; int k=0;
    int32_t base = p10_u8(ed->dec);
    int sign = (ed->val < 0) ? -1 : 1;
    int32_t absv = (ed->val < 0)? -ed->val : ed->val;

  //内部数值拆分成 整数ip 小数fp 
    int32_t ip = absv / base;
    int32_t fp = absv % base;

    char intbuf[32];
    lv_snprintf(intbuf, sizeof(intbuf), "%ld", (long)ip);
    int intlen = (int)strlen(intbuf);

    char fracbuf[16] = {0};
    if(ed->dec){
        char fmt[8]; lv_snprintf(fmt,sizeof(fmt),"%%0%uld",(unsigned)ed->dec);
        lv_snprintf(fracbuf,sizeof(fracbuf),fmt,(long)fp);
    }
//计算 整数最小位数 --补0
    int pad_n = 0;
    if(intlen < ed->int_min_digits)
      pad_n = ed->int_min_digits - intlen;

    ed->digits_cnt = 0;
    if(sign < 0) out[k++]='-';

    int total_int = pad_n + intlen;
    int cur = 0;
    for(int p=0;p<total_int;p++){
        char ch = (p<pad_n)? '0' : intbuf[p-pad_n];
        ed->pow10_map[cur]    = p10_u8(ed->dec + (total_int-1 - p));
        ed->char_idx_map[cur] = k;
        ed->digits_cnt++;
        out[k++] = ch;
        cur++;
    }

    if(ed->dec){
        out[k++]='.';
        for(int j=0;j<ed->dec;j++){
            ed->pow10_map[cur]    = p10_u8(ed->dec-1-j);
            ed->char_idx_map[cur] = k;
            ed->digits_cnt++;
            out[k++] = fracbuf[j];
            cur++;
        }
    }

    out[k] = '\0';
    lv_label_set_recolor(ed->lab,false);
    lv_label_set_text(ed->lab,out);

    if(ed->sel_pow){
        for(int i=0;i<ed->digits_cnt;i++){
            if(ed->pow10_map[i]==ed->sel_pow){ ed->sel_idx=i; break; }
        }
    }
    apply_selection(ed);
}

static int32_t label_to_internal(lv_obj_t *lbl, uint8_t dec){
    const char *s = lv_label_get_text(lbl);
    int sign = 1;
    int32_t ip = 0, fp = 0;
    int fp_d = 0;
    bool seen_dot = false;

    for(const char *p=s; *p; p++){
        if(*p=='-'){ sign=-1; continue; }
        if(*p=='.'){ seen_dot=true; continue; }
        if(*p<'0' || *p>'9') continue;
        int d = *p - '0';
        if(!seen_dot) ip = ip*10 + d;
        else if(fp_d < dec){ fp = fp*10 + d; fp_d++; }
    }
    while(fp_d < dec){ fp *= 10; fp_d++; }

    int32_t base = p10_u8(dec);
    return sign * (ip * base + fp);
}

static void move_sel(numedit_t *ed, int step){
    if(!ed || ed->digits_cnt<=0) return;
    ed->sel_idx += step;
    if(ed->sel_idx < 0) ed->sel_idx = 0;
    if(ed->sel_idx > ed->digits_cnt-1) ed->sel_idx = ed->digits_cnt-1;
    ed->sel_pow = ed->pow10_map[ed->sel_idx];
    apply_selection(ed);
}

static void bump_digit(numedit_t *ed, int dir){
    if(!ed || ed->digits_cnt<=0) return;

    int32_t delta = ed->sel_pow ? ed->sel_pow : p10_u8(ed->dec);
    int sign = (ed->val<0)? -1:1;
    int32_t absv = (ed->val<0)? -ed->val:ed->val;

    if(dir>0){
        if(absv <= INT32_MAX - delta) absv += delta;
    }else{
        absv = (absv>=delta)? (absv-delta) : 0;
    }
    int32_t nv = sign*absv;

    if(nv > ed->vmax) nv = ed->vmax;
    if(nv < ed->vmin) nv = ed->vmin;
    
    nv = cap_adjust_candidate(ed, nv);
    
    ed->val = nv;
    render_plain_and_map(ed);
    //插入
    numedit__product_try_update_cap();
}

static void start_edit(numedit_t *ed){
    if(!ed || !ed->lab || ed->editing) return;

    init_sel_style_once();
    // 给选区添加样式（加在 SELECTED 部位）
    lv_obj_add_style(ed->lab, &style_sel_bg, LV_PART_SELECTED);
    
    /* 1) 从标签当前文本解析出内部整数 */
    ed->val     = label_to_internal(ed->lab, ed->dec);

    /* 2) 默认选中“个位” */
  ed->sel_pow = p10_u8(ed->dec);//p10_u8(ed->dec+1):选中十位
    ed->sel_idx = 0;

    /* 3) 进入编辑态（不抢焦点！焦点继续留在你的 focuser 上） */
    ed->editing = true;
    if(encoder_group) lv_group_set_editing(encoder_group, true);

    /* 4) 渲染+高亮当前位 */
    render_plain_and_map(ed);
}


static void end_edit(numedit_t *ed){
    if(!ed) return;

    ed->editing = false;

    /* 清除标签的选择高亮 */
    lv_label_set_text_sel_start(ed->lab, LV_LABEL_TEXT_SELECTION_OFF);
    lv_label_set_text_sel_end  (ed->lab, LV_LABEL_TEXT_SELECTION_OFF);
  //插入
    numedit__product_try_update_cap();
    /* 退出编辑态（仍然不动焦点） */
    if(encoder_group) lv_group_set_editing(encoder_group, false);
}


void numedit_init(numedit_t *ed,
                  lv_obj_t *label,
                  uint8_t dec,
                  int32_t vmin,
                  int32_t vmax,
                  uint8_t int_min_digits)
{
    memset(ed, 0, sizeof(*ed));
    ed->lab            = label;
    ed->dec            = dec;
    ed->vmin           = vmin;
    ed->vmax           = vmax;
    ed->int_min_digits = int_min_digits;

    lv_obj_add_flag(ed->lab, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);

    ed->val = label_to_internal(ed->lab, ed->dec);
    render_plain_and_map(ed);

    if(encoder_group) lv_group_add_obj(encoder_group, ed->lab);
}

void numedit_set_value(numedit_t *ed, int32_t v){
    if(!ed) return;
    if(v < ed->vmin) v = ed->vmin;
    if(v > ed->vmax) v = ed->vmax;
  
    v = cap_adjust_candidate(ed, v);
  
    ed->val = v;
    render_plain_and_map(ed);
  //插入
  numedit__product_try_update_cap();
}

int32_t numedit_get_value(const numedit_t *ed){
    return ed ? ed->val : 0;
}

bool numedit_key(numedit_t *ed, lv_event_t *e, uint32_t trigger_key){
    if(!ed || !e) return false;
    if(lv_event_get_code(e) != LV_EVENT_KEY) return false;

    uint32_t key = lv_event_get_key(e);

    if(ed->editing){
        switch(key){
        case LV_KEY_LEFT:   move_sel(ed, -1); lv_event_stop_bubbling(e); return true;
        case LV_KEY_RIGHT:  move_sel(ed, +1); lv_event_stop_bubbling(e); return true;
        case LV_KEY_UP:     bump_digit(ed, +1); lv_event_stop_bubbling(e); return true;
        case LV_KEY_DOWN:   bump_digit(ed, -1); lv_event_stop_bubbling(e); return true;         
        case LV_KEY_ENTER: 
        case LV_KEY_ENCODER:
        end_edit(ed);      lv_event_stop_bubbling(e); return true;
        case LV_KEY_ESC:    end_edit(ed);      lv_event_stop_bubbling(e); return true;
        default:
          //再次按下相同的按键  取消编辑
            if(key == trigger_key){ end_edit(ed); lv_event_stop_bubbling(e); return true; }
            return false;
        }
    }else{
        if(key == trigger_key){
            start_edit(ed);
            lv_event_stop_bubbling(e);
            return true;
        }
        return false;
    }
}

#include <inttypes.h>
/* ================================================
 *   V*A 联动 + 最大乘积上限
 * ================================================ */
typedef struct {
    numedit_t *v;        // V 编辑器
    numedit_t *a;        // A 编辑器
    lv_obj_t  *labW;     // W 标签
    int        show_dec; // W 显示的小数位（固定值，如 2）
    int32_t    cap_real; // 乘积上限（实数部分），比如 180
    bool       enabled;
} numedit_prod_cap_t;

static numedit_prod_cap_t s_pc = {0};

/* 把 value(10^src_dec) -> 文本（固定 show_dec 小数位，四舍五入） */
static void fixed_to_text_w(char *buf, size_t n,
                            int64_t value, int src_dec,
                            int show_dec, int min_int_width)
{
    if (show_dec < 0) show_dec = 0;
    if (min_int_width < 1) min_int_width = 1;

    int64_t v = value;

    /* 先把 v 从 10^src_dec 换到 10^show_dec，并完成四舍五入 */
    if (src_dec > show_dec) {
        int64_t div  = p10_u8(src_dec - show_dec);
       v = v / div;
      //四舍五入的操作
//        int64_t half = div / 2;
//        v = (v >= 0) ? (v + half) / div : (v - half) / div;
    } else if (src_dec < show_dec) {
        int64_t mul = p10_u8(show_dec - src_dec);
        v = v * mul;
    }

    int64_t absv = (v < 0) ? -v : v;
    int64_t ip, fp = 0;
    if (show_dec > 0) {
        int64_t base = p10_u8(show_dec);
        ip = absv / base;
        fp = absv % base;
        lv_snprintf(buf, n, "%s%0*lld.%0*lld",
                    (v < 0) ? "-" : "",
                    min_int_width, (long long)ip,
                    show_dec,      (long long)fp);
    } else {
        ip = absv;
        lv_snprintf(buf, n, "%s%0*lld",
                    (v < 0) ? "-" : "",
                    min_int_width, (long long)ip);
    }
}


/* ========== 180 上限的“护栏判断 + 夹紧” ========== */
/* 若把 ed 改为 cand 会超上限，则把 cand 夹到允许的最大值；否则原样返回 */
static int32_t cap_adjust_candidate(numedit_t *ed, int32_t cand)
{
    if(!s_pc.enabled || (!s_pc.v) || (!s_pc.a)) return cand;
    if(ed != s_pc.v && ed != s_pc.a) return cand;

    /* 当前另一侧的值 */
    int32_t v_int = numedit_get_value(s_pc.v);
    int32_t a_int = numedit_get_value(s_pc.a);
    int dv = s_pc.v->dec;
    int da = s_pc.a->dec;

    /* 180 * 10^(dv+da) */
    int64_t cap_scaled = (int64_t)s_pc.cap_real;
    for(int i=0;i<dv+da;i++) cap_scaled *= 10;

    /* 用候选值替换正在编辑的那一侧，检查是否越界 */
    int64_t V = (ed == s_pc.v) ? (int64_t)cand : (int64_t)v_int;
    int64_t A = (ed == s_pc.a) ? (int64_t)cand : (int64_t)a_int;

    /* 允许负号，但一般你是非负范围：统一用绝对值做约束 */
    int64_t VV = (V<0)? -V:V;
    int64_t AA = (A<0)? -A:A;

    if(VV == 0 || AA == 0) return cand;              // 乘积为 0，必然不超
    if(VV * AA <= cap_scaled) return cand;           // 没超，直接用

    /* 需要夹紧：给出“最大允许值”（保持 cand 的符号） */
    int sign = (cand < 0) ? -1 : 1;
    if(ed == s_pc.a){
        int64_t vmax = VV;                            // V 固定
        if(vmax == 0) return cand;
        int64_t a_max = cap_scaled / vmax;            // floor
        if(a_max < 0) a_max = 0;
        /* 不跨越你自己的 vmin/vmax，交给后续已有的范围夹紧处理 */
        int64_t out = sign * a_max;
        if(out > INT32_MAX) out = INT32_MAX;
        if(out < INT32_MIN) out = INT32_MIN;
        return (int32_t)out;
    }else{ /* ed == s_pc.v */
        int64_t amax = AA;                            // A 固定
        if(amax == 0) return cand;
        int64_t v_max = cap_scaled / amax;            // floor
        if(v_max < 0) v_max = 0;
        int64_t out = sign * v_max;
        if(out > INT32_MAX) out = INT32_MAX;
        if(out < INT32_MIN) out = INT32_MIN;
        return (int32_t)out;
    }
}

/* ========== W = V*A 的联动刷新（已被护栏保证 ≤ 上限） ========== */
/* W = V * A 刷新（动态小数位 + 个位数补0；保持乘积≤上限的护栏已在别处生效） */
/* W = V * A 刷新（动态小数位 + 个位数补0；保持乘积≤上限的护栏已在别处生效） */
/* W = V * A 刷新（>100 一位小数；否则两位；个位补0） */
static void product_update_W(void)
{
    if (!s_pc.enabled || !s_pc.labW || !s_pc.v || !s_pc.a) return;

    int32_t v_int = numedit_get_value(s_pc.v);
    int32_t a_int = numedit_get_value(s_pc.a);
    int dv = s_pc.v->dec;
    int da = s_pc.a->dec;

    /* 乘积的定点值；小数位相加 */
    int64_t w_int = (int64_t)v_int * (int64_t)a_int;
    int     w_dec = dv + da;

    /* 取绝对值的整数部分（不含小数）用于判断显示规则 */
    int64_t absv   = (w_int < 0) ? -w_int : w_int;
    int64_t denom  = (w_dec > 0) ? p10_u8(w_dec) : 1;
    int64_t ip_abs = (w_dec > 0) ? (absv / denom) : absv;

    /* 显示规则：
       - s_pc.show_dec >= 0: 固定小数位（优先）
       - 否则：ip >= 100 -> 1 位小数；否则 2 位小数 */
    int show_dec = (s_pc.show_dec >= 0)
                   ? s_pc.show_dec
                   : ((ip_abs >= 100) ? 1 : 2);

    /* 个位数补0：整数位 0~9 -> 宽度=2；否则宽度=1 */
    int min_int_width = (ip_abs < 10) ? 2 : 1;

    char buf[32];
    fixed_to_text_w(buf, sizeof(buf), w_int, w_dec, show_dec, min_int_width);
    lv_label_set_text(s_pc.labW, buf);
}


/* 给上述第 3 步里插入的调用 */
static inline void numedit__product_try_update_cap(void)
{
    if(!s_pc.enabled) return;

    /* —— 护栏一步：把“刚刚改过的那个 ed->val”再夹一次，防止超过 180 —— */
    // 注意：我们在 bump_digit()/set_value() 内已经先做了范围夹紧，
    // 这里再做一次是兜底（如果你在别处改了 ed->val 也能被兜住）。

    /* 刷新 W */
    product_update_W();
  //实时更新电压
  if(OUT_ONOFF_led_on){    
    //旋钮改电压/电流标签时（输出打开才判断）
    power_update_cc_cv_leds();
  //  power_apply_voltage_from_label();
  }
}

/* ========== 对外 API：绑定 / 解绑 ========== */
void numedit_bind_product_cap(numedit_t *v, numedit_t *a, lv_obj_t *labW, int w_show_dec, int32_t w_cap_real)
{
    s_pc.v = v;
    s_pc.a = a;
    s_pc.labW = labW;
    s_pc.show_dec = w_show_dec; // 固定小数位；建议 2
    s_pc.cap_real = (w_cap_real <= 0) ? 180 : w_cap_real;
    s_pc.enabled = (v && a && labW);

    if(s_pc.labW){
        /* 初始显示 */
        lv_label_set_text(s_pc.labW, "00.00");
    }
    /* 不立即算；等 V/A 第一次变化后刷新 */
}

void numedit_unbind_product_cap(void)
{
    s_pc.v = s_pc.a = NULL;
    s_pc.labW = NULL;
    s_pc.show_dec = 0;
    s_pc.cap_real = 0;
    s_pc.enabled = false;
}



void numedit_switch_edit(numedit_t *from, numedit_t *to)
{
    if (from && from->editing) {
        end_edit(from);   /* 提交当前值、清除选区高亮、联动刷新 */
    }
    if (to) {
        start_edit(to);   /* 选中 to 并进入编辑（默认光标在个位） */
    }
}

