#include "MsgBox.h"


int32_t Msg_KeepTime = 0;


//用于发送时对比消息是否一样
Msg_Def thisMsg = {0};
static uint8_t __MsgBox_Check(Msg_Def *msg)
{
    if(msg == NULL) {
        return 0;
    }
    uint8_t flag = 0;
    //消息类型相同,同时内容相同,则不管
    if((msg->type == thisMsg.type)
            && ((msg->data.mult_msg == thisMsg.data.mult_msg) || (msg->data.msg == thisMsg.data.msg)))
    {
        flag = 1;
    }
    return flag;
}

void MsgBox_GroupCreate(void)
{
    {
        setup_scr_MsgBox(&ui);
        lv_obj_set_parent(ui.MsgBox_cont, ui.Back_cont_back);
        lv_obj_align(ui.MsgBox_cont, ui.Back_cont_back, LV_ALIGN_CENTER, 0, -20);
        lv_obj_set_hidden(ui.MsgBox_cont, 1);
        lv_obj_set_top(ui.MsgBox_cont, 1);
    }
    lv_obj_set_event_cb(ui.MsgBox_cont, MsgBox_Event_handler);
    //
    lv_label_set_long_mode(ui.MsgBox_btn_msg_label, LV_LABEL_LONG_SROLL);  //LV_LABEL_LONG_SROLL_CIRC
    extern lv_font_t MultFont_16;
    lv_obj_set_style_local_text_font(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
    lv_obj_set_size(ui.MsgBox_btn_msg_label, 320, 60);
    lv_label_set_align(ui.MsgBox_btn_msg_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_btn_msg, LV_ALIGN_CENTER, 0, 5);
    lv_obj_align(ui.MsgBox_btn_msg, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    //
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
    MsgBox_Exit();
}

void MsgBox_Exit(void)
{
    lv_obj_set_hidden(ui.MsgBox_cont, 1);
    Msg_KeepTime = -1;
    lv_label_set_text(ui.MsgBox_btn_msg_label, "");
    lv_obj_set_hidden(ui.MsgBox_img_error, 1);
    lv_obj_set_hidden(ui.MsgBox_img_tips, 1);
    lv_obj_set_hidden(ui.MsgBox_img_Warring, 1);
    lv_obj_set_hidden(ui.MsgBox_img_pass, 1);
}





/*
 * @brief       void IF_MsgBox_Tips(const char *str)
 * @details     弹出提示框
 */
void IF_MsgBox_Tips(const char *str)
{
    if(str == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TIPS_MSG;
    msg.data.msg = str;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
void IF_MsgBox_Tips_Mult(const MultStr_Def *multMsg)
{
    if(multMsg == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_TIPS_MULTMSG;
    msg.data.mult_msg = multMsg;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}

/*
 * @brief       void IF_MsgBox_Warring(const char *str,uint8_t* pflag)
 * @details     弹出警告框(需要Enter / Esc 关闭)
 */
void IF_MsgBox_Warring(const char *str, uint8_t *pflag)
{
    if(str == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_WARRING_MSG;
    msg.data.msg = str;
    msg.errorFlag = pflag;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
void IF_MsgBox_Warring_Mult(const MultStr_Def *multMsg, uint8_t *pflag)
{
    if(multMsg == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_WARRING_MULTMSG;
    msg.data.mult_msg = multMsg;
    msg.errorFlag = pflag;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
/*
 * @brief       void IF_MsgBox_Error(const char *str)
 * @details     弹出错误框(需要Enter / Esc 关闭)
 */
void IF_MsgBox_Error(const char *str, uint8_t *pflag)
{
    if(str == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_ERR_MSG;
    msg.data.msg = str;
    msg.errorFlag = pflag;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
void IF_MsgBox_Error_Mult(const MultStr_Def *multMsg, uint8_t *pflag)
{
    if(multMsg == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_ERR_MULTMSG;
    msg.data.mult_msg = multMsg;
    msg.errorFlag = pflag;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}





static void MsgBox_Warring(const char *msg)
{
    if(msg == NULL) {
        return ;
    }
    lv_obj_set_hidden(ui.MsgBox_img_Warring, 0);
    lv_label_set_text(ui.MsgBox_btn_msg_label, msg);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0x00));
    lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_obj_set_hidden(ui.MsgBox_cont, 0);
    Msg_KeepTime = 0;
}

static void MsgBox_Error(const char *msg)
{
    if(msg == NULL) {
        return ;
    }
    lv_obj_set_hidden(ui.MsgBox_img_error, 0);
    lv_label_set_text(ui.MsgBox_btn_msg_label, msg);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
    lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_obj_set_hidden(ui.MsgBox_cont, 0);
    Msg_KeepTime = 0;
}

static void MsgBox_Tips(const char *msg)
{
    if(msg == NULL) {
        return ;
    }
    lv_obj_set_hidden(ui.MsgBox_img_tips, 0);
    lv_label_set_text(ui.MsgBox_btn_msg_label, msg);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0xff));
    lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_obj_set_hidden(ui.MsgBox_cont, 0);
    Msg_KeepTime = 2000;
}



/*
 * @brief
 * @details     显示多国语言消息
 */
static void MsgBox_Warring_MultStr(const MultStr_Def *msg_multstr)
{
    if(msg_multstr == NULL) {
        return ;
    }
    MsgBox_Warring(MultStr_GetS(msg_multstr));
}

static void MsgBox_Error_MultStr(const MultStr_Def *msg_multstr)
{
    if(msg_multstr == NULL) {
        return ;
    }
    MsgBox_Error(MultStr_GetS(msg_multstr));
}

static void MsgBox_Tips_MultStr(const MultStr_Def *msg_multstr)
{
    if(msg_multstr == NULL) {
        return ;
    }
    MsgBox_Tips(MultStr_GetS(msg_multstr));
}





void IF_MsgBox_BatTester_Pass(const char *str)
{
    if(str == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BAT_TESTER_PASS_MSG;
    msg.data.msg = str;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
void IF_MsgBox_BatTester_Pass_Mult(const MultStr_Def *multMsg)
{
    if(multMsg == NULL) { return; }
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BAT_TESTER_PASS_MULTMSG;
    msg.data.mult_msg = multMsg;
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}


void IF_MsgBox_BatTester_Error(const char *str, uint8_t *pflag, const char *fmt, ...)
{
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BAT_TESTER_ERR_MSG;
    msg.data.msg = str;
    msg.errorFlag = pflag;
    if(fmt != NULL) {
        static char printf_buf[128];
        va_list args;
        int printed;
        va_start(args, fmt);
        printed = vsprintf(printf_buf, fmt, args);
        va_end(args);
        char *msg_malloc = NULL;
        msg_malloc = pvPortMalloc(printed + 1);
        if(msg_malloc != NULL) {
            memset(msg_malloc, 0, printed + 1);
            strcpy(msg_malloc, printf_buf);
            msg.msg_fmt = msg_malloc;
        }
    }
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}
void IF_MsgBox_BatTester_Error_Mult(const MultStr_Def *multMsg, uint8_t *pflag, const char *fmt, ...)
{
    Msg_Def msg = {0};
    __IO uint8_t result = 0;
    msg.type = MSG_TYPE_BAT_TESTER_ERR_MULTMSG;
    msg.data.mult_msg = multMsg;
    msg.errorFlag = pflag;
    if(fmt != NULL) {
        static char printf_buf[128];
        va_list args;
        int printed;
        va_start(args, fmt);
        printed = vsprintf(printf_buf, fmt, args);
        va_end(args);
        char *msg_malloc = NULL;
        msg_malloc = pvPortMalloc(printed + 1);
        if(msg_malloc != NULL) {
            memset(msg_malloc, 0, printed + 1);
            strcpy(msg_malloc, printf_buf);
            msg.msg_fmt = msg_malloc;
        }
    }
    if(__MsgBox_Check(&msg) != 0) {
        return ;
    }
    MsgQueue_Send(&msg);
}

static void MsgBox_BatTester_Error(Msg_Def *msg)
{
    if(msg == NULL) {
        return ;
    }
    if(msg->data.msg != NULL) {
        if(msg->msg_fmt == NULL) {
            lv_label_set_text(ui.MsgBox_btn_msg_label, msg->data.msg);
        } else {
            lv_label_set_text_fmt(ui.MsgBox_btn_msg_label, "%s%s", msg->data.msg, msg->msg_fmt);
            vPortFree(msg->msg_fmt);
        }
    } else
        if(msg->data.mult_msg != NULL) {
            if(msg->msg_fmt == NULL) {
                lv_label_set_text(ui.MsgBox_btn_msg_label, MultStr_GetS(msg->data.mult_msg));
            } else {
                lv_label_set_text_fmt(ui.MsgBox_btn_msg_label, "%s%s", MultStr_GetS(msg->data.mult_msg), msg->msg_fmt);
                vPortFree(msg->msg_fmt);
            }
        } else {
            return ;
        }
    lv_obj_set_hidden(ui.MsgBox_img_error, 0);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
    lv_obj_set_hidden(ui.MsgBox_cont, 0);
    Msg_KeepTime = 0;
}
static void MsgBox_BatTester_Error_MultStr(Msg_Def *msg)
{
    if(msg == NULL) {
        return ;
    }
    if(msg->data.mult_msg == NULL) {
        return ;
    }
    MsgBox_BatTester_Error(msg);
}


static void MsgBox_BatTester_Pass(const char *msg)
{
    if(msg == NULL) {
        return ;
    }
    lv_obj_set_hidden(ui.MsgBox_img_pass, 0);
    lv_label_set_text(ui.MsgBox_btn_msg_label, msg);
    lv_obj_align(ui.MsgBox_btn_msg_label, ui.MsgBox_cont, LV_ALIGN_CENTER, 20, 0);
    lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
    lv_obj_set_style_local_border_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0xFF, 0x00));
    lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_obj_set_hidden(ui.MsgBox_cont, 0);
    Msg_KeepTime = 2000;
}
static void MsgBox_BatTester_Pass_MultStr(const MultStr_Def *msg_multstr)
{
    if(msg_multstr == NULL) {
        return ;
    }
    MsgBox_BatTester_Pass(MultStr_GetS(msg_multstr));
}

/*
 * @brief       void MsgBox_Event_handler(lv_obj_t *obj, lv_event_t event)
 * @details     事件处理
 */
void MsgBox_Event_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            switch(thisMsg.type) {
                //                default :MsgBox_Exit();break;
                case MSG_TYPE_TIPS_MSG:
                case MSG_TYPE_TIPS_MULTMSG:
                case MSG_TYPE_BAT_TESTER_PASS_MSG:
                case MSG_TYPE_BAT_TESTER_PASS_MULTMSG:
                    MsgBox_Exit();
                    break;
                case MSG_TYPE_WARRING_MSG:
                case MSG_TYPE_WARRING_MULTMSG:
                case MSG_TYPE_ERR_MSG:
                case MSG_TYPE_ERR_MULTMSG:
                    switch(key) {
                        case LV_KEY_ESC:
                        case LV_KEY_ENTER:
                        case LV_KEY_ENCODER:
                        case LV_KEY_ENCODER_LONGP:
                            MsgBox_Exit();
                            break;
                    }
                    break;
                case MSG_TYPE_BAT_TESTER_ERR_MSG:
                case MSG_TYPE_BAT_TESTER_ERR_MULTMSG:
                    ;
                    break;
            }
            return ;
        }
        break;
    }
}



/*
 * @brief       static uint8_t GUI_Queue_MsgBox_Process(Msg_Def* msg)
 * @details     消息处理
 */
static uint8_t GUI_Queue_MsgBox_Process(Msg_Def *msg)
{
    if(ui.MsgBox_cont == NULL) {
        return 0;
    }
    memcpy(&thisMsg, msg, sizeof(Msg_Def));
    switch(msg->type)
    {
        //消息提示
        case MSG_TYPE_TIPS_MSG:
            MsgBox_Tips(msg->data.msg);
            break;
        case MSG_TYPE_WARRING_MSG:
            MsgBox_Warring(msg->data.msg);
            break;
        case MSG_TYPE_ERR_MSG:
            MsgBox_Error(msg->data.msg);
            break;
        case MSG_TYPE_TIPS_MULTMSG:
            MsgBox_Tips_MultStr(msg->data.mult_msg);
            break;
        case MSG_TYPE_WARRING_MULTMSG:
            MsgBox_Warring_MultStr(msg->data.mult_msg);
            break;
        case MSG_TYPE_ERR_MULTMSG:
            MsgBox_Error_MultStr(msg->data.mult_msg);
            break;
        //
        case MSG_TYPE_BAT_TESTER_PASS_MSG:
            MsgBox_BatTester_Pass(msg->data.msg);
            break;
        case MSG_TYPE_BAT_TESTER_PASS_MULTMSG:
            MsgBox_BatTester_Pass_MultStr(msg->data.mult_msg);
            break;
        case MSG_TYPE_BAT_TESTER_ERR_MSG:
            MsgBox_BatTester_Error(msg);
            break;
        case MSG_TYPE_BAT_TESTER_ERR_MULTMSG:
            MsgBox_BatTester_Error_MultStr(msg);
            break;
        default:
            return 0;
    }
    return 1;
}



/*
 * @brief       void MsgBox_Tick(uint16_t tickTime)
 * @details     消息窗口心跳(用于定时关闭)
 */
void MsgBox_Tick(uint16_t tickTime)
{
    if(0 == lv_obj_get_hidden(ui.MsgBox_cont))
    {
        static uint16_t timeCount = 0;
        switch(thisMsg.type) {
            case MSG_TYPE_BAT_TESTER_ERR_MSG:
            case MSG_TYPE_BAT_TESTER_ERR_MULTMSG: {
                if(timeCount == 0) {
                    static uint8_t flag = 0;
                    flag = !flag;
                    if(flag) {
                        lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFAA00));
                        lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x222222));
                    } else {
                        lv_obj_set_style_local_bg_color(ui.MsgBox_cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFF6600));
                        lv_obj_set_style_local_text_color(ui.MsgBox_btn_msg_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x444444));
                    }
                    BEEP_BAT_TESTER_ERR();
                }
                if(timeCount < 200) {
                    timeCount += tickTime;
                } else {
                    timeCount = 0;
                }
            }
            break;
            default:
                timeCount = 0;
                break;
        }
    }
    //当标志位为0时,清除弹窗
    if(thisMsg.type != 0) {
        if(thisMsg.errorFlag != NULL) {
            if(*thisMsg.errorFlag == 0) {
                MsgBox_Exit();
            }
        }
    }
    if(Msg_KeepTime > 0) {
        Msg_KeepTime -= tickTime;
        if(Msg_KeepTime <= 0) {
            Msg_KeepTime = 0;
            MsgBox_Exit();
        }
    }
    //显示剩余消息
    uint8_t length = MsgQueue_Length() + 1;
    lv_label_set_text_fmt(ui.MsgBox_btn_msgLen_label, "1/%d", length);
    //获取新消息
    if(0 != lv_obj_get_hidden(ui.MsgBox_cont)) {
        Msg_Def msg_now = {0};
        if(0 != MsgQueue_Rec(&msg_now)) {
            if(__MsgBox_Check(&msg_now) == 0) {
                GUI_Queue_MsgBox_Process(&msg_now);
            }
        } else {
            memset(&thisMsg, 0, sizeof(thisMsg));
        }
    }
}

