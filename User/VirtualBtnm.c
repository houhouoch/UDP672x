#include "VirtualBtnm.h"

//各界面按�?
#include "BtnTree.h"
#include "HomePage.h"
#include "ListPage.h"
#include "DelayOutPage.h"
#include "SettingPage.h"

typedef struct {
    uint16_t count;
    uint16_t baseIdx;
    const struct BtnInfo_Def *btnInfo;
} btnStruct;

enum {
    STATUS_CURRENT,     //显示当前节点按键
};

typedef struct {
    btnStruct curBtns;      //
    uint8_t status;
    const struct BtnInfo_Def *dispBtnInfo[6];
} BtnsInfo_Def;

static BtnsInfo_Def btnsInfo = {
    .status = STATUS_CURRENT,
};

static void VirtualBtnm_Refresh(void);
static void VirtualBtnm_event_handler(lv_obj_t *obj, lv_event_t event);
static void __KeyProcess(uint8_t index, uint8_t longFlag);


/*
 * @brief       static btnStruct* __GetBtns_toDisplay(void)
 * @details     获取当前应�?显示的按�?���?
 */
static btnStruct *__GetBtns_toDisplay(void)
{
    switch(btnsInfo.status)
    {
        case STATUS_CURRENT:
            return &btnsInfo.curBtns;
    }
    return NULL;
}



static void VirtualBtnm_event_handler(lv_obj_t *obj, lv_event_t event)
{
    if(obj == NULL)
    {
        return ;
    }
    switch(event)
    {
        //刷新事件
        case LV_EVENT_REFRESH: {
            VirtualBtnm_Refresh();
        }
        break;
        case LV_EVENT_KEY:
        {
            lv_key_t key = *(lv_key_t *)lv_event_get_data();
            uint8_t longFlag = 1;
            switch(key)
            {
                case LV_KEY_F1:
                case LV_KEY_F2:
                case LV_KEY_F3:
                case LV_KEY_F4:
                case LV_KEY_F5:
                case LV_KEY_F6:
                    longFlag = 0;
                case LV_KEY_F1_LONGP:
                case LV_KEY_F2_LONGP:
                case LV_KEY_F3_LONGP:
                case LV_KEY_F4_LONGP:
                case LV_KEY_F5_LONGP:
                case LV_KEY_F6_LONGP: {
                    BEEP_OK();
                    uint8_t idx = 0xff;
                    if((LV_KEY_F1 <= key) && (key <= LV_KEY_F6)) {
                        idx = key - LV_KEY_F1;
                    } else
                        if((LV_KEY_F1_LONGP <= key)
                                && (key <= LV_KEY_F6_LONGP)) {
                            idx = key - LV_KEY_F1_LONGP;
                        }
                    //取消选中
                    //                    lv_btnmatrix_set_focused_btn(obj, LV_BTNMATRIX_BTN_NONE);
                    lv_obj_set_hidden(ui.BtnBar_img_keydown, 1);
                    if(idx != 0xff)
                    {
                        if(btnsInfo.dispBtnInfo[idx] != NULL)
                        {
                            //按键屏蔽
                            extern uint8_t Btn_KeyInvalid_CheckKey(lv_key_t key);
                            if(Btn_KeyInvalid_CheckKey(key)) {
                                break;
                            }
                            printf("%s\r\n", MultStr_GetS(btnsInfo.dispBtnInfo[idx]->multStr));
                            __KeyProcess(idx, longFlag);
                        }
                    }
                }
                break;
                case LV_KEY_F1_HOLD:
                case LV_KEY_F2_HOLD:
                case LV_KEY_F3_HOLD:
                case LV_KEY_F4_HOLD:
                case LV_KEY_F5_HOLD:
                case LV_KEY_F6_HOLD: {
                    uint8_t idx = key - LV_KEY_F1_HOLD;
                    //选中
                    //                    lv_btnmatrix_set_focused_btn(ui.BtnBar_btnm, idx);
                    lv_obj_set_hidden(ui.BtnBar_img_keydown, 0);
                    lv_obj_set_pos(ui.BtnBar_img_keydown, 80 * idx, 1);
                }
                break;
                //�?��到后�?
                default: {
                    if((key != LV_KEY_UP) && (key != LV_KEY_DOWN)) {
                        BEEP_OK();
                    }
                    //按键屏蔽
                    extern uint8_t Btn_KeyInvalid_CheckKey(lv_key_t key);
                    if(Btn_KeyInvalid_CheckKey(key)) {
                        break;
                    }
                    lv_event_send(ui.Back_cont_back, LV_EVENT_KEY, &key);
                }
                break;
            }
        }
        break;
    }
}







/* ----------- 虚拟按键 -------- */
struct BtnInfo_Def PageDown_UpButtons[] = {
    {   .type = BTN_TYPE_PGUP, .multStr = &mStr_PageUp},
    {   .type = BTN_TYPE_PGDN, .multStr = &mStr_PageDown},
};

/*
 * @brief       void VirtualBtnm_SetBtnmInfo(const struct BtnInfo_Def* info)
 * @details     设置按键表信�?
 */
void VirtualBtnm_SetBtnmInfo(const struct BtnInfo_Def *info)
{
    btnsInfo.curBtns.btnInfo = info;
    btnsInfo.curBtns.count = 0;
    btnsInfo.curBtns.baseIdx = 0;
    //获取长度
    if(info != NULL)
    {
        for(uint8_t i = 0;; ++i)
        {
            if(btnsInfo.curBtns.btnInfo[i].multStr != NULL) {
                if(btnsInfo.curBtns.btnInfo[i].noVisable == 0) {
                    btnsInfo.curBtns.count++;
                }
            } else {
                break;
            }
        }
        VirtualBtnm_Refresh();
    }
}





void VirtualBtnm_GroupCreate(void)
{
    {
        setup_scr_BtnBar(&ui);
        lv_obj_set_parent(ui.BtnBar_cont_Btnm, ui.Back_cont_back);
        lv_obj_set_top(ui.BtnBar_cont_Btnm, 1);
    }
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_1_label);
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_2_label);
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_3_label);
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_4_label);
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_5_label);
    UI_BtnMatrix_Style_Load(ui.BtnBar_btn_6_label);
    lv_obj_set_event_cb(ui.BtnBar_cont_Btnm, VirtualBtnm_event_handler);
    lv_obj_set_hidden(ui.BtnBar_img_keydown, 1);
}

//<=6�?         //6+0
//>6�? <=10�?   //5+1
//>10�?         //5+1 4+2 5+1
//0  5  5+4 5+4+4
static uint8_t __GetBtn_PageCount(void)
{
    btnStruct *pBtns = __GetBtns_toDisplay();
    if(pBtns->count <= 6) {
        return 1;
    }
    uint16_t page = 0;
    for(uint8_t i = 0;; ++i) {
        uint16_t pageCount = 0;
        pageCount = (5 + 1) + (i * 4) + (5 + 1);
        if(pBtns->count <= pageCount) {
            return (page + 2);
        } else {
            ++page;
        }
    }
}

static uint8_t __isFontPage(void)
{
    btnStruct *pBtns = __GetBtns_toDisplay();
    return (pBtns->baseIdx == 0);
}

static uint8_t __isBackPage(void)
{
    btnStruct *pBtns = __GetBtns_toDisplay();
    return (abs(pBtns->baseIdx - pBtns->count) <= 5);
}
/*
 * @brief       static void VirtualBtnm_PageUp(void)
 * @details     上一�?
 */
uint8_t count = 0;
static void VirtualBtnm_PageUp(void)
{
    btnStruct *pBtns = __GetBtns_toDisplay();
    if(pBtns == NULL) while(1);
    int8_t idx = pBtns->baseIdx;
    idx -= count;
    if(idx < 0) {
        idx = 0;
    }
    pBtns->baseIdx = idx;
    VirtualBtnm_Refresh();
}

/*
 * @brief       static void VirtualBtnm_PageDown(void)
 * @details     下一�?
 */
static void VirtualBtnm_PageDown(void)
{
    btnStruct *pBtns = __GetBtns_toDisplay();
    if(pBtns == NULL) while(1);
    //    if(__isFontPage())
    //        count = 5;
    //    else
    //        count = 4;
    count = 4;
    if(pBtns->baseIdx <= (pBtns->count - count)) {
        pBtns->baseIdx += count;
        VirtualBtnm_Refresh();
    }
}

uint16_t pageCount = 0;

static void VirtualBtnm_Refresh(void)
{
    static const char *btnm_map[7] = {"", "", "", "", "", "", ""};
    uint8_t mapCount = 0;
    btnStruct *pBtns = __GetBtns_toDisplay();
    if(pBtns == NULL) while(1);
    pageCount = __GetBtn_PageCount();
    for(uint8_t i = 0; i < 6; ++i)
    {
        if(pageCount <= 1) {
            if(((pBtns->baseIdx + i) < pBtns->count)
                    && (pBtns->btnInfo != NULL)
                    && (pBtns->btnInfo[pBtns->baseIdx + i].multStr != NULL)
                    && (pBtns->btnInfo[pBtns->baseIdx + i].noVisable == 0))
            {
                btnsInfo.dispBtnInfo[i] = &pBtns->btnInfo[pBtns->baseIdx + i];
            } else {
                btnsInfo.dispBtnInfo[i] = NULL;
            }
        } else {
            if(__isFontPage())
            {
                if(i == 5) {
                    btnsInfo.dispBtnInfo[i] = &PageDown_UpButtons[1];
                    btnm_map[mapCount] = MultStr_GetS(btnsInfo.dispBtnInfo[i]->multStr);
                    mapCount++;
                    continue;
                }
            } else
                if(__isBackPage()) {
                    if(i == 5) {
                        btnsInfo.dispBtnInfo[i] = &PageDown_UpButtons[0];
                        btnm_map[mapCount] = MultStr_GetS(btnsInfo.dispBtnInfo[i]->multStr);
                        mapCount++;
                        continue;
                    }
                } else
                    if((!__isFontPage()) && (!__isBackPage())) {
                        if(i == 4) {
                            btnsInfo.dispBtnInfo[i] = &PageDown_UpButtons[0];
                            btnm_map[mapCount] = MultStr_GetS(btnsInfo.dispBtnInfo[i]->multStr);
                            mapCount++;
                            continue;
                        } else
                            if(i == 5) {
                                btnsInfo.dispBtnInfo[i] = &PageDown_UpButtons[1];
                                btnm_map[mapCount] = MultStr_GetS(btnsInfo.dispBtnInfo[i]->multStr);
                                mapCount++;
                                continue;
                            }
                    }
            if(((pBtns->baseIdx + i) < pBtns->count)
                    && (pBtns->btnInfo != NULL)
                    && (pBtns->btnInfo[pBtns->baseIdx + i].multStr != NULL)
                    && (pBtns->btnInfo[pBtns->baseIdx + i].noVisable == 0))
            {
                btnsInfo.dispBtnInfo[i] = &pBtns->btnInfo[pBtns->baseIdx + i];
            } else {
                btnsInfo.dispBtnInfo[i] = NULL;
            }
        }
        //
        if(btnsInfo.dispBtnInfo[i] != NULL)
        {
            btnm_map[mapCount] = MultStr_GetS(btnsInfo.dispBtnInfo[i]->multStr);
        } else {
            btnm_map[mapCount] = " ";
        }
        mapCount++;
    }
    for(uint8_t i = 0; i < 6; ++i) {
        switch(i) {
            case 0:
                lv_label_set_text_static(ui.BtnBar_btn_1_label, btnm_map[i]);
            case 1:
                lv_label_set_text_static(ui.BtnBar_btn_2_label, btnm_map[i]);
            case 2:
                lv_label_set_text_static(ui.BtnBar_btn_3_label, btnm_map[i]);
            case 3:
                lv_label_set_text_static(ui.BtnBar_btn_4_label, btnm_map[i]);
            case 4:
                lv_label_set_text_static(ui.BtnBar_btn_5_label, btnm_map[i]);
            case 5:
                lv_label_set_text_static(ui.BtnBar_btn_6_label, btnm_map[i]);
        }
    }
}



static void __KeyProcess(uint8_t index, uint8_t longFlag)
{
    if(btnsInfo.dispBtnInfo[index] != NULL) {
        switch(btnsInfo.dispBtnInfo[index]->type)
        {
            case BTN_TYPE_PGUP: {
                VirtualBtnm_PageUp();
            }
            break;
            case BTN_TYPE_PGDN: {
                VirtualBtnm_PageDown();
            }
            break;
            default: {
                Tree_UI_Enter(btnsInfo.dispBtnInfo[index], longFlag);
            }
            break;
        }
    }
}

/* ------------------------------------------------------------- */



