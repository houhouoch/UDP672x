#ifndef _BTN_TREE_H_
#define _BTN_TREE_H_

#include "tree.h"

Tree_Def *UI_Tree_Init(void);

#include "Commd.h"

#include "HomePage.h"
#include "HomePage_2.h"

#include "ListOut.h"
#include "ListPage.h"
#include "List_Interface.h"
#include "ListPage_Table.h"
#include "ListPage_Option.h"
#include "ListPage_Manager.h"
#include "ListTempPage.h"

#include "MonitorPage.h"

#include "OutOptionPage.h"
#include "OutOptionPage_item.h"

#include "DelayOut.h"
#include "Delay_Interface.h"
#include "DelayOutPage.h"
#include "DelayOutPage_Table.h"
#include "DelayPage_Option.h"
#include "DelayPage_Manager.h"
#include "DelayTempPage.h"

#include "BatTesterPage.h"
#include "BatTesterPage_Table.h"
#include "BatTester_Option.h"
#include "BatTester_Manager.h"

#include "Trigger.h"
#include "TriggerPage.h"

#include "PresetPage.h"

#include "MenuPage.h"
#include "SettingPage.h"
#include "GroupPage.h"
#include "CalibPage.h"
#include "VirtualBtnm.h"



extern const struct BtnInfo_Def btn_enter;
extern const struct BtnInfo_Def btn_esc;

extern const struct BtnInfo_Def btn_left;
extern const struct BtnInfo_Def btn_right;
extern const struct BtnInfo_Def btn_up;
extern const struct BtnInfo_Def btn_down;

extern const struct BtnInfo_Def btn_on;
extern const struct BtnInfo_Def btn_off;
extern const struct BtnInfo_Def btn_start;
extern const struct BtnInfo_Def btn_contiune;
extern const struct BtnInfo_Def btn_stop;
extern const struct BtnInfo_Def btn_pause;

extern const struct BtnInfo_Def btn_M1;
extern const struct BtnInfo_Def btn_M2;
extern const struct BtnInfo_Def btn_M3;
extern const struct BtnInfo_Def btn_M4;
extern const struct BtnInfo_Def btn_M5;
//字符串输入 临时键盘
extern const struct BtnInfo_Def btn_Upper;
extern const struct BtnInfo_Def btn_Lower;
extern const struct BtnInfo_Def btn_Number;



void Tree_UI_Sel_Enter(Tree_Def *node, uint8_t longFlag);

/*
 * @brief       void Tree_Btnm_Refresh(void)
 * @details     刷新虚拟按键
 */
void Tree_Btnm_Refresh(void);

/*
 * @brief       void Tree_Btnm_Load(Tree_Def* tree)
 * @details     加载虚拟按键
 */
void Tree_Btnm_Load(Tree_Def *tree);

/*
 * @brief       void Tree_Btnm_Replace(Tree_Def* tree,const struct BtnInfo_Def* btn1,const struct BtnInfo_Def* btn2)
 * @details     替代按键
 */
void Tree_Btnm_Replace(Tree_Def *tree, const struct BtnInfo_Def *btn1, const struct BtnInfo_Def *btn2);

/*
 * @brief       Tree_Def* Tree_UI_GetNode_byBtn(Tree_Def* tree,const struct BtnInfo_Def* btnInfo)
 * @details     通过按键信息 获取 对应节点
 */
Tree_Def *Tree_UI_GetNode_byBtn(Tree_Def *tree, const struct BtnInfo_Def *btnInfo);


/*
 * @brief       void btnTree_event_handler(lv_obj_t *obj, lv_event_t event)
 * @details
 */
void btnTree_event_handler(lv_obj_t *obj, lv_event_t event);


/*
 * @brief       void Tree_UI_Sel_Exit(void)
 * @details     返回上一级节点
 */
void Tree_UI_Sel_Exit(void);
/*
 * @brief       void Tree_UI_Enter(const struct BtnInfo_Def* btnInfo,uint8_t longFlag)
 * @details     虚拟按键进入树节点
 */
void Tree_UI_Enter(const struct BtnInfo_Def *btnInfo, uint8_t longFlag);


void Group_Esc_Call(void);




/*
 * @brief       void UI_Switch_Page(uint8_t page)
 * @details     切换页面
 */
void UI_Switch_Page(uint8_t page);



//主页
//输出电压设置
extern const struct BtnInfo_Def btn_VSet;
//输出电流设置
extern const struct BtnInfo_Def btn_ISet;
//电压限制
extern const struct BtnInfo_Def btn_Vlimit;
//电流限制
extern const struct BtnInfo_Def btn_Ilimit;
//定时关闭
extern const struct BtnInfo_Def btn_TimeOff;

//输出电压设置
extern const struct BtnInfo_Def btn_VSet_2;
//输出电流设置
extern const struct BtnInfo_Def btn_ISet_2;
//电压限制
extern const struct BtnInfo_Def btn_Vlimit_2;
//电流限制
extern const struct BtnInfo_Def btn_Ilimit_2;
//定时关闭
extern const struct BtnInfo_Def btn_TimeOff_2;


//序列输出
//起始点
extern const struct BtnInfo_Def btn_list_start;
//结束点
extern const struct BtnInfo_Def btn_list_Groups;
//循环次数
extern const struct BtnInfo_Def btn_list_cycle;
//末态
extern const struct BtnInfo_Def btn_list_endState;
//表格
extern const struct BtnInfo_Def btn_list_table;
//管理
extern const struct BtnInfo_Def btn_list_manage;




//DelayOut输出
//起始点
extern const struct BtnInfo_Def btn_delay_start;
//结束点
extern const struct BtnInfo_Def btn_delay_Groups;
//循环次数
extern const struct BtnInfo_Def btn_delay_cycle;
//保护值
extern const struct BtnInfo_Def btn_delay_stopVal;
//动作
extern const struct BtnInfo_Def btn_delay_endState;

//表格
extern const struct BtnInfo_Def btn_delay_table;
//管理
extern const struct BtnInfo_Def btn_delay_manage;

#if 1
    extern const struct BtnInfo_Def btn_Battest_option;
    extern const struct BtnInfo_Def btn_Battest_start;
    extern const struct BtnInfo_Def btn_Battest_Groups;
    extern const struct BtnInfo_Def btn_Battest_cycle;
    extern const struct BtnInfo_Def btn_Battest_table;
    extern const struct BtnInfo_Def btn_Battest_manage;
#endif


//工作模式
extern const struct BtnInfo_Def btn_Mode;
//斜率模式
extern const struct BtnInfo_Def btn_SR_Mode;
//斜率设置
extern struct BtnInfo_Def btn_SR_Set;
//电压斜率
extern struct BtnInfo_Def btn_VSR_Rising;
extern struct BtnInfo_Def btn_VSR_Failing;
//电流斜率
extern struct BtnInfo_Def btn_ISR_Rising;
extern struct BtnInfo_Def btn_ISR_Failing;

extern Tree_Def *tree_SR_Set;
extern Tree_Def *tree_VSR_Up_Set;
extern Tree_Def *tree_VSR_Dn_Set;
extern Tree_Def *tree_ISR_Up_Set;
extern Tree_Def *tree_ISR_Dn_Set;

//网络设置
extern const struct BtnInfo_Def btn_ip;
extern const struct BtnInfo_Def btn_gateway;
extern const struct BtnInfo_Def btn_netway;
//Preset
extern const struct BtnInfo_Def btn_preset_save;
extern const struct BtnInfo_Def btn_preset_load;
//Group
extern const struct BtnInfo_Def btn_group_save;
extern const struct BtnInfo_Def btn_group_load;
extern const struct BtnInfo_Def btn_group_saveAs;


#endif