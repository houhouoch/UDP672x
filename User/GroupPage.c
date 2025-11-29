#include "GroupPage.h"

Tree_Def *tree_group;

#undef TABLE_ROW_CNT
#undef TABLE_COL_CNT
#define TABLE_ROW_CNT   9//行 
#define TABLE_COL_CNT   3//列


#define MIN_ROW (1)
#define MAX_ROW (TABLE_ROW_CNT-1)
static uint16_t edit_row_y = MIN_ROW;  //行数 [1,8]
static uint16_t disp_baseIndex = 0;

//按键表格
static lv_obj_t *table_label[TABLE_ROW_CNT][TABLE_COL_CNT] = {0};
static uint16_t table_x = 1;
static const uint16_t table_y = 11;
static const uint16_t table_width[TABLE_COL_CNT] = {60, 80, 326};
static const uint16_t table_height = 21;



static void __Table_DrawLine(lv_obj_t *backg)
{
    static lv_point_t line_point_V[] = {{0, 0}, {470, 0}};
    static lv_point_t line_point_H[] = {{0, 0}, {0, 203}};
    uint16_t line_V_Count = (sizeof(table_label) / sizeof(table_label[0]));
    for(uint8_t i = 0; i < line_V_Count; ++i) {
        //横线
        uint16_t x_v = lv_obj_get_x(table_label[i][0]) - 1;
        uint16_t y_v = lv_obj_get_y(table_label[i][0]) - 1;
        if(i == 0) {
            y_v = 6;
        }
        lv_obj_t *line_V = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_V, x_v, y_v);
        lv_obj_set_size(line_V, 470, 0);
        lv_line_set_points(line_V, line_point_V, 2);
        lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(i == (line_V_Count - 1)) {
            y_v += table_height + 1;
            line_V = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_V, x_v, y_v);
            lv_obj_set_size(line_V, 470, 0);
            lv_line_set_points(line_V, line_point_V, 2);
            lv_obj_set_style_local_line_color(line_V, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        }
    }
    uint16_t line_H_Count = (sizeof(table_label[0]) / sizeof(table_label[0][0]));
    for(uint8_t j = 0; j < line_H_Count; ++j) {
        //竖线
        uint16_t x_h = lv_obj_get_x(table_label[0][j]) - 1;
        uint16_t y_h = 6;
        lv_obj_t *line_H = lv_line_create(backg, NULL);
        lv_obj_set_pos(line_H, x_h, y_h);
        lv_obj_set_size(line_H, 0, 203);
        lv_line_set_points(line_H, line_point_H, 2);
        lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        if(j == (line_H_Count - 1)) {
            x_h += lv_obj_get_width(table_label[0][j]) + 1;
            line_H = lv_line_create(backg, NULL);
            lv_obj_set_pos(line_H, x_h, y_h);
            lv_obj_set_size(line_H, 0, 203);
            lv_line_set_points(line_H, line_point_H, 2);
            lv_obj_set_style_local_line_color(line_H, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x22, 0x22, 0x22));
        }
    }
}

static void __Table_Init(void)
{
    lv_obj_t *backg = ui.GroupPage_cont;
    for(uint8_t i = 0; i < (sizeof(table_label) / sizeof(table_label[0])); ++i)
    {
        table_x = 5 + 1;
        for(uint8_t j = 0; j < (sizeof(table_label[0]) / sizeof(table_label[0][0])); ++j)
        {
            lv_obj_t *label = lv_label_create(backg, NULL);
            lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
            if(j > 0)
            {
                table_x += table_width[j - 1] + 1;
            }
            extern lv_font_t MultFont_16;
            lv_obj_set_style_local_text_letter_space(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 2);
            if(i == 0) {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &MultFont_16);
                lv_obj_set_size(label, table_width[j], table_height);
                lv_obj_set_pos(label, table_x, table_y);
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 255, 255));
            } else {
                lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_AlibabaPuHuiTi_Light_16);
                lv_obj_set_size(label, table_width[j], table_height);
                lv_obj_set_pos(label, table_x, table_y + ((table_height + 1 + 1) + (i - 1) * (table_height + 1)));
                lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
            }
            table_label[i][j] = label;
            lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
        }
    }
    __Table_DrawLine(backg);
}






//文件信息
static uint16_t itemCount = 0;
#include "LinkList.h"
static LinkList_Def *GroupFile_listHead = NULL;

static FRESULT FATFS_FindFile_Recursive(const char *device, const char *path, const char *fileName)
{
    return FATFS_find(GroupFile_listHead, device, path, fileName);
}












/*
 * @brief
 * @details
 */
static void __Table_setFocus(uint16_t *row_y)
{
    if(row_y == NULL)
    {
        return ;
    }
    edit_row_y = *row_y;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    for(uint8_t i = 0; i < TABLE_COL_CNT; ++i) {
        width += lv_obj_get_width(table_label[edit_row_y][i]);
    }
    height = table_height + 1;
    width += TABLE_COL_CNT - 1;
    x = lv_obj_get_x(table_label[edit_row_y][0]);
    y = lv_obj_get_y(table_label[edit_row_y][0]);
    lv_obj_set_size(ui.GroupPage_img_itemSel, width, height);
    lv_obj_set_pos(ui.GroupPage_img_itemSel, x, y);
    lv_obj_set_hidden(ui.GroupPage_img_itemSel, 0);
}

/*
 * @brief
 * @details     刷新特定行
 */
static void __Tabel_Refresh_Row(uint16_t baseIndex, uint16_t i)
{
    if(itemCount <= 0) {
        return;
    }
    const LinkList_Def *pnode = LinkList_At(GroupFile_listHead, i);
    if(pnode == NULL) {
        return ;
    }
    char tempString[128] = {0};
    sprintf(tempString, "%d", i);
    lv_label_set_text(table_label[i - baseIndex + 1][0], tempString);
    sprintf(tempString, "%s", pnode->device);
    lv_label_set_text(table_label[i - baseIndex + 1][1], tempString);
    sprintf(tempString, "%s", pnode->fileName);
    lv_label_set_text(table_label[i - baseIndex + 1][2], tempString);
}

/*
 * @brief       表格刷新
 * @details
 */
static void __Table_Refresh(uint16_t baseIndex)
{
    if(lv_obj_is_visible(ui.GroupPage_cont) == 0)
    {
        return ;
    }
    uint16_t maxindex = baseIndex + (TABLE_ROW_CNT - 1);
    //限制显示数量
    if(maxindex > (itemCount)) {
        maxindex = (itemCount);
    }
    uint16_t i = 0;
    for(i = baseIndex; i < maxindex; ++i) {
        __Tabel_Refresh_Row(baseIndex, i);
    }
    //其余不显示的行,全清空
    for(; (i - baseIndex + 1) <= MAX_ROW; ++i) {
        lv_label_set_text(table_label[i - baseIndex + 1][0], "");
        lv_label_set_text(table_label[i - baseIndex + 1][1], "");
        lv_label_set_text(table_label[i - baseIndex + 1][2], "");
    }
}


//获取当前聚焦的文件全名(带路径)
static const char *__GetFocusFileName(void)
{
    LinkList_Def *current = LinkList_At(GroupFile_listHead, disp_baseIndex + edit_row_y - MIN_ROW);
    if(current != NULL) {
        return current->path;
    } else {
        return "";
    }
}

static const LinkList_Def *__GetCurrentList(void)
{
    LinkList_Def *current = LinkList_At(GroupFile_listHead, disp_baseIndex + edit_row_y - MIN_ROW);
    return current;
}

#include "InputWidget.h"
//保存文件
#define MAX_SAVE_FILENAME_LEN 128
static char fileName[MAX_SAVE_FILENAME_LEN] = "";

static uint8_t Group_Rename(const char *oldname, const char *newname);
static void Group_Delete(const char *name);

void GroupTable_handler(lv_obj_t *obj, lv_event_t event)
{
    obj = obj;
    lv_key_t key = *(lv_key_t *)lv_event_get_data();
    if(lv_obj_is_visible(ui.InputWidget_cont_inputString)) {
        InputVal_StringEdit_handler(obj, event);
        if(event == LV_EVENT_KEY)
        {
            //检测文件名是否重复
            char fileName_temp[MAX_SAVE_FILENAME_LEN] = {0};
            sprintf(fileName_temp, "%s.user", fileName);
            uint8_t result = 1;
            switch(key) {
                case LV_KEY_SAVE_FLASH: {
                    result = LinkList_Find_duplicate(GroupFile_listHead, "FLASH", fileName_temp);
                }
                break;
                case LV_KEY_SAVE_UDISK: {
                    result = LinkList_Find_duplicate(GroupFile_listHead, "USB", fileName_temp);
                }
                break;
                case LV_KEY_ENTER: {
                    const LinkList_Def *current = __GetCurrentList();
                    if(current != NULL) {
                        if(0 == strcmp("USB", current->device)) {
                            result = LinkList_Find_duplicate(GroupFile_listHead, "USB", fileName_temp);
                        } else
                            if(0 == strcmp("FLASH", current->device)) {
                                result = LinkList_Find_duplicate(GroupFile_listHead, "FLASH", fileName_temp);
                            }
                    } else {
                        result = 0; //非法
                    }
                }
                break;
            }
            if(result == 0) {
                //文件出现重复名
                IF_MsgBox_Tips_Mult(&mStr_FileName_Duplicate_Tips);
            } else {
                char savefileName[MAX_SAVE_FILENAME_LEN + 10] = {0};
                if(key == LV_KEY_SAVE_FLASH) {
                    //另存为到U盘
                    sprintf(savefileName, "%s/%s.user", GROUP_FILE_FLASH_PATH, fileName);
                    if(0 != Group_Save(&CurGroup, savefileName)) {
                        IF_MsgBox_Tips_Mult(&mStr_Save_Tips);
                    }
                } else
                    if(key == LV_KEY_SAVE_UDISK) {
                        //另存为到USB
                        sprintf(savefileName, "%s/%s.user", GROUP_FILE_USB_PATH, fileName);
                        if(0 != Group_Save(&CurGroup, savefileName)) {
                            IF_MsgBox_Tips_Mult(&mStr_Save_Tips);
                        }
                    } else
                        if(key == LV_KEY_ENTER) {
                            //重命名
                            const LinkList_Def *current = __GetCurrentList();
                            if(current != NULL) {
                                if(0 == strcmp("FLASH", current->device)) {
                                    sprintf(savefileName, "%s/%s.user", GROUP_FILE_FLASH_PATH, fileName);
                                    if(0 != Group_Rename(current->path, savefileName)) {
                                        Group_Delete(current->path);
                                    }
                                } else
                                    if(0 == strcmp("USB", current->device)) {
                                        sprintf(savefileName, "%s/%s.user", GROUP_FILE_USB_PATH, fileName);
                                        if(0 != Group_Rename(current->path, savefileName)) {
                                            Group_Delete(current->path);
                                        }
                                    }
                            }
                        }
            }
            lv_event_send_refresh_recursive(ui.GroupPage_cont);
        }
        return;
    }
    uint8_t refreshFlag = 0;
    switch(event)
    {
        case LV_EVENT_KEY:
        {
            switch(key)
            {
                case LV_KEY_SAVE: {
                    if(itemCount > 0) {
                        Group_Save(&CurGroup, __GetFocusFileName());
                        printf("Save File:|%s|\r\n", __GetFocusFileName());
                        refreshFlag = 1;
                        IF_MsgBox_Tips_Mult(&mStr_Save_Tips);
                    }
                }
                break;
                case LV_KEY_LOAD: {
                    if(itemCount > 0) {
                        memset(&CurGroup, 0, sizeof(Group_Def));
                        Group_Load(&CurGroup, __GetFocusFileName());
                        printf("Load File:|%s|\r\n", __GetFocusFileName());
                        refreshFlag = 1;
                        IF_MsgBox_Tips_Mult(&mStr_Load_Tips);
                        //加载输出配置
                        extern void __Load_OutPut_Setting(void);
                        __Load_OutPut_Setting();
                    }
                }
                break;
                case LV_KEY_SAVEAS: {
                    memset(fileName, 0, sizeof(fileName));
                    InputVal_StringEdit_SetCall(&mStr_InputFileName_Title, fileName, MAX_SAVE_FILENAME_LEN - 1);
                    refreshFlag = 1;
                }
                break;
                case LV_KEY_RENAME: {
                    memset(fileName, 0, sizeof(fileName));
                    InputVal_StringEdit_SetCall(&mStr_InputFileName_Title, fileName, MAX_SAVE_FILENAME_LEN - 1);
                    refreshFlag = 1;
                }
                break;
                case LV_KEY_DELETE: {
                    Group_Delete(__GetFocusFileName());
                    refreshFlag = 1;
                    IF_MsgBox_Tips_Mult(&mStr_Delete_Tips);
                }
                break;
                case LV_KEY_UP: {
                    if(edit_row_y > MIN_ROW) {
                        if((disp_baseIndex + edit_row_y - MIN_ROW) > 0)
                        {
                            edit_row_y--;
                        }
                    } else {
                        //不能向上移动/向上显示
                        if(disp_baseIndex > 0)
                        {
                            disp_baseIndex -= MAX_ROW;
                            edit_row_y = MAX_ROW;
                            __Table_Refresh(disp_baseIndex);
                        }
                    }
                    __Table_setFocus(&edit_row_y);
                }
                break;
                case LV_KEY_DOWN: {
                    if(edit_row_y < MAX_ROW) {
                        if((disp_baseIndex + edit_row_y - MIN_ROW) < (itemCount - 1))
                        {
                            edit_row_y++;
                        }
                    } else {
                        //不能向下移动/向下显示
                        if(disp_baseIndex <= ((itemCount - 1) - (TABLE_ROW_CNT - 1)))
                        {
                            disp_baseIndex += MAX_ROW;
                            edit_row_y = MIN_ROW;
                            __Table_Refresh(disp_baseIndex);
                        }
                    }
                    __Table_setFocus(&edit_row_y);
                }
                break;
            }
        }
        break;
        case LV_EVENT_CLICKED:
        case LV_EVENT_REFRESH:
            if(lv_obj_is_visible(obj) != 0)
            {
                refreshFlag = 1;
            }
            break;
    }
    if(refreshFlag == 1) {
        LinkList_DeleteAll(GroupFile_listHead);
        FATFS_FindFile_Recursive("FLASH", GROUP_FILE_FLASH_PATH, "*.user");
        FATFS_FindFile_Recursive("USB", GROUP_FILE_USB_PATH, "*.user");
        itemCount = LinkList_Count(GroupFile_listHead);
        if(edit_row_y > (itemCount - disp_baseIndex)) {
            edit_row_y = MIN_ROW;
            disp_baseIndex = 0;
        }
        __Table_Refresh(disp_baseIndex);
        __Table_setFocus(&edit_row_y);
    }
}





static void Group_Delete(const char *name)
{
    f_unlink(name);
}

static uint8_t Group_Rename(const char *oldname, const char *newname)
{
    FIL readFile;
    FIL writeFile;
    //打开文件
    if(f_open(&readFile, oldname, FA_READ) != FR_OK) {
        return 0;
    }
    if(f_open(&writeFile, newname, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
        return 0;
    }
    for(uint32_t count = 0; count < f_size(&readFile);)
    {
        uint8_t buf[256] = {0};
        UINT bytesread = 0;
        UINT byteswrite = 0;
        if((FR_OK != f_read(&readFile, buf, sizeof(buf), &bytesread)) && (bytesread == 0)) {
            break;
        }
        if((FR_OK != f_write(&writeFile, buf, bytesread, &byteswrite)) && (byteswrite == 0)) {
            break;
        }
        if(bytesread != byteswrite) {
            break;
        } else {
            count += byteswrite;
        }
    }
    f_close(&readFile);
    f_close(&writeFile);
    return 1;
}


void Group_Create(const char *name)
{
    FIL myFile;
    //打开文件
    if(f_open(&myFile, name, FA_CREATE_NEW | FA_WRITE) != FR_OK) {
        return ;
    }
    Group_Def group_null = {0};
    md5((uint8_t *)&group_null, sizeof(Group_Def) - sizeof(group_null.md5Value), group_null.md5Value);
    UINT byteWrite = 0;
    f_write(&myFile, &group_null, sizeof(Group_Def), &byteWrite);
    f_close(&myFile);
}



uint8_t Group_Save(Group_Def *pGroup, const char *name)
{
    if(pGroup == NULL) {
        return 0;
    }
    FIL myFile;
    //打开文件
    if(f_open(&myFile, name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
        return 0;
    }
    Group_Def group_null = {0};
    if(pGroup == NULL) {
        pGroup = &group_null;
    }
    Group_Def tempGounp = {0};
    memcpy(&tempGounp, pGroup, sizeof(tempGounp));
    //保存时默认关闭输出
    tempGounp.outset.out = 0;
    tempGounp.outset.lock = 0;
    md5((uint8_t *)&tempGounp, sizeof(Group_Def) - sizeof(tempGounp.md5Value), tempGounp.md5Value);
    UINT byteWrite = 0;
    f_write(&myFile, &tempGounp, sizeof(Group_Def), &byteWrite);
    f_close(&myFile);
    return 1;
}

void Group_Load(Group_Def *pGroup, const char *name)
{
    if(pGroup == NULL) {
        return ;
    }
    FIL myFile;
    if(f_open(&myFile, name, FA_READ) != FR_OK) {
        //若无该文件,则新建
        Group_Save(NULL, name);
        if(f_open(&myFile, name, FA_READ) != FR_OK) {
            return ;
        }
    }
    Group_Def tempInfo = {0};
    UINT byteRead = 0;
    FRESULT fres = FR_OK;
    fres = f_read(&myFile, &tempInfo, sizeof(Group_Def), &byteRead);
    if(fres != FR_OK) {
        goto closeFile;
    }
    //计算MD5
    uint8_t md5Value[16];
    md5((uint8_t *)&tempInfo, sizeof(Group_Def) - sizeof(tempInfo.md5Value), md5Value);
    //比较MD5并拷贝
    if(memcmp(md5Value, tempInfo.md5Value, sizeof(tempInfo.md5Value)) == 0) {
        memcpy(pGroup, &tempInfo, sizeof(Group_Def));
    }
closeFile:
    //关闭文件
    f_close(&myFile);
    lv_event_send_refresh_recursive(ui.HomePage_cont_Set);
}

/*
 * @brief       void GroupPage_Enter(void)
 * @details     进入Group页面
 */
void GroupPage_Enter(void)
{
    lv_obj_set_hidden(ui.GroupPage_cont, 0);
    disp_baseIndex = 0;
    lv_event_send_refresh_recursive(ui.GroupPage_cont);
    lv_label_set_text_static(table_label[0][0], "No");
    lv_label_set_text_static(table_label[0][1], "Device");
    lv_label_set_text_static(table_label[0][2], "FileName");
    __Table_setFocus(&edit_row_y);
}

/*
 * @brief       void GroupPage_Exit(void)
 * @details     退出Group页面
 */
void GroupPage_Exit(void)
{
    LinkList_DeleteAll(GroupFile_listHead);
    lv_obj_set_hidden(ui.GroupPage_cont, 1);
}


void GroupPage_GroupCreate(void)
{
    Group_Create(GROUP_FILE_FLASH_PATH"/group1.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group2.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group3.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group4.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group5.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group6.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group7.user");
    Group_Create(GROUP_FILE_FLASH_PATH"/group8.user");
    //
    {
        setup_scr_GroupPage(&ui);
        lv_obj_set_parent(ui.GroupPage_cont, ui.Back_cont_back);
    }
    __Table_Init();
    //
    GroupFile_listHead = LinkList_Create("", "", "");
    GroupPage_Enter();
    GroupPage_Exit();
}


