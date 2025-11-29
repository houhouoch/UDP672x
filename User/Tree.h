#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "freertos.h"

#ifndef true
    #define true 1
#endif // true

#ifndef false
    #define false 0
#endif // false

#ifndef bool
    #define bool uint8_t
#endif // bool

#ifndef NULL
    #define NULL (void*)0
#endif // NULL

#define PRINTF Debug

#define Tree_malloc(x)  pvPortMalloc(x)
#define Tree_free(x)    vPortFree(x)
#define Tree_Printf     printf



//使用动态内存作为字符串的存储位置
//#define TREE_MALLOC_STRING
#include "VirtualBtnm.h"
typedef struct Tree_Def
{
    struct Tree_Def *next;  //前一个
    struct Tree_Def *prev;  //下一个
    struct Tree_Def *child; //子类
    struct Tree_Def *parent;//父类

    //    const void* pdata;

    const struct BtnInfo_Def *pdata;
} Tree_Def;


/*!
 * @brief   Tree_Def *Tree_CreateNode(const void* pdata)
 *          创建树节点
 * @param   string:字符串,树的回调函数
 * @retval  Tree_Def* 对象指针
 */
Tree_Def *Tree_CreateNode(const void *pdata);

/*!
 * @brief   void Tree_Delete(Tree_Def* parent,Tree_Def* tree)
 *          释放树内存
 * @param   parent:父类 tree:需要释放的树指针
 */
void Tree_Delete(Tree_Def *parent, Tree_Def *tree);

/*!
 * @brief   void Tree_Append(Tree_Def* parent,Tree_Def* tree)
 *          新增节点
 * @param   parent父类,tree:节点
 */
void Tree_Append(Tree_Def *parent, Tree_Def *tree);

/*!
 * @brief   Tree_Def *Tree_AddNode(Tree_Def *parent, const void* pdata);
 *          添加新节点
 * @param   parent:父类,pdata 数据
 */
Tree_Def *Tree_AddNode(Tree_Def *parent, const void *pdata);



/*!
 * @brief   int16_t Tree_GetChildCount(Tree_Def* treeNode)
 *          获取树节点的子类数量
 * @param   treeNode:树节点
 * @retval  节点数
 */
uint16_t Tree_GetChildCount(Tree_Def *treeNode);


/*
 * @brief       Tree_Def* Tree_GetItem_At(Tree_Def *treeNode,uint16_t i)
 * @details     获取特定索引节点
 */
Tree_Def *Tree_GetItem_At(Tree_Def *treeNode, uint16_t i);


/*
 * @brief       uint8_t Tree_IsChild(Tree_Def *parent,Tree_Def* tree)
 * @details     是否为子节点
 */
uint8_t Tree_IsChild(Tree_Def *parent, Tree_Def *tree);





/*!
 * @brief   void Tree_Print(Tree_Def* tree,uint16_t deepth)
 *          打印树
 * @param   tree:树;deepth:显示深度
 */
void Tree_Print(Tree_Def *tree, uint16_t deepth);

#endif // _TREE_H_
