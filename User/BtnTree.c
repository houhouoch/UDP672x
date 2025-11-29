#include "BtnTree.h"
#include "BtnTree_Limit.h"


typedef struct {
    Tree_Def *curNode;      //当前树节点(显示)
    Tree_Def *selNode;      //选择树节点(仅lv_obj_t对象)
    Tree_Def *uiNode;       //UI树节点
} Tree_UI_Def;
static Tree_UI_Def tree_ui = {0};


const struct BtnInfo_Def btn_enter = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_ENTER,    .key_long = LV_KEY_ENTER,  .multStr = &mStr_Enter,
};  //Enter
const struct BtnInfo_Def btn_esc = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_ESC,    .key_long = LV_KEY_ESC,  .multStr = &mStr_Return,
};  //Esc



const struct BtnInfo_Def btn_left = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LEFT,      .key_long = LV_KEY_LEFT,    .multStr = &mStr_Left,
};  //←
const struct BtnInfo_Def btn_right =  {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_RIGHT,     .key_long = LV_KEY_RIGHT,   .multStr = &mStr_Right,
};  //→
const struct BtnInfo_Def btn_up = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_UP,        .key_long = LV_KEY_UP,      .multStr = &mStr_Up,
};   //增加
const struct BtnInfo_Def btn_down = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_DOWN,      .key_long = LV_KEY_DOWN,    .multStr = &mStr_Down,
};   //减少



const struct BtnInfo_Def btn_on = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_ON,    .key_long = LV_KEY_ON,  .multStr = &mStr_ON,
};  //开启

const struct BtnInfo_Def btn_off = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_OFF,    .key_long = LV_KEY_OFF,  .multStr = &mStr_OFF,
};  //关闭


const struct BtnInfo_Def btn_start = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_START,    .key_long = LV_KEY_START,  .multStr = &mStr_Start,
};  //开始
const struct BtnInfo_Def btn_contiune = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_CONTIUNE,  .key_long = LV_KEY_CONTIUNE,  .multStr = &mStr_Contiune,
};  //继续
const struct BtnInfo_Def btn_stop = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_STOP,      .key_long = LV_KEY_STOP,  .multStr = &mStr_Stop,
};  //停止
const struct BtnInfo_Def btn_pause = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_PAUSE,    .key_long = LV_KEY_PAUSE,  .multStr = &mStr_Pause,
};  //开始



/*
 * @brief       虚拟键盘输入
 * @details
 */
const struct BtnInfo_Def btn_Upper = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_UPPER, .key_long = LV_KEY_UPPER,  .multStr = &mStr_Upper,
};
const struct BtnInfo_Def btn_Lower = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOWER, .key_long = LV_KEY_LOWER,  .multStr = &mStr_Lower,
};
const struct BtnInfo_Def btn_Number = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_NUMBER, .key_long = LV_KEY_NUMBER,  .multStr = &mStr_Number,
};


/*
 * @brief       文件操作
 * @details
 */
//删除文件(长按)
const struct BtnInfo_Def btn_file_delete = {
    .type = BTN_TYPE_KEY,   .key_short = LV_KEY_DEFAULT,    .key_long = LV_KEY_DELETE,      .multStr = &mStr_delete,
};
//重命名
const struct BtnInfo_Def btn_file_rename = {
    .type = BTN_TYPE_KEY,   .key_short = LV_KEY_RENAME,     .key_long = LV_KEY_RENAME,      .multStr = &mStr_rename,
};
//保存于内部存储器
const struct BtnInfo_Def btn_file_save_flash = {
    .type = BTN_TYPE_KEY,   .key_short = LV_KEY_SAVE_FLASH, .key_long = LV_KEY_SAVE_FLASH,  .multStr = &mStr_save_Flash,
};
//保存于USB存储器
const struct BtnInfo_Def btn_file_save_udisk = {
    .type = BTN_TYPE_KEY,   .key_short = LV_KEY_SAVE_UDISK, .key_long = LV_KEY_SAVE_UDISK,  .multStr = &mStr_save_UDisk,
};



/*!
 * @brief   void Tree_Print(Tree_Def* tree,uint16_t deepth)
 *          打印树
 * @param   tree:树;deepth:显示深度
 */
void Tree_Print(Tree_Def *tree, uint16_t deepth)
{
    if(tree != NULL)
    {
        for(uint16_t i = 0; i < deepth; ++i)
        {
            Tree_Printf("    ");
        }
        if(tree->pdata != NULL)
        {
            Tree_Printf("%s\r\n", MultStr_GetS(((const struct BtnInfo_Def *)tree->pdata)->multStr));
        }
        if(tree->child != NULL) {
            Tree_Print(tree->child, deepth + 1);
        }
        if(tree->next != NULL) {
            Tree_Print(tree->next, deepth);
        }
    }
}


Tree_Def *Tree_UI_Set_EventCb(Tree_Def *tree);




#ifdef HAOYI_VER
//主页
//输出电压设置
const struct BtnInfo_Def btn_VSet = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Vout_Set,
    .evencb = volSet_handler,
    .multStr = &mStr_home_VSet,
};
//输出电流设置
const struct BtnInfo_Def btn_ISet = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Iout_Set,
    .evencb = ampSet_handler,
    .multStr = &mStr_home_ISet,
};
//电压限制
const struct BtnInfo_Def btn_Vlimit = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_OVP_Set,
    .evencb = volLimit_handler,
    .multStr = &mStr_home_Vlimit,
};
//电流限制
const struct BtnInfo_Def btn_Ilimit = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_OCP_Set,
    .evencb = ampLimit_handler,
    .multStr = &mStr_home_Ilimit,
};


//定时关闭
const struct BtnInfo_Def btn_TimeOff = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Time_Set,
    .evencb = TimeOff_handler,
    .multStr = &mStr_home_TimeOff,
};

//输出电压设置
const struct BtnInfo_Def btn_VSet_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_Vset,
    .evencb = volSet_handler,
    .multStr = &mStr_home_VSet,
};
//输出电流设置
const struct BtnInfo_Def btn_ISet_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_Iset,
    .evencb = ampSet_handler,
    .multStr = &mStr_home_ISet,
};
//电压限制
const struct BtnInfo_Def btn_Vlimit_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_OVP,
    .evencb = volLimit_handler,
    .multStr = &mStr_home_Vlimit,
};
//电流限制
const struct BtnInfo_Def btn_Ilimit_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_OCP,
    .evencb = ampLimit_handler,
    .multStr = &mStr_home_Ilimit,
};


//定时关闭
const struct BtnInfo_Def btn_TimeOff_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_timeOff,
    .evencb = TimeOff_handler,
    .multStr = &mStr_home_TimeOff,
};
#else
//主页
//输出电压设置
const struct BtnInfo_Def btn_VSet = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_Vset,
    .evencb = volSet_handler,
    .multStr = &mStr_home_VSet,
};
//输出电流设置
const struct BtnInfo_Def btn_ISet = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_Iset,
    .evencb = ampSet_handler,
    .multStr = &mStr_home_ISet,
};
//电压限制
const struct BtnInfo_Def btn_Vlimit = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_OVP,
    .evencb = volLimit_handler,
    .multStr = &mStr_home_Vlimit,
};
//电流限制
const struct BtnInfo_Def btn_Ilimit = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_OCP,
    .evencb = ampLimit_handler,
    .multStr = &mStr_home_Ilimit,
};


//定时关闭
const struct BtnInfo_Def btn_TimeOff = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage_edit_timeOff,
    .evencb = TimeOff_handler,
    .multStr = &mStr_home_TimeOff,
};

//输出电压设置
const struct BtnInfo_Def btn_VSet_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Vout_Set,
    .evencb = volSet_handler,
    .multStr = &mStr_home_VSet,
};
//输出电流设置
const struct BtnInfo_Def btn_ISet_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Iout_Set,
    .evencb = ampSet_handler,
    .multStr = &mStr_home_ISet,
};
//电压限制
const struct BtnInfo_Def btn_Vlimit_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_OVP_Set,
    .evencb = volLimit_handler,
    .multStr = &mStr_home_Vlimit,
};
//电流限制
const struct BtnInfo_Def btn_Ilimit_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_OCP_Set,
    .evencb = ampLimit_handler,
    .multStr = &mStr_home_Ilimit,
};


//定时关闭
const struct BtnInfo_Def btn_TimeOff_2 = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.HomePage2_label_Time_Set,
    .evencb = TimeOff_handler,
    .multStr = &mStr_home_TimeOff,
};
#endif

#if 1
//序列输出
//起始点
const struct BtnInfo_Def btn_list_start = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.ListPage_btn_start_label,
    .evencb = ListPage_Option_editStartP_handler,
    .multStr = &mStr_list_lab_Start,
};
//结束点
const struct BtnInfo_Def btn_list_Groups = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.ListPage_btn_count_label,
    .evencb = ListPage_Option_editCount_handler,
    .multStr = &mStr_list_lab_Groups,
};
//循环次数
const struct BtnInfo_Def btn_list_cycle = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.ListPage_btn_cycle_label,
    .evencb = ListPage_Option_editCycles_handler,
    .multStr = &mStr_list_lab_Cycles,
};
//末态
const struct BtnInfo_Def btn_list_endState = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.ListPage_btn_laststate_label,
    .evencb = ListPage_Option_LastState_handler,
    .multStr = &mStr_list_lab_EndState,
};


//表格
const struct BtnInfo_Def btn_list_table = {
    .type = BTN_TYPE_MORE,
    .multStr = &mStr_list_edit,
};
//管理
const struct BtnInfo_Def btn_list_manage = {
    .type = BTN_TYPE_UI,
    .multStr = &mStr_list_manage,
    .ui_enter = ListPage_Manager_Enter,
    .ui_exit = ListPage_Manager_Exit,
    .obj = &ui.ListManagePage_cont,
    .evencb = ListPage_Manager_Table_handler,
};

#endif




#if 1
//DelayOut输出
//起始点
const struct BtnInfo_Def btn_delay_start = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.DelayPage_btn_start_label,
    .evencb = DelayPage_Option_editStartP_handler,
    .multStr = &mStr_delay_lab_Start,
};
//结束点
const struct BtnInfo_Def btn_delay_Groups = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.DelayPage_btn_count_label,
    .evencb = DelayPage_Option_editCount_handler,
    .multStr = &mStr_delay_lab_Groups,
};
//循环次数
const struct BtnInfo_Def btn_delay_cycle = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.DelayPage_btn_cycle_label,
    .evencb = DelayPage_Option_editCycles_handler,
    .multStr = &mStr_delay_lab_Cycles,
};
//保护值
const struct BtnInfo_Def btn_delay_stopVal = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.DelayPage_btn_stopVal_label,
    .evencb = DelayPage_Option_stopVal_handler,
    .multStr = &mStr_delay_lab_stopVal,
};
//动作
const struct BtnInfo_Def btn_delay_endState = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.DelayPage_btn_lastState_label,
    .evencb = DelayPage_Option_lastState_handler,
    .multStr = &mStr_delay_lab_EndState,
};

//表格
const struct BtnInfo_Def btn_delay_table = {
    .type = BTN_TYPE_MORE,
    .multStr = &mStr_delay_edit,
};
//管理
const struct BtnInfo_Def btn_delay_manage = {
    .type = BTN_TYPE_UI,
    .multStr = &mStr_delay_manage,
    .ui_enter = DelayPage_Manager_Enter,
    .ui_exit = DelayPage_Manager_Exit,
    .obj = &ui.DelayManagePage_cont,
    .evencb = DelayPage_Manager_Table_handler,
};
#endif

#if 1
//设置
const struct BtnInfo_Def btn_Battest_option = {
    .type = BTN_TYPE_MORE,
    .multStr = &mStr_Battest_option,
};
//起始点
const struct BtnInfo_Def btn_Battest_start = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.BatTester_btn_start_label,
    .evencb = BatTester_Option_editStartP_handler,
    .multStr = &mStr_Battest_lab_Start,
};
//结束点
const struct BtnInfo_Def btn_Battest_Groups = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.BatTester_btn_count_label,
    .evencb = BatTester_Option_editCount_handler,
    .multStr = &mStr_Battest_lab_Groups,
};
//循环次数
const struct BtnInfo_Def btn_Battest_cycle = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.BatTester_btn_cycle_label,
    .evencb = BatTester_Option_editCycles_handler,
    .multStr = &mStr_Battest_lab_Cycles,
};
const struct BtnInfo_Def btn_Battest_table = {
    .type = BTN_TYPE_MORE,
    .multStr = &mStr_Battest_edit,
};
const struct BtnInfo_Def btn_Battest_manage = {
    .type = BTN_TYPE_UI,
    .multStr = &mStr_Battest_manage,
    .ui_enter = BatTester_Page_Manager_Enter,
    .ui_exit = BatTester_Page_Manager_Exit,
    .obj = &ui.BatTesterManager_cont,
    .evencb = BatTester_Page_Manager_Table_handler,
};
#endif

#if 1
//工作模式
const struct BtnInfo_Def btn_Mode = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_mode_label,
    .evencb = Mode_handler,
    .multStr = &mStr_Mode,
};

//斜率模式
const struct BtnInfo_Def btn_SR_Mode = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_SRMode_label,
    .evencb = SRMode_handler,
    .multStr = &mStr_SR_Mode,
};
struct BtnInfo_Def btn_SR_Set = {
    .type = BTN_TYPE_MORE,
    .multStr = &mStr_SR_Title,
};
//电压斜率
struct BtnInfo_Def btn_VSR_Rising = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_VSR_Up_label,
    .evencb = VSR_Up_handler,
    .multStr = &mStr_VSR_U,
};
struct BtnInfo_Def btn_VSR_Failing = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_VSR_Dn_label,
    .evencb = VSR_Down_handler,
    .multStr = &mStr_VSR_D,
};
//电流斜率
struct BtnInfo_Def btn_ISR_Rising = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_ISR_Up_label,
    .evencb = ISR_Up_handler,
    .multStr = &mStr_ISR_U,
};
struct BtnInfo_Def btn_ISR_Failing = {
    .type = BTN_TYPE_SEL,
    .obj = &ui.OutOptionPage_btn_ISR_Dn_label,
    .evencb = ISR_Down_handler,
    .multStr = &mStr_ISR_D,
};


Tree_Def *tree_SR_Set;
Tree_Def *tree_VSR_Up_Set;
Tree_Def *tree_VSR_Dn_Set;
Tree_Def *tree_ISR_Up_Set;
Tree_Def *tree_ISR_Dn_Set;
#endif


const struct BtnInfo_Def btn_preset_save = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_save,
};
const struct BtnInfo_Def btn_preset_load = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOAD, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_load,
};


const struct BtnInfo_Def btn_group_save = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_SAVE,  .multStr = &mStr_save,
};
const struct BtnInfo_Def btn_group_load = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOAD, .key_long = LV_KEY_LOAD,  .multStr = &mStr_load,
};
const struct BtnInfo_Def btn_group_saveAs = {
    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVEAS, .key_long = LV_KEY_SAVEAS,  .multStr = &mStr_saveAs,
};

#if 1
const struct BtnInfo_Def btn_ip = {
    .type = BTN_TYPE_SEL,  .multStr = &mStr_IP,
    .obj = &ui.Setting_btn_NetIP_label,
    .evencb = IP_handler,
};
const struct BtnInfo_Def btn_gateway = {
    .type = BTN_TYPE_SEL,  .multStr = &mStr_Gateway,
    .obj = &ui.Setting_btn_GateWay_label,
    .evencb = GateWay_handler,
};
const struct BtnInfo_Def btn_netway = {
    .type = BTN_TYPE_SEL,  .multStr = &mStr_NetMask,
    .obj = &ui.Setting_btn_NetMask_label,
    .evencb = NetMask_handler,
};
#endif



static int8_t __curPage = 0;
uint8_t __Get_CurrentPage(void)
{
    if(tree_ui.uiNode == tree_home) {
        return PAGE_HOME;
    } else
        if(tree_ui.uiNode == tree_home_2) {
            return PAGE_HOME2;
        } else
            if(tree_ui.uiNode == tree_preset) {
                return PAGE_PRESET;
            } else
                if(tree_ui.uiNode == tree_list) {
                    return PAGE_LIST;
                } else
                    if(tree_ui.uiNode == tree_list_manage) {
                        return PAGE_LIST_MANAGER;
                    } else
                        if(tree_ui.uiNode == tree_list_temp) {
                            return PAGE_LIST_TEMP;
                        } else
                            if(tree_ui.uiNode == tree_delay) {
                                return PAGE_DELAY;
                            } else
                                if(tree_ui.uiNode == tree_delay_manage) {
                                    return PAGE_DELAY_MANAGER;
                                } else
                                    if(tree_ui.uiNode == tree_delay_temp) {
                                        return PAGE_DELAY_TEMP;
                                    } else
                                        if(tree_ui.uiNode == tree_setting) {
                                            return PAGE_SETTING;
                                        } else
                                            if(tree_ui.uiNode == tree_BatTester) {
                                                return PAGE_BATTESTER;
                                            } else
                                                if(tree_ui.uiNode == tree_monitor) {
                                                    return PAGE_MONITOR;
                                                } else
                                                    if(tree_ui.uiNode == tree_outoption) {
                                                        return PAGE_OUTOPTION;
                                                    } else
                                                        if(tree_ui.uiNode == tree_menu) {
                                                            return PAGE_MENU;
                                                        } else
                                                            if(tree_ui.uiNode == tree_group) {
                                                                return PAGE_GROUP;
                                                            }
    return PAGE_NULL;
}


static void TREE_TEST()
{
    while(tree_ui.uiNode != tree_home) {
        //Tree_UI_Sel_Exit();
        //GUI_KeySend(ui.BtnBar_btnm, LV_KEY_RETURN);
        GUI_KeySend(ui.BtnBar_cont_Btnm, LV_KEY_ESC);
    }
}

void UI_Switch_Page(uint8_t page)
{
    if((page < PAGE_MIN) || (PAGE_MAX < page)) {
        return;
    }
    __curPage = __Get_CurrentPage();
    if(__curPage != page) {
        __curPage = page;
        TREE_TEST();
        switch(page)
        {
            //
            case PAGE_HOME:
                Tree_UI_Sel_Enter(tree_home, 0);
                break;
            case PAGE_HOME2:
                Tree_UI_Sel_Enter(tree_home_2, 0);
                break;
            //
            case PAGE_LIST:
                Tree_UI_Sel_Enter(tree_list, 0);
                break;
            case PAGE_LIST_TEMP:
                Tree_UI_Sel_Enter(tree_list_temp, 0);
                break;
            case PAGE_LIST_MANAGER:
                Tree_UI_Sel_Enter(tree_list_manage, 0);
                break;
            //
            case PAGE_DELAY:
                Tree_UI_Sel_Enter(tree_delay, 0);
                break;
            case PAGE_DELAY_TEMP:
                Tree_UI_Sel_Enter(tree_delay_temp, 0);
                break;
            case PAGE_DELAY_MANAGER:
                Tree_UI_Sel_Enter(tree_delay_manage, 0);
                break;
            //
            case PAGE_PRESET:
                Tree_UI_Sel_Enter(tree_preset, 0);
                break;
            case PAGE_MENU:
                Tree_UI_Sel_Enter(tree_menu, 0);
                break;
            case PAGE_MONITOR:
                Tree_UI_Sel_Enter(tree_monitor, 0);
                break;
            case PAGE_OUTOPTION:
                Tree_UI_Sel_Enter(tree_outoption, 0);
                break;
            case PAGE_SETTING:
                Tree_UI_Sel_Enter(tree_setting, 0);
                break;
            case PAGE_GROUP:
                Tree_UI_Sel_Enter(tree_group, 0);
                break;
            case PAGE_BATTESTER:
                Tree_UI_Sel_Enter(tree_BatTester, 0);
                break;
        }
    }
}
//下一页
void __Next_Page(void) {
    if(__curPage < PAGE_MAX) {
        __curPage += 1;
    } else {
        __curPage = PAGE_MIN;
    }
    UI_Switch_Page(__curPage);
}
//上一页
void __Previous_Page(void) {
    if(__curPage > PAGE_MIN) {
        __curPage -= 1;
    } else {
        __curPage = PAGE_MAX;
    }
    UI_Switch_Page(__curPage);
}

#include "bmpImage.h"
#include "Setting_Interface.h"
uint8_t System_Key_Process(lv_key_t key)
{
    uint8_t used = 0;
    switch(key) {
        case LV_KEY_MENU_LONGP: {
            //长按截图
            IF_System_ScreenShot();
            used = 1;
        }
        break;
        #ifndef HAOYI_VER
        case LV_KEY_PRESET: {
            if(__Get_CurrentPage() != PAGE_PRESET)
            {
                UI_Switch_Page(PAGE_PRESET);
            }
            used = 1;
        }
        break;
        case LV_KEY_PRESET_LONGP: {
            //校准模式显示校准点
            if(systemInfo.calibMode != 0) {
                CalibPage_Enter();
            }
            used = 1;
        }
        break;
        case LV_KEY_HOME: {
            static uint8_t preferPage = 0;
            if(preferPage == 0) {
                if(__Get_CurrentPage() != PAGE_HOME)
                {
                    UI_Switch_Page(PAGE_HOME);
                    preferPage  = 0;
                } else {
                    UI_Switch_Page(PAGE_HOME2);
                    preferPage  = 1;
                }
            } else {
                if(__Get_CurrentPage() != PAGE_HOME2)
                {
                    UI_Switch_Page(PAGE_HOME2);
                    preferPage  = 1;
                } else {
                    UI_Switch_Page(PAGE_HOME);
                    preferPage = 0;
                }
            }
            used = 1;
        }
        break;
        #else
        case LV_KEY_ENTER_LONGP: {
            //校准模式显示校准点
            if(systemInfo.calibMode != 0) {
                CalibPage_Enter();
            }
            used = 1;
        }
        break;
        case LV_KEY_WAVE: {
            if(__Get_CurrentPage() != PAGE_HOME2)
            {
                UI_Switch_Page(PAGE_HOME2);
            } else {
                UI_Switch_Page(PAGE_HOME);
            }
        }
        break;
        #endif
        case LV_KEY_MENU: {
            //            if(__Get_CurrentPage() != PAGE_MENU)
            {
                UI_Switch_Page(PAGE_MENU);
            }
            used = 1;
        }
        break;
        #ifndef HAOYI_VER
        case LV_KEY_LIST: {
            if(ListOut_IsRunning() != 0) {
                if(__Get_CurrentPage() != PAGE_LIST) {
                    UI_Switch_Page(PAGE_LIST);
                }
            } else
                if(ListOut_IsRunning() != 0) {
                    if(__Get_CurrentPage() != PAGE_DELAY) {
                        UI_Switch_Page(PAGE_DELAY);
                    }
                } else
                    if(__Get_CurrentPage() != PAGE_LIST) {
                        UI_Switch_Page(PAGE_LIST);
                    } else
                        if(__Get_CurrentPage() != PAGE_DELAY) {
                            UI_Switch_Page(PAGE_DELAY);
                        }
            used = 1;
        }
        break;
        #else
        case LV_KEY_LIST: {
            if(__Get_CurrentPage() != PAGE_LIST) {
                UI_Switch_Page(PAGE_LIST);
            }
            used = 1;
        }
        break;
        case LV_KEY_DELAYER: {
            if(__Get_CurrentPage() != PAGE_DELAY) {
                UI_Switch_Page(PAGE_DELAY);
            }
            used = 1;
        }
        break;
        #endif
        //上锁
        case LV_KEY_LOCK:
            //若有选择Obj,则取消
            if(tree_ui.selNode != NULL) {
                GUI_SEND_KEY(LV_KEY_RETURN);
            }
            UI_IF_Power_Set_Lock(1);
            used = 1;
            break;
        //上锁/解锁,手动解锁时,强制解除远程控制模式
        case LV_KEY_LOCK_LONGP:
            UI_IF_Power_Set_Lock(0);
            UI_IF_System_Set_Remote(0);
            used = 1;
            break;
        //输出按键
        case LV_KEY_OUTPUT: {
            uint8_t lastState = IF_Power_Get_On_Off();
            uint8_t newState = !lastState;
            if(POWER_MODE != POWER_MODE_NORMAL) {
                newState = 0;
                UI_IF_Power_Set_Mode(POWER_MODE_NORMAL);
                IF_MsgBox_Tips_Mult(&mStr_Exit_extMode_Tips);
            }
            if(newState != 0) {
                //手动操作,自动清除保护状态
                IF_Power_OVP_Clean();
                IF_Power_OCP_Clean();
            }
            UI_IF_Power_Set_On_Off(newState);
            used = 1;
        }
        break;
    }
    return used;
}


void __Goto_Preset(void)
{
    UI_Switch_Page(PAGE_PRESET);
}



Tree_Def *UI_Tree_Init(void)
{
    {
        //主页
        #ifdef HAOYI_VER
        static const struct BtnInfo_Def btn_home = {
            .multStr = &mStr_Home,
            .type = BTN_TYPE_UI,
            .ui_enter = HomePage_2_Enter,
            .ui_exit = HomePage_2_Exit,
            .obj = &ui.HomePage2_cont_Set,
            .evencb = HomePage_2_handler,
        };
        static const struct BtnInfo_Def btn_home_2 = {
            .multStr = &mStr_Home,
            .type = BTN_TYPE_UI,
            .ui_enter = HomePage_Enter,
            .ui_exit = HomePage_Exit,
            .obj = &ui.HomePage_cont_Set,
            .evencb = HomePage_handler,
            .noVisable = 1,
        };
        #else
        //
        static const struct BtnInfo_Def btn_home = {
            .multStr = &mStr_Home,
            .type = BTN_TYPE_UI,
            .ui_enter = HomePage_Enter,
            .ui_exit = HomePage_Exit,
            .obj = &ui.HomePage_cont_Set,
            .evencb = HomePage_handler,
        };
        static const struct BtnInfo_Def btn_home_2 = {
            .multStr = &mStr_Home,
            .type = BTN_TYPE_UI,
            .ui_enter = HomePage_2_Enter,
            .ui_exit = HomePage_2_Exit,
            .obj = &ui.HomePage2_cont_Set,
            .evencb = HomePage_2_handler,
            .noVisable = 1,
        };
        #endif
        tree_home = Tree_CreateNode(&btn_home);
        {
            tree_VSet = Tree_AddNode(tree_home, &btn_VSet);
            tree_ISet = Tree_AddNode(tree_home, &btn_ISet);
            tree_Vlimit = Tree_AddNode(tree_home, &btn_Vlimit);
            tree_Ilimit = Tree_AddNode(tree_home, &btn_Ilimit);
            tree_TimeOff = Tree_AddNode(tree_home, &btn_TimeOff);
            #ifdef HAOYI_VER
            //快捷设置Mx
            static const struct BtnInfo_Def btn_preset = {
                .multStr = &mStr_Preset,
                .type = BTN_TYPE_UI,
                .ui_enter = PresetPage_Enter,
                .ui_exit = PresetPage_Exit,
                .obj = &ui.Preset_img_itemSel,
                .evencb = PresetCont_handler,
                .noVisable = 0,
            };
            tree_preset = Tree_AddNode(tree_home, &btn_preset);
            #else
            static const struct BtnInfo_Def btn_switchPage = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_HOME, .key_long = LV_KEY_HOME,  .multStr = &mStr_Home_Switch,
            };
            Tree_AddNode(tree_home, &btn_switchPage);
            //快捷设置Mx
            static const struct BtnInfo_Def btn_preset = {
                .multStr = &mStr_Preset,
                .type = BTN_TYPE_UI,
                .ui_enter = PresetPage_Enter,
                .ui_exit = PresetPage_Exit,
                .obj = &ui.Preset_img_itemSel,
                .evencb = PresetCont_handler,
                .noVisable = 1,
            };
            tree_preset = Tree_AddNode(tree_home, &btn_preset);
            #endif
            tree_home_2 = Tree_AddNode(tree_home, &btn_home_2);
            {
                Tree_AddNode(tree_home_2, &btn_VSet_2);
                Tree_AddNode(tree_home_2, &btn_ISet_2);
                Tree_AddNode(tree_home_2, &btn_Vlimit_2);
                Tree_AddNode(tree_home_2, &btn_Ilimit_2);
                Tree_AddNode(tree_home_2, &btn_TimeOff_2);
                #ifdef HAOYI_VER
                //跳转预设值页面
                static const struct BtnInfo_Def btn_Preset = {
                    .type = BTN_TYPE_CALL, .multStr = &mStr_Preset,
                    .call = __Goto_Preset,
                };
                Tree_AddNode(tree_home_2, &btn_Preset);
                #else
                Tree_AddNode(tree_home_2, &btn_switchPage);
                #endif
            }
            {
                //编辑
                static const struct BtnInfo_Def btn_Preset_Edit = {
                    .type = BTN_TYPE_MORE, .multStr = &mStr_Preset_edit,
                };
                Tree_Def *tree_preset_edit = Tree_AddNode(tree_preset, &btn_Preset_Edit);
                {
                    #if 1
                    extern lv_obj_t *preset_voltage_sel_node;
                    extern lv_obj_t *preset_current_sel_node;
                    extern lv_obj_t *preset_ovp_sel_node;
                    extern lv_obj_t *preset_ocp_sel_node;
                    extern lv_obj_t *preset_time_sel_node;
                    static const struct BtnInfo_Def btn_Vol = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_home_VSet,
                        .obj = &preset_voltage_sel_node,    .evencb = Preset_Volt_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_Amp = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_home_ISet,
                        .obj = &preset_current_sel_node,    .evencb = Preset_Curr_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_OVP = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_home_Vlimit,
                        .obj = &preset_ovp_sel_node,        .evencb = Preset_OVP_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_OCP = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_home_Ilimit,
                        .obj = &preset_ocp_sel_node,        .evencb = Preset_OCP_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_timeOff = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_home_TimeOff,
                        .obj = &preset_time_sel_node,       .evencb = Preset_Time_Set_handler,
                    };
                    Tree_AddNode(tree_preset_edit, &btn_Vol);
                    Tree_AddNode(tree_preset_edit, &btn_Amp);
                    Tree_AddNode(tree_preset_edit, &btn_OVP);
                    Tree_AddNode(tree_preset_edit, &btn_OCP);
                    Tree_AddNode(tree_preset_edit, &btn_timeOff);
                    #else
                    static const struct BtnInfo_Def btn_Vol = {
                        .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F1, .key_long = LV_KEY_F1,  .multStr = &mStr_home_VSet,
                        .obj = &ui.Preset_img_itemSel,
                    };
                    static const struct BtnInfo_Def btn_Amp = {
                        .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F2, .key_long = LV_KEY_F2,  .multStr = &mStr_home_ISet,
                        .obj = &ui.Preset_img_itemSel,
                    };
                    static const struct BtnInfo_Def btn_OVP = {
                        .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F3, .key_long = LV_KEY_F3_LONGP,  .multStr = &mStr_home_Vlimit,
                        .obj = &ui.Preset_img_itemSel,
                    };
                    static const struct BtnInfo_Def btn_OCP = {
                        .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F4, .key_long = LV_KEY_F4_LONGP,  .multStr = &mStr_home_Ilimit,
                        .obj = &ui.Preset_img_itemSel,
                    };
                    static const struct BtnInfo_Def btn_timeOff = {
                        .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F5, .key_long = LV_KEY_F5,  .multStr = &mStr_home_TimeOff,
                        .obj = &ui.Preset_img_itemSel,
                    };
                    Tree_AddNode(tree_preset_edit, &btn_Vol);
                    Tree_AddNode(tree_preset_edit, &btn_Amp);
                    Tree_AddNode(tree_preset_edit, &btn_OVP);
                    Tree_AddNode(tree_preset_edit, &btn_OCP);
                    Tree_AddNode(tree_preset_edit, &btn_timeOff);
                    #endif
                }
                Tree_AddNode(tree_preset, &btn_preset_save);
                Tree_AddNode(tree_preset, &btn_preset_load);
            }
        }
        #if 1
        //序列输出
        static const struct BtnInfo_Def btn_list = {
            .multStr = &mStr_List,
            .type = BTN_TYPE_UI,
            .ui_enter = ListPage_Enter,
            .ui_exit = ListPage_Exit,
            .obj = &ui.ListPage_cont_Table,
            .evencb = ListPage_Table_handler,
            .noVisable = 1,
        };
        tree_list = Tree_AddNode(tree_home, &btn_list);
        {
            //设置
            static const struct BtnInfo_Def btn_list_option = {
                .type = BTN_TYPE_MORE,
                .multStr = &mStr_list_option,
            };
            tree_list_option = Tree_AddNode(tree_list, &btn_list_option);
            {
                tree_list_start = Tree_AddNode(tree_list_option, &btn_list_start);
                tree_list_end = Tree_AddNode(tree_list_option, &btn_list_Groups);
                tree_list_cycles = Tree_AddNode(tree_list_option, &btn_list_cycle);
                tree_list_lastState = Tree_AddNode(tree_list_option, &btn_list_endState);
            }
            //表格
            tree_list_table = Tree_AddNode(tree_list, &btn_list_table);
            {
                extern lv_obj_t *list_voltage_sel_node;
                extern lv_obj_t *list_current_sel_node;
                extern lv_obj_t *list_ktime_sel_node;
                static const struct BtnInfo_Def btn_Vout = {
                    .type = BTN_TYPE_SEL,       .obj = &list_voltage_sel_node,
                    .evencb = List_Volt_Set_handler,
                    .multStr = &mStr_list_Voltage,
                };
                static const struct BtnInfo_Def btn_Iout = {
                    .type = BTN_TYPE_SEL,       .obj = &list_current_sel_node,
                    .evencb = List_Curr_Set_handler,
                    .multStr = &mStr_list_Current,
                };
                static const struct BtnInfo_Def btn_keepT = {
                    .type = BTN_TYPE_SEL,       .obj = &list_ktime_sel_node,
                    .evencb = List_Time_Set_handler,
                    .multStr = &mStr_list_keepT,
                };
                tree_list_Vout = Tree_AddNode(tree_list_table, &btn_Vout);
                tree_list_Iout = Tree_AddNode(tree_list_table, &btn_Iout);
                tree_list_keepT = Tree_AddNode(tree_list_table, &btn_keepT);
            }
            //管理
            tree_list_manage = Tree_AddNode(tree_list, &btn_list_manage);
            {
                static const struct BtnInfo_Def btn_list_save = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_save,
                };
                Tree_AddNode(tree_list_manage, &btn_list_save);
                static const struct BtnInfo_Def btn_list_load = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOAD, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_load,
                };
                Tree_AddNode(tree_list_manage, &btn_list_load);
                static const struct BtnInfo_Def btn_list_saveAs = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVEAS, .key_long = LV_KEY_SAVEAS,  .multStr = &mStr_saveAs,
                };
                Tree_Def *tree_list_manage_saveAs = Tree_AddNode(tree_list_manage, &btn_list_saveAs);
                {
                    Tree_AddNode(tree_list_manage_saveAs, &btn_Upper);
                    Tree_AddNode(tree_list_manage_saveAs, &btn_Lower);
                    Tree_AddNode(tree_list_manage_saveAs, &btn_Number);
                    //保存
                    Tree_AddNode(tree_list_manage_saveAs, &btn_file_save_flash);
                    Tree_AddNode(tree_list_manage_saveAs, &btn_file_save_udisk);
                }
                Tree_Def *tree_list_manage_rename = Tree_AddNode(tree_list_manage, &btn_file_rename);
                {
                    Tree_AddNode(tree_list_manage_rename, &btn_Upper);
                    Tree_AddNode(tree_list_manage_rename, &btn_Lower);
                    Tree_AddNode(tree_list_manage_rename, &btn_Number);
                    //
                    Tree_AddNode(tree_list_manage_rename, &btn_enter);
                    Tree_AddNode(tree_list_manage_rename, &btn_esc);
                }
                Tree_AddNode(tree_list_manage, &btn_file_delete);
            }
            //模板
            static const struct BtnInfo_Def btn_list_temp = {
                .type = BTN_TYPE_UI,
                .multStr = &mStr_list_temp,
                .ui_enter = ListTempPage_Enter,
                .ui_exit = ListTempPage_Exit,
                .obj = &ui.ListTempPage_cont_1,
                .evencb = ListTempPage_Cont_handler,
            };
            tree_list_temp = Tree_AddNode(tree_list, &btn_list_temp);
            {
                void ListTemp_Edit_Object_handler(lv_obj_t *obj, lv_event_t event);
                void ListTemp_Edit_Type_handler(lv_obj_t *obj, lv_event_t event);
                //变量(电压/电流)
                static const struct BtnInfo_Def btn_tempObject = {
                    .type = BTN_TYPE_SEL,
                    .obj = &ui.ListTempPage_btn_obj_label,
                    .evencb = ListTemp_Edit_Object_handler,
                    .multStr = &mStr_list_temp_Object,
                };
                Tree_AddNode(tree_list_temp, &btn_tempObject);
                //波形种类
                static const struct BtnInfo_Def btn_tempWave = {
                    .type = BTN_TYPE_SEL,
                    .obj = &ui.ListTempPage_btn_type_label,
                    .evencb = ListTemp_Edit_Type_handler,
                    .multStr = &mStr_list_temp_Type,
                };
                Tree_AddNode(tree_list_temp, &btn_tempWave);
                //编辑
                static const struct BtnInfo_Def btn_tempEdit = {
                    .type = BTN_TYPE_MORE, .multStr = &mStr_list_temp_Edit,
                };
                tree_list_tempEdit = Tree_AddNode(tree_list_temp, &btn_tempEdit);
                //生成
                static const struct BtnInfo_Def btn_tempGenerate = {
                    .type = BTN_TYPE_KEY, .key_short = 'C', .multStr = &mStr_list_temp_Generate,
                };
                Tree_AddNode(tree_list_temp, &btn_tempGenerate);
            }
            tree_list_btn_start = Tree_AddNode(tree_list, &btn_start);
        }
        #endif
        #if 1
        //DelayOut输出
        static const struct BtnInfo_Def btn_delay = {
            .multStr = &mStr_Delayer,
            .type = BTN_TYPE_UI,
            .ui_enter = DelayPage_Enter,
            .ui_exit = DelayPage_Exit,
            .obj = &ui.DelayPage_cont_Table,
            .evencb = DelayPage_Table_handler,
            .noVisable = 1,
        };
        tree_delay = Tree_AddNode(tree_home, &btn_delay);
        {
            //设置
            static const struct BtnInfo_Def btn_delay_option = {
                .type = BTN_TYPE_MORE,
                .multStr = &mStr_delay_option,
            };
            tree_delay_option = Tree_AddNode(tree_delay, &btn_delay_option);
            {
                tree_delay_start = Tree_AddNode(tree_delay_option, &btn_delay_start);
                tree_delay_end = Tree_AddNode(tree_delay_option, &btn_delay_Groups);
                tree_delay_cycles = Tree_AddNode(tree_delay_option, &btn_delay_cycle);
                tree_delay_protectVal = Tree_AddNode(tree_delay_option, &btn_delay_stopVal);
                tree_delay_protectAction = Tree_AddNode(tree_delay_option, &btn_delay_endState);
            }
            //表格
            tree_delay_table = Tree_AddNode(tree_delay, &btn_delay_table);
            {
                #if 1
                extern lv_obj_t *delayer_state_sel_node;
                extern lv_obj_t *delayer_dT_sel_node;
                static const struct BtnInfo_Def btn_State = {
                    .type = BTN_TYPE_SEL,       .obj = &delayer_state_sel_node,
                    .evencb = Delayer_State_Set_handler,
                    .multStr = &mStr_delay_State,
                };
                static const struct BtnInfo_Def btn_dealyT = {
                    .type = BTN_TYPE_SEL,       .obj = &delayer_dT_sel_node,
                    .evencb = Delayer_dT_Set_handler,
                    .multStr = &mStr_delay_dT,
                };
                tree_delay_Out = Tree_AddNode(tree_delay_table, &btn_State);
                tree_delay_delayT = Tree_AddNode(tree_delay_table, &btn_dealyT);
                #else
                static const struct BtnInfo_Def btn_State = {
                    .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F1, .key_long = LV_KEY_F1,  .multStr = &mStr_delay_State,
                    .obj = &ui.DelayPage_cont_Table,
                };
                static const struct BtnInfo_Def btn_dealyT = {
                    .type = BTN_TYPE_SEL,    .key_short = LV_KEY_F2, .key_long = LV_KEY_F2,  .multStr = &mStr_delay_dT,
                    .obj = &ui.DelayPage_cont_Table,
                };
                tree_delay_Out = Tree_AddNode(tree_delay_table, &btn_State);
                tree_delay_delayT = Tree_AddNode(tree_delay_table, &btn_dealyT);
                #endif
            }
            //管理
            tree_delay_manage = Tree_AddNode(tree_delay, &btn_delay_manage);
            {
                static const struct BtnInfo_Def btn_delay_save = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_save,
                };
                Tree_AddNode(tree_delay_manage, &btn_delay_save);
                static const struct BtnInfo_Def btn_delay_load = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOAD, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_load,
                };
                Tree_AddNode(tree_delay_manage, &btn_delay_load);
                static const struct BtnInfo_Def btn_delay_saveAs = {
                    .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVEAS, .key_long = LV_KEY_SAVEAS,  .multStr = &mStr_saveAs,
                };
                Tree_Def *tree_delay_manage_saveAs = Tree_AddNode(tree_delay_manage, &btn_delay_saveAs);
                {
                    Tree_AddNode(tree_delay_manage_saveAs, &btn_Upper);
                    Tree_AddNode(tree_delay_manage_saveAs, &btn_Lower);
                    Tree_AddNode(tree_delay_manage_saveAs, &btn_Number);
                    //保存
                    Tree_AddNode(tree_delay_manage_saveAs, &btn_file_save_flash);
                    Tree_AddNode(tree_delay_manage_saveAs, &btn_file_save_udisk);
                }
                Tree_Def *tree_delay_manage_rename = Tree_AddNode(tree_delay_manage, &btn_file_rename);
                {
                    Tree_AddNode(tree_delay_manage_rename, &btn_Upper);
                    Tree_AddNode(tree_delay_manage_rename, &btn_Lower);
                    Tree_AddNode(tree_delay_manage_rename, &btn_Number);
                    //
                    Tree_AddNode(tree_delay_manage_rename, &btn_enter);
                    Tree_AddNode(tree_delay_manage_rename, &btn_esc);
                }
                Tree_AddNode(tree_delay_manage, &btn_file_delete);
            }
            //模板
            extern void Delay_Temp_Cont_EventHandler(lv_obj_t *obj, lv_event_t event);
            static const struct BtnInfo_Def btn_delay_temp = {
                .type = BTN_TYPE_UI,
                .multStr = &mStr_delay_temp,
                .ui_enter = DelayTempPage_Enter,
                .ui_exit = DelayTempPage_Exit,
                .obj = &ui.DelayTempPage_cont_1,
                .evencb = Delay_Temp_Cont_EventHandler,
            };
            tree_delay_temp = Tree_AddNode(tree_delay, &btn_delay_temp);
            //功能开关
            Tree_AddNode(tree_delay, &btn_start);
        }
        #endif
        static const struct BtnInfo_Def btn_Menu = {
            .multStr = &mStr_Menu,
            .type = BTN_TYPE_UI,
            .ui_enter = MenuPage_Enter,
            .ui_exit = MenuPage_Exit,
            .obj = &ui.Menu_cont,
            .evencb = Menu_handler,
            .noVisable = 1,
        };
        tree_menu = Tree_AddNode(tree_home, &btn_Menu);
        {
            #if USE_BATTESTER
            static const struct BtnInfo_Def btn_more_volt = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_MORE_VOLT,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_MORE_VOLT,
            };
            static const struct BtnInfo_Def btn_less_volt = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LESS_VOLT,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_LESS_VOLT,
            };
            static const struct BtnInfo_Def btn_more_curr = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_MORE_CURR,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_MORE_CURR,
            };
            static const struct BtnInfo_Def btn_less_curr = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LESS_CURR,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_LESS_CURR,
            };
            static const struct BtnInfo_Def btn_more_power = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_MORE_POWER,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_MORE_POWER,
            };
            static const struct BtnInfo_Def btn_less_power = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LESS_POWER,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_LESS_POWER,
            };
            static const struct BtnInfo_Def btn_more_dvm = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_MORE_DVM,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_MORE_DVM,
            };
            static const struct BtnInfo_Def btn_less_dvm = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LESS_DVM,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_LESS_DVM,
            };
            static const struct BtnInfo_Def btn_none_protect = {
                .type = BTN_TYPE_KEY,    .key_short = LV_KEY_NONE_PROTECT,
                .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_Battest_None_Protect,
            };
            //电池测试
            static const struct BtnInfo_Def btn_BatteryTest = {
                .multStr = &mStr_BatteryTester,
                .type = BTN_TYPE_UI,
                .ui_enter = BatteryTester_Page_Enter,
                .ui_exit = BatteryTester_Page_Exit,
                .obj = &ui.BatTester_cont_Table,
                .evencb = BatteryTester_Page_Table_handler,
                .noVisable = 0,
            };
            tree_BatTester = Tree_AddNode(tree_menu, &btn_BatteryTest);
            {
                tree_BatTester_option = Tree_AddNode(tree_BatTester, &btn_Battest_option);
                {
                    tree_BatTester_start = Tree_AddNode(tree_BatTester_option, &btn_Battest_start);
                    tree_BatTester_end = Tree_AddNode(tree_BatTester_option, &btn_Battest_Groups);
                    tree_BatTester_cycles = Tree_AddNode(tree_BatTester_option, &btn_Battest_cycle);
                    //全局保护设置
                    static const struct BtnInfo_Def btn_Battest_protect = {
                        .type = BTN_TYPE_MORE,
                        .multStr = &mStr_Battest_Protect,
                    };
                    tree_BatTester_protect = Tree_AddNode(tree_BatTester_option, &btn_Battest_protect);
                    {
                        static const struct BtnInfo_Def btn_Battest_protect_param_0 = {
                            .type = BTN_TYPE_SEL,       .obj = &ui.BatTester_btn_protect_label,
                            .evencb = BatTester_Option_Protect_Value_0_handler,
                            .multStr = &mStr_Battest_Protect_Param_0,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_logic_1 = {
                            .type = BTN_TYPE_SEL,       .obj = &ui.BatTester_btn_protect_label,
                            .evencb = BatTester_Option_Protect_Logic_1_handler,
                            .multStr = &mStr_Battest_Protect_Logic_1,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_param_1 = {
                            .type = BTN_TYPE_SEL,       .obj = &ui.BatTester_btn_protect_label,
                            .evencb = BatTester_Option_Protect_Value_1_handler,
                            .multStr = &mStr_Battest_Protect_Param_1,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_logic_2 = {
                            .type = BTN_TYPE_SEL,       .obj = &ui.BatTester_btn_protect_label,
                            .evencb = BatTester_Option_Protect_Logic_2_handler,
                            .multStr = &mStr_Battest_Protect_Logic_2,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_param_2 = {
                            .type = BTN_TYPE_SEL,       .obj = &ui.BatTester_btn_protect_label,
                            .evencb = BatTester_Option_Protect_Value_2_handler,
                            .multStr = &mStr_Battest_Protect_Param_2,
                        };
                        Tree_Def *tree_temp = NULL;
                        tree_temp = Tree_AddNode(tree_BatTester_protect, &btn_Battest_protect_param_0);
                        {
                            Tree_AddNode(tree_temp, &btn_more_volt);
                            Tree_AddNode(tree_temp, &btn_less_volt);
                            Tree_AddNode(tree_temp, &btn_more_curr);
                            Tree_AddNode(tree_temp, &btn_less_curr);
                            Tree_AddNode(tree_temp, &btn_more_power);
                            Tree_AddNode(tree_temp, &btn_less_power);
                            Tree_AddNode(tree_temp, &btn_more_dvm);
                            Tree_AddNode(tree_temp, &btn_less_dvm);
                            Tree_AddNode(tree_temp, &btn_none_protect);
                        }
                        Tree_AddNode(tree_BatTester_protect, &btn_Battest_protect_logic_1);
                        tree_temp = Tree_AddNode(tree_BatTester_protect, &btn_Battest_protect_param_1);
                        {
                            Tree_AddNode(tree_temp, &btn_more_volt);
                            Tree_AddNode(tree_temp, &btn_less_volt);
                            Tree_AddNode(tree_temp, &btn_more_curr);
                            Tree_AddNode(tree_temp, &btn_less_curr);
                            Tree_AddNode(tree_temp, &btn_more_power);
                            Tree_AddNode(tree_temp, &btn_less_power);
                            Tree_AddNode(tree_temp, &btn_more_dvm);
                            Tree_AddNode(tree_temp, &btn_less_dvm);
                            Tree_AddNode(tree_temp, &btn_none_protect);
                        }
                        Tree_AddNode(tree_BatTester_protect, &btn_Battest_protect_logic_2);
                        tree_temp = Tree_AddNode(tree_BatTester_protect, &btn_Battest_protect_param_2);
                        {
                            Tree_AddNode(tree_temp, &btn_more_volt);
                            Tree_AddNode(tree_temp, &btn_less_volt);
                            Tree_AddNode(tree_temp, &btn_more_curr);
                            Tree_AddNode(tree_temp, &btn_less_curr);
                            Tree_AddNode(tree_temp, &btn_more_power);
                            Tree_AddNode(tree_temp, &btn_less_power);
                            Tree_AddNode(tree_temp, &btn_more_dvm);
                            Tree_AddNode(tree_temp, &btn_less_dvm);
                            Tree_AddNode(tree_temp, &btn_none_protect);
                        }
                    }
                    //触发时间
                    static const struct BtnInfo_Def btn_Battest_trigTime = {
                        .type = BTN_TYPE_SEL,
                        .obj = &ui.BatTester_btn_TrigTime_label,
                        .evencb = BatTester_Option_TrigTime_handler,
                        .multStr = &mStr_Battest_lab_TrigTime,
                    };
                    tree_BatTester_trigTime = Tree_AddNode(tree_BatTester_option, &btn_Battest_trigTime);
                }
                //表格
                tree_BatTester_table = Tree_AddNode(tree_BatTester, &btn_Battest_table);
                {
                    extern lv_obj_t *voltage_sel_node;
                    extern lv_obj_t *current_sel_node;
                    extern lv_obj_t *ktime_sel_node;
                    extern void __Volt_Set_handler(lv_obj_t *obj, lv_event_t event);
                    extern void __Curr_Set_handler(lv_obj_t *obj, lv_event_t event);
                    extern void __Time_Set_handler(lv_obj_t *obj, lv_event_t event);
                    static const struct BtnInfo_Def btn_Vout = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_Battest_Voltage,
                        .obj = &voltage_sel_node,
                        .evencb = __Volt_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_Iout = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_Battest_Current,
                        .obj = &current_sel_node,
                        .evencb = __Curr_Set_handler,
                    };
                    static const struct BtnInfo_Def btn_keepT = {
                        .type = BTN_TYPE_SEL,    .multStr = &mStr_Battest_keepT,
                        .obj = &ktime_sel_node,
                        .evencb = __Time_Set_handler,
                    };
                    tree_BatTester_Vout = Tree_AddNode(tree_BatTester_table, &btn_Vout);
                    tree_BatTester_Iout = Tree_AddNode(tree_BatTester_table, &btn_Iout);
                    tree_BatTester_keepT = Tree_AddNode(tree_BatTester_table, &btn_keepT);
                    {
                        extern lv_obj_t *protect_param0_sel_node;
                        extern lv_obj_t *protect_logic1_sel_node;
                        extern lv_obj_t *protect_param1_sel_node;
                        void __Protect_Set_Param0_handler(lv_obj_t *obj, lv_event_t event);
                        void __Protect_Set_Logic1_handler(lv_obj_t *obj, lv_event_t event);
                        void __Protect_Set_Param1_handler(lv_obj_t *obj, lv_event_t event);
                        static const struct BtnInfo_Def btn_Battest_protect_param_0 = {
                            .type = BTN_TYPE_SEL,       .obj = &protect_param0_sel_node,
                            .evencb = __Protect_Set_Param0_handler,
                            .multStr = &mStr_Battest_Protect_Param_0,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_logic_1 = {
                            .type = BTN_TYPE_SEL,       .obj = &protect_logic1_sel_node,
                            .evencb = __Protect_Set_Logic1_handler,
                            .multStr = &mStr_Battest_Protect_Logic_1,
                        };
                        static const struct BtnInfo_Def btn_Battest_protect_param_1 = {
                            .type = BTN_TYPE_SEL,       .obj = &protect_param1_sel_node,
                            .evencb = __Protect_Set_Param1_handler,
                            .multStr = &mStr_Battest_Protect_Param_1,
                        };
                        Tree_Def *tree_temp = NULL;
                        tree_temp = Tree_AddNode(tree_BatTester_table, &btn_Battest_protect_param_0);
                        {
                            Tree_AddNode(tree_temp, &btn_more_volt);
                            Tree_AddNode(tree_temp, &btn_less_volt);
                            Tree_AddNode(tree_temp, &btn_more_curr);
                            Tree_AddNode(tree_temp, &btn_less_curr);
                            Tree_AddNode(tree_temp, &btn_more_power);
                            Tree_AddNode(tree_temp, &btn_less_power);
                            Tree_AddNode(tree_temp, &btn_more_dvm);
                            Tree_AddNode(tree_temp, &btn_less_dvm);
                            Tree_AddNode(tree_temp, &btn_none_protect);
                        }
                        Tree_AddNode(tree_BatTester_table, &btn_Battest_protect_logic_1);
                        tree_temp = Tree_AddNode(tree_BatTester_table, &btn_Battest_protect_param_1);
                        {
                            Tree_AddNode(tree_temp, &btn_more_volt);
                            Tree_AddNode(tree_temp, &btn_less_volt);
                            Tree_AddNode(tree_temp, &btn_more_curr);
                            Tree_AddNode(tree_temp, &btn_less_curr);
                            Tree_AddNode(tree_temp, &btn_more_power);
                            Tree_AddNode(tree_temp, &btn_less_power);
                            Tree_AddNode(tree_temp, &btn_more_dvm);
                            Tree_AddNode(tree_temp, &btn_less_dvm);
                            Tree_AddNode(tree_temp, &btn_none_protect);
                        }
                    }
                }
                #if 1
                //管理
                tree_BatTester_manage = Tree_AddNode(tree_BatTester, &btn_Battest_manage);
                {
                    static const struct BtnInfo_Def btn_Battest_save = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_save,
                    };
                    Tree_AddNode(tree_BatTester_manage, &btn_Battest_save);
                    static const struct BtnInfo_Def btn_Battest_load = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_LOAD, .key_long = LV_KEY_DEFAULT,  .multStr = &mStr_load,
                    };
                    Tree_AddNode(tree_BatTester_manage, &btn_Battest_load);
                    static const struct BtnInfo_Def btn_Battest_saveAs = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVEAS, .key_long = LV_KEY_SAVEAS,  .multStr = &mStr_saveAs,
                    };
                    Tree_Def *tree_Battest_manage_saveAs = Tree_AddNode(tree_BatTester_manage, &btn_Battest_saveAs);
                    {
                        Tree_AddNode(tree_Battest_manage_saveAs, &btn_Upper);
                        Tree_AddNode(tree_Battest_manage_saveAs, &btn_Lower);
                        Tree_AddNode(tree_Battest_manage_saveAs, &btn_Number);
                        //保存
                        Tree_AddNode(tree_Battest_manage_saveAs, &btn_file_save_flash);
                        Tree_AddNode(tree_Battest_manage_saveAs, &btn_file_save_udisk);
                    }
                    Tree_Def *tree_Battest_manage_rename = Tree_AddNode(tree_BatTester_manage, &btn_file_rename);
                    {
                        Tree_AddNode(tree_Battest_manage_rename, &btn_Upper);
                        Tree_AddNode(tree_Battest_manage_rename, &btn_Lower);
                        Tree_AddNode(tree_Battest_manage_rename, &btn_Number);
                        //
                        Tree_AddNode(tree_Battest_manage_rename, &btn_enter);
                        Tree_AddNode(tree_Battest_manage_rename, &btn_esc);
                    }
                    Tree_AddNode(tree_BatTester_manage, &btn_file_delete);
                }
                #endif
                tree_BatTester_btn_start = Tree_AddNode(tree_BatTester, &btn_start);
            }
            #endif
            #if 0
            //触发器
            static const struct BtnInfo_Def btn_trigger = {
                .multStr = &mStr_trigger,
                .type = BTN_TYPE_UI,
                .ui_enter = TriggerPage_Enter,
                .ui_exit = TriggerPage_Exit,
                .obj = &ui.TriggerPage_cont_1,
                .evencb = TriggerPage_handler,
                .noVisable = 0,
            };
            tree_trigger = Tree_AddNode(tree_menu, &btn_trigger);
            #endif
            //监视器
            static const struct BtnInfo_Def btn_monitor = {
                .multStr = &mStr_Monitor,
                .type = BTN_TYPE_UI,
                .ui_enter = MonitorPage_Enter,
                .ui_exit = MonitorPage_Exit,
                .obj = &ui.Monitor_cont,
                .evencb = Monitor_handler,
                .noVisable = 0,
            };
            tree_monitor = Tree_AddNode(tree_menu, &btn_monitor);
            {
                //                Tree_AddNode(tree_monitor, &btn_on);
            }
            //输出设置
            static const struct BtnInfo_Def btn_outoption = {
                .multStr = &mStr_OutOption,
                .type = BTN_TYPE_UI,
                .ui_enter = OutOptionPage_Enter,
                .ui_exit = OutOptionPage_Exit,
                .obj = &ui.OutOptionPage_cont,
                //                .evencb = OutOptionTable_handler,
                .noVisable = 0,
            };
            tree_outoption = Tree_AddNode(tree_menu, &btn_outoption);
            {
                //工作模式
                Tree_Def *tree_outoption_mode = Tree_AddNode(tree_outoption, &btn_Mode);
                {
                    #ifndef VER_A
                    static const struct BtnInfo_Def btn_Normal = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_F1, .key_long = LV_KEY_F1,  .multStr = &mStr_Mode_Normal,
                        .obj = &ui.OutOptionPage_btn_mode_label,
                    };
                    Tree_AddNode(tree_outoption_mode, &btn_Normal);
                    static const struct BtnInfo_Def btn_ExtV = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_F2, .key_long = LV_KEY_F2,  .multStr = &mStr_Mode_Ext_V,
                        .obj = &ui.OutOptionPage_btn_mode_label,
                    };
                    Tree_AddNode(tree_outoption_mode, &btn_ExtV);
                    static const struct BtnInfo_Def btn_ExtD = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_F3, .key_long = LV_KEY_F3,  .multStr = &mStr_Mode_Ext_D,
                        .obj = &ui.OutOptionPage_btn_mode_label,
                    };
                    Tree_AddNode(tree_outoption_mode, &btn_ExtD);
                    #endif
                }
                //上电保持
                static const struct BtnInfo_Def btn_POut = {
                    .type = BTN_TYPE_SEL,
                    .obj = &ui.OutOptionPage_btn_P_Out_label,
                    .evencb = P_Out_handler,
                    .multStr = &mStr_P_Out,
                };
                Tree_AddNode(tree_outoption, &btn_POut);
                //数字电压表
                static const struct BtnInfo_Def btn_DVM_Onoff = {
                    .type = BTN_TYPE_SEL,
                    .obj = &ui.OutOptionPage_btn_DVM_label,
                    .evencb = DVM_Onoff_handler,
                    .multStr = &mStr_DVM_onoff,
                };
                Tree_AddNode(tree_outoption, &btn_DVM_Onoff);
                //斜率设置
                Tree_AddNode(tree_outoption, &btn_SR_Mode);
                tree_SR_Set = Tree_AddNode(tree_outoption, &btn_SR_Set);
                {
                    tree_VSR_Up_Set = Tree_AddNode(tree_SR_Set, &btn_VSR_Rising);
                    tree_VSR_Dn_Set = Tree_AddNode(tree_SR_Set, &btn_VSR_Failing);
                    tree_ISR_Up_Set = Tree_AddNode(tree_SR_Set, &btn_ISR_Rising);
                    tree_ISR_Dn_Set = Tree_AddNode(tree_SR_Set, &btn_ISR_Failing);
                }
            }
            //设置
            extern void SettingTable_handler(lv_obj_t *obj, lv_event_t event);
            static const struct BtnInfo_Def btn_setting = {
                .multStr = &mStr_Setting,
                .type = BTN_TYPE_UI,
                .ui_enter = SettingPage_Enter,
                .ui_exit = SettingPage_Exit,
                .obj = &ui.Setting_cont_1,
                .evencb = SettingTable_handler,
                .noVisable = 0,
            };
            tree_setting = Tree_AddNode(tree_menu, &btn_setting);
            {
                //基础设置
                static const struct BtnInfo_Def btn_Base = {
                    .type = BTN_TYPE_MORE,
                    .multStr = &mStr_BaseTitle,
                };
                Tree_Def *tree_base = Tree_AddNode(tree_setting, &btn_Base);
                {
                    //屏幕背光
                    static const struct BtnInfo_Def btn_BackLight = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_Brightness,
                        .obj = &ui.Setting_btn_BackLight_label,
                        .evencb = Brightness_handler,
                    };
                    Tree_AddNode(tree_base, &btn_BackLight);
                    //提示音
                    static const struct BtnInfo_Def btn_beep = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_Beeper,
                        .obj = &ui.Setting_btn_Beep_label,
                        .evencb = Beep_handler,
                    };
                    Tree_AddNode(tree_base, &btn_beep);
                    //掉电检测
                    static const struct BtnInfo_Def btn_PowerDown = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_PowerDown,
                        .obj = &ui.Setting_btn_PowerDown_label,
                        .evencb = Power_Setting_handler,
                    };
                    Tree_AddNode(tree_base, &btn_PowerDown);
                }
                //通讯设置
                static const struct BtnInfo_Def btn_Comm = {
                    .type = BTN_TYPE_MORE,
                    .multStr = &mStr_CommTitle,
                };
                Tree_Def *tree_comm = Tree_AddNode(tree_setting, &btn_Comm);
                {
                    //波特率
                    static const struct BtnInfo_Def btn_baudRate = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_Comm_BaudRate,
                        .obj = &ui.Setting_btn_Comm_BaudRate_label,
                        .evencb = Comm_BaudRate_handler,
                    };
                    Tree_AddNode(tree_comm, &btn_baudRate);
                    //通讯协议
                    static const struct BtnInfo_Def btn_Protocol = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_Comm_Protocol,
                        .obj = &ui.Setting_btn_Comm_Protocol_label,
                        .evencb = Comm_Protocol_handler,
                    };
                    Tree_AddNode(tree_comm, &btn_Protocol);
                    //通讯地址
                    static const struct BtnInfo_Def btn_Protocol_Address = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_Comm_Address,
                        .obj = &ui.Setting_btn_Comm_Address_label,
                        .evencb = Comm_Protocol_Address_handler,
                    };
                    Tree_AddNode(tree_comm, &btn_Protocol_Address);
                }
                //网络设置
                static const struct BtnInfo_Def btn_Network = {
                    .type = BTN_TYPE_MORE,
                    .multStr = &mStr_NetTitle,
                };
                Tree_Def *tree_network = Tree_AddNode(tree_setting, &btn_Network);
                {
                    static const struct BtnInfo_Def btn_dhcp = {
                        .type = BTN_TYPE_SEL,  .multStr = &mStr_DHCP,
                        .obj = &ui.Setting_btn_DHCP_label,
                        .evencb = DHCP_handler,
                    };
                    Tree_AddNode(tree_network, &btn_dhcp);
                    Tree_AddNode(tree_network, &btn_ip);
                    Tree_AddNode(tree_network, &btn_netway);
                    Tree_AddNode(tree_network, &btn_gateway);
                    static const struct BtnInfo_Def btn_save = {
                        .type = BTN_TYPE_KEY,    .key_short = LV_KEY_SAVE, .key_long = LV_KEY_DEFAULT,
                        .multStr = &mStr_save,   .obj = &ui.Setting_cont_1,
                    };
                    Tree_AddNode(tree_network, &btn_save);
                }
                //关于本机
                static const struct BtnInfo_Def btn_about = {
                    .type = BTN_TYPE_UI,  .multStr = &mStr_About,
                    .ui_enter = About_Enter,
                    .ui_exit = About_Exit,
                    .obj = &ui.About_cont,
                };
                Tree_Def *tree_about = Tree_AddNode(tree_setting, &btn_about);
                {
                    static const struct BtnInfo_Def btn_loadDefault = {
                        .type = BTN_TYPE_KEY,  .key_short = LV_KEY_LOADDEFAULT, .key_long = LV_KEY_LOADDEFAULT_LONGP,
                        .multStr = &mStr_LoadDefault, .obj = &ui.Setting_cont_1,
                    };
                    Tree_AddNode(tree_about, &btn_loadDefault);
                    Tree_AddNode(tree_about, &btn_esc);
                }
            }
            //用户组
            extern void GroupTable_handler(lv_obj_t *obj, lv_event_t event);
            static const struct BtnInfo_Def btn_group = {
                .multStr = &mStr_Group,
                .type = BTN_TYPE_UI,
                .ui_enter = GroupPage_Enter,
                .ui_exit = GroupPage_Exit,
                .obj = &ui.GroupPage_cont,
                .evencb = GroupTable_handler,
                .noVisable = 0,
            };
            tree_group = Tree_AddNode(tree_menu, &btn_group);
            {
                //保存文件
                Tree_AddNode(tree_group, &btn_group_save);
                //加载文件
                Tree_AddNode(tree_group, &btn_group_load);
                //另存为
                Tree_Def *tree_group_saveAs = Tree_AddNode(tree_group, &btn_group_saveAs);
                {
                    Tree_AddNode(tree_group_saveAs, &btn_Upper);
                    Tree_AddNode(tree_group_saveAs, &btn_Lower);
                    Tree_AddNode(tree_group_saveAs, &btn_Number);
                    //保存
                    Tree_AddNode(tree_group_saveAs, &btn_file_save_flash);
                    Tree_AddNode(tree_group_saveAs, &btn_file_save_udisk);
                }
                Tree_Def *tree_group_rename = Tree_AddNode(tree_group, &btn_file_rename);
                {
                    Tree_AddNode(tree_group_rename, &btn_Upper);
                    Tree_AddNode(tree_group_rename, &btn_Lower);
                    Tree_AddNode(tree_group_rename, &btn_Number);
                    //
                    Tree_AddNode(tree_group_rename, &btn_enter);
                    Tree_AddNode(tree_group_rename, &btn_esc);
                }
                //删除文件
                Tree_AddNode(tree_group, &btn_file_delete);
            }
            //语言设置
            static const struct BtnInfo_Def btn_language = {
                .multStr = &mStr_Language,
                .type = BTN_TYPE_SEL,
                .obj = &ui.Menu_btn_language_label,
                .evencb = Language_handler,
                .noVisable = 1,
            };
            tree_language = Tree_AddNode(tree_menu, &btn_language);
        }
        Tree_UI_Set_EventCb(tree_home);
        ////////
        Tree_UI_Sel_Enter(tree_home, 0);
    }
    return tree_home;
}



Tree_Def *Tree_UI_Set_EventCb(Tree_Def *tree)
{
    if(tree == NULL)
    {
        return NULL;
    }
    Tree_Def *node = NULL;
    if(tree->pdata != NULL) {
        const struct BtnInfo_Def *pdata = tree->pdata;
        if((pdata->obj != NULL)
                && (*pdata->obj != NULL)
                && (pdata->evencb != NULL))
        {
            lv_obj_set_event_cb(*pdata->obj, pdata->evencb);
        }
    }
    if(tree->child != NULL) {
        node = Tree_UI_Set_EventCb(tree->child);
        if(node != NULL) {
            return node;
        }
    }
    if(tree->next != NULL) {
        node = Tree_UI_Set_EventCb(tree->next);
        if(node != NULL) {
            return node;
        }
    }
    return node;
}

/*
 * @brief       void Tree_UI_Sel_Exit(void)
 * @details     返回上一级节点
 */
void Tree_UI_Sel_Exit(void)
{
    Tree_Def *temp_selNode = tree_ui.selNode;
    //像已选对象发送Refresh事件,设置default
    if(temp_selNode != NULL)
    {
        if((temp_selNode->pdata != NULL)
                && (temp_selNode->pdata->obj != NULL)
                && (*temp_selNode->pdata->obj != NULL))
        {
            lv_obj_set_state(*temp_selNode->pdata->obj, LV_STATE_DEFAULT);
            lv_event_send(*temp_selNode->pdata->obj, LV_EVENT_DEFOCUSED, NULL);
            lv_key_t key = LV_KEY_ESC;
            lv_event_send(*temp_selNode->pdata->obj, LV_EVENT_KEY, &key);
            lv_event_send_refresh(*temp_selNode->pdata->obj);
        } else {
            NULL_ERROR();
        }
        tree_ui.selNode = NULL;
        if(temp_selNode->child == NULL) {
            if((tree_ui.uiNode->pdata->obj != NULL)
                    && (*tree_ui.uiNode->pdata->obj != NULL))
            {
                lv_event_send_refresh_recursive(*tree_ui.uiNode->pdata->obj);
            }
            return ;
        }
    } else {
    }
    //若子类不为空,则返回上级
    if((temp_selNode != NULL) && (temp_selNode->child == NULL)) {
    } else {
        if((tree_ui.curNode != NULL) && (tree_ui.curNode->parent != NULL)) {
            Tree_UI_Sel_Enter(tree_ui.curNode->parent, 0);
        }
    }
}
/*
 * @brief       void Tree_UI_Sel_Enter(Tree_Def *node)
 * @details     进入节点
 */
void Tree_UI_Sel_Enter(Tree_Def *node, uint8_t longFlag)
{
    if(node == NULL)
    {
        return ;
    }
    if(node->pdata == NULL)
    {
        return ;
    }
    //按下(非下属)按键退出选定
    {
        //退出当前选中对象节点
        if((tree_ui.selNode != NULL) && (tree_ui.selNode != node))
        {
            Tree_UI_Sel_Exit();
            tree_ui.selNode = NULL;
        }
    }
    const struct BtnInfo_Def *pdata = node->pdata;
    switch(pdata->type)
    {
        //可选对象
        case BTN_TYPE_SEL: {
            //向新目标发送Click事件,设置为Focus状态
            if((pdata->obj == NULL) && (*pdata->obj == NULL))
            {
                return ;
            }
            tree_ui.selNode = node;
            if(lv_obj_get_event_cb(*pdata->obj) != pdata->evencb)
            {
                lv_obj_set_event_cb(*pdata->obj, pdata->evencb);
            }
            lv_event_send(*pdata->obj, LV_EVENT_FOCUSED, NULL);
            lv_event_send(*pdata->obj, LV_EVENT_CLICKED, NULL);
            lv_obj_set_state(*pdata->obj, LV_STATE_FOCUSED);
            //若附带按键,则发送按键
            if(longFlag == 0)
            {
                if(pdata->key_short != LV_KEY_DEFAULT) {
                    lv_event_send(*pdata->obj, LV_EVENT_KEY, &pdata->key_short);
                }
            } else {
                if(pdata->key_long != LV_KEY_DEFAULT) {
                    lv_event_send(*pdata->obj, LV_EVENT_KEY, &pdata->key_long);
                }
            }
            //刷新对象
            lv_obj_invalidate(*pdata->obj);
        }
        break;
        //UI
        case BTN_TYPE_UI: {
            if(tree_ui.uiNode != node) {
                //非子节点,退出UI
                if(0 == Tree_IsChild(tree_ui.uiNode, node))
                {
                    //退出上次UI节点
                    if((tree_ui.uiNode != NULL)
                            && (tree_ui.uiNode->pdata != NULL))
                    {
                        if(tree_ui.uiNode->pdata->ui_exit != NULL)
                        {
                            tree_ui.uiNode->pdata->ui_exit();
                        }
                    }
                }
                //进入新的UI节点
                if(pdata->ui_enter != NULL)
                {
                    pdata->ui_enter();
                }
                tree_ui.uiNode = node;
            }
        }
        break;
        //用来测试的
        case BTN_TYPE_CALL: {
            if(pdata->call != NULL) {
                pdata->call();
            }
        }
        break;
        default:
            break;
    }
    //如果子类不为空,则进入树节点
    if(node != NULL) {
        if(node->child != NULL) {
            tree_ui.curNode = node;
            Tree_Btnm_Load(node);
        }
    }
}
/*
 * @brief       void Tree_UI_Enter(const struct BtnInfo_Def* btnInfo,uint8_t longFlag)
 * @details     虚拟按键进入树节点
 */
void Tree_UI_Enter(const struct BtnInfo_Def *btnInfo, uint8_t longFlag)
{
    if(btnInfo == NULL)
    {
        NULL_ERROR();
        return ;
    }
    //消息框处理
    if(1 == lv_obj_is_visible(ui.MsgBox_cont)) {
        lv_key_t key = LV_KEY_DEFAULT;
        lv_event_send(ui.MsgBox_cont, LV_EVENT_KEY, &key);
        //        return;
    }
    //获取树节点
    Tree_Def *node = Tree_UI_GetNode_byBtn(tree_ui.curNode->child, btnInfo);
    if(node == NULL)
    {
        return ;
    }
    if(Btn_KeyInvalid_CheckBtn(btnInfo) != 0) {
        return ;
    }
    const struct BtnInfo_Def *pdata = node->pdata;
    if(pdata == NULL) {
        NULL_ERROR();
    }
    #if 1
    //发送按键
    if(pdata->type == BTN_TYPE_KEY) {
        lv_key_t key = LV_KEY_DEFAULT;
        if(longFlag == 0) {
            key = pdata->key_short;
        } else {
            key = pdata->key_long;
        }
        if(pdata->obj == NULL) {
            lv_event_send(ui.Back_cont_back, LV_EVENT_KEY, &key);
        } else
            if(*pdata->obj != NULL) {
                //发送至特定的对象
                lv_event_send(*pdata->obj, LV_EVENT_KEY, &key);
            }
    } //else
    #endif
    {
        Tree_UI_Sel_Enter(node, longFlag);
    }
}
/*
 * @brief       Tree_Def* Tree_UI_GetNode_byBtn(Tree_Def* tree,const struct BtnInfo_Def* btnInfo)
 * @details     通过虚拟按键信息 获取 对应节点
 */
Tree_Def *Tree_UI_GetNode_byBtn(Tree_Def *tree, const struct BtnInfo_Def *btnInfo)
{
    if(btnInfo == NULL)
    {
        return NULL;
    }
    if(tree == NULL)
    {
        return NULL;
    }
    Tree_Def *node = NULL;
    if(tree->pdata != NULL) {
        const struct BtnInfo_Def *pdata = tree->pdata;
        if(memcmp(pdata, btnInfo, sizeof(struct BtnInfo_Def)) == 0) {
            return tree;
        }
    }
    //        if(tree->child != NULL) {
    //            node = Tree_UI_GetNode_byBtn(tree->child, btnInfo);
    //            if(node != NULL) { return node; }
    //        }
    //递归
    if(tree->next != NULL) {
        node = Tree_UI_GetNode_byBtn(tree->next, btnInfo);
        if(node != NULL) {
            return node;
        }
    }
    return node;
}
/*
 * @brief       void Tree_Btnm_Refresh(void)
 * @details     刷新虚拟按键
 */
void Tree_Btnm_Refresh(void)
{
    if(tree_ui.curNode == NULL)
    {
        return;
    }
    //逐个添加
    Tree_Def *temp = tree_ui.curNode->child;
    if(temp == NULL)
    {
        return ;
    }
    static struct BtnInfo_Def *KeyInfo = NULL;
    if(KeyInfo != NULL) {
        //释放内存
        Tree_free(KeyInfo);
        KeyInfo = NULL;
    }
    //获取节点数
    uint8_t nodeCout = Tree_GetChildCount(tree_ui.curNode);
    KeyInfo = Tree_malloc((nodeCout + 1) * sizeof(struct BtnInfo_Def));
    if(KeyInfo == NULL) {
        DEBUG("malloc Failed!\r\n");
        return ;
    }
    memset(KeyInfo, 0, (nodeCout + 1)*sizeof(struct BtnInfo_Def));
    struct BtnInfo_Def *tempInfo = KeyInfo;
    do {
        const struct BtnInfo_Def *pdata = temp->pdata;
        if((pdata != NULL) && (pdata->multStr != NULL))
        {
            memcpy(tempInfo, pdata, sizeof(struct BtnInfo_Def));
            tempInfo++;
        }
        temp = temp->next;
    } while(temp != NULL);
    //刷新按键
    VirtualBtnm_SetBtnmInfo(KeyInfo);
    //
    lv_label_set_text_static(ui.Bar_btn_title_label, MultStr_GetS(tree_ui.uiNode->pdata->multStr));
}
/*
 * @brief       void Tree_Btnm_Load(Tree_Def* tree)
 * @details     加载虚拟按键
 */
void Tree_Btnm_Load(Tree_Def *tree)
{
    if(tree == NULL) {
        return ;
    }
    tree_ui.curNode = tree;
    Tree_Btnm_Refresh();
}
/*
 * @brief       void Tree_Btnm_Replace(Tree_Def* tree,const struct BtnInfo_Def* btn1,const struct BtnInfo_Def* btn2)
 * @details     替代按键
 */
void Tree_Btnm_Replace(Tree_Def *tree, const struct BtnInfo_Def *btn1, const struct BtnInfo_Def *btn2)
{
    if(tree == NULL)
    {
        return;
    }
    if(tree->child == NULL)
    {
        return ;
    }
    if((btn1 == NULL) || (btn2 == NULL))
    {
        return ;
    }
    Tree_Def *node = NULL;
    node = Tree_UI_GetNode_byBtn(tree->child, btn1);
    if(node != NULL) {
        node->pdata = btn2;
        if(tree_ui.curNode == tree)
        {
            Tree_Btnm_Refresh();
        }
    }
}
/*
 * @brief       void btnTree_event_handler(lv_obj_t *obj, lv_event_t event)
 * @details
 */
#include "MsgBox.h"
void btnTree_event_handler(lv_obj_t *obj, lv_event_t event)
{
    if(event != LV_EVENT_KEY) {
        return ;
    }
    lv_key_t key = LV_KEY_DEFAULT;
    key = *(lv_key_t *)lv_event_get_data();
    if(key != LV_KEY_RETURN)
    {
        //校准数据弹窗处理
        if(1 == CalibPage_isVisable()) {
            CalibPage_Exit();
            return ;
        }
        //输入框处理
        if(lv_obj_is_visible(ui.InputWidget_cont_inputVal)) {
            extern void InputVal_handler(lv_obj_t *obj, lv_event_t event);
            obj = ui.InputWidget_btn_ValInput_label;
            InputVal_handler(obj, event);
            return;
        }
        if(Btn_KeyInvalid_CheckKey(key)) {
        } else {
            //系统按键处理
            extern uint8_t System_Key_Process(lv_key_t key);
            if(System_Key_Process(key) != 0) {
            } else {
                //消息框处理
                if(1 == lv_obj_is_visible(ui.MsgBox_cont)) {
                    lv_event_send(ui.MsgBox_cont, event, &key);
                    return;
                }
                //
                if((tree_ui.selNode != NULL) && (tree_ui.uiNode->pdata->obj != NULL) && (*tree_ui.uiNode->pdata->obj != NULL))
                {
                    if(lv_obj_get_event_cb(*tree_ui.uiNode->pdata->obj) != tree_ui.uiNode->pdata->evencb)
                    {
                        lv_obj_set_event_cb(*tree_ui.uiNode->pdata->obj, tree_ui.uiNode->pdata->evencb);
                    }
                    lv_event_send(*tree_ui.selNode->pdata->obj, event, &key);
                } else {
                    if((tree_ui.uiNode->pdata->obj != NULL)
                            && (tree_ui.uiNode->pdata->evencb != NULL))
                    {
                        if(lv_obj_get_event_cb(*tree_ui.uiNode->pdata->obj) != tree_ui.uiNode->pdata->evencb)
                        {
                            lv_obj_set_event_cb(*tree_ui.uiNode->pdata->obj, tree_ui.uiNode->pdata->evencb);
                        }
                        switch(event)
                        {
                            case LV_EVENT_KEY: {
                                switch(key) {
                                    default: {
                                        lv_event_send(*tree_ui.uiNode->pdata->obj, event, &key);
                                    }
                                    break;
                                }
                            }
                            break;
                            default: {
                                lv_event_send(*tree_ui.uiNode->pdata->obj, event, NULL);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    key = *(lv_key_t *)lv_event_get_data();
    if((event == LV_EVENT_KEY) && ((key == LV_KEY_ESC) || (key == LV_KEY_RETURN)))
    {
        Tree_UI_Sel_Exit();
    }
}
/*
 * @brief       static uint32_t Tree_GetObjCount(const Tree_Def* tree)
 * @details     获取可选节点数
 */
static uint32_t Tree_GetObjCount(const Tree_Def *tree)
{
    uint32_t count = 0;
    if(tree != NULL)
    {
        if(tree->pdata != NULL)
        {
            const struct BtnInfo_Def *pdata = tree->pdata;
            if(pdata->type == BTN_TYPE_MORE) {
                //查询更多
                if(tree->child != NULL) {
                    count += Tree_GetObjCount(tree->child);
                }
            } else
                if(pdata->type == BTN_TYPE_SEL) {
                    //计数
                    if((pdata->obj != NULL) && (*pdata->obj != NULL)) {
                        count++;
                    }
                }
        }
        if(tree->next != NULL) {
            count += Tree_GetObjCount(tree->next);
        }
    }
    return count;
}
/*
 * @brief       Tree_Def* Tree_UI_GetNode_ByObj(Tree_Def* tree,lv_obj_t* obj)
 * @details     通过对象 获取 对应节点
 */
Tree_Def *Tree_UI_GetNode_ByObj(Tree_Def *tree, lv_obj_t *obj)
{
    if(obj == NULL)
    {
        return NULL;
    }
    if(tree == NULL)
    {
        return NULL;
    }
    Tree_Def *node = NULL;
    if(tree != NULL)
    {
        if(tree->pdata != NULL) {
            const struct BtnInfo_Def *pdata = tree->pdata;
            if(*pdata->obj == obj) {
                return tree;
            }
        }
        if(tree->child != NULL) {
            node = Tree_UI_GetNode_ByObj(tree->child, obj);
            if(node != NULL) {
                return node;
            }
        }
        if(tree->next != NULL) {
            node = Tree_UI_GetNode_ByObj(tree->next, obj);
            if(node != NULL) {
                return node;
            }
        }
    }
    return node;
}