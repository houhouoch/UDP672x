#include "Tree.h"
#include <stdint.h>

//用于调试查看申请的树节点内存数量
uint16_t Tree_NodeCount = 0;


/*!
 * @brief   Tree_Def *Tree_CreateNode(const void* pdata)
 *          创建树节点
 * @param   string:字符串,树的回调函数
 * @retval  Tree_Def* 对象指针
 */
Tree_Def *Tree_CreateNode(const void *pdata)
{
    Tree_Def *tree = Tree_malloc(sizeof(Tree_Def));
    if(tree != NULL)
    {
        Tree_NodeCount++;
        memset(tree, 0, sizeof(Tree_Def));
        tree->pdata = pdata;
    }
    return tree;
}

/*!
 * @brief   void Tree_Delete(Tree_Def* parent,Tree_Def* tree)
 *          释放树内存
 * @param   parent:父类 tree:需要释放的树指针
 */
void Tree_Delete(Tree_Def *parent, Tree_Def *tree)
{
    if(parent == NULL) {
        return;
    }
    //递归删除
    if(tree == NULL) {
        return;
    }
    if(tree->parent != parent) {
        return;
    }
    if(parent->child == tree) {
        parent->child = NULL;
    } else {
        Tree_Def *preNode = tree->prev;
        preNode->next = NULL;
    }
    if(tree->child != NULL) {
        Tree_Delete(tree, tree->child);
        tree->child = NULL;
    }
    if(tree->next != NULL) {
        Tree_Delete(parent, tree->next);
        tree->next = NULL;
    }
    //释放自身内存
    //        Tree_free(tree->pdata);
    Tree_free(tree);
    Tree_NodeCount--;
}

/*!
 * @brief   void Tree_Append(Tree_Def* parent,Tree_Def* tree)
 *          新增节点
 * @param   parent父类,tree:节点
 */
void Tree_Append(Tree_Def *parent, Tree_Def *tree)
{
    if((parent != NULL) && (tree != NULL))
    {
        if(parent->child == NULL)
        {
            parent->child = tree;
            tree->parent = parent;
        }
        else {
            //追加节点
            uint16_t tree_count = 0;
            Tree_Def *temp_node = parent->child;
            while(temp_node->next != NULL)
            {
                temp_node = temp_node->next;
                ++tree_count;
            }
            temp_node->next = tree;
            tree->prev = temp_node;
            tree->next = NULL;
            tree->parent = parent;
        }
    }
}

/*!
 * @brief   Tree_Def *Tree_AddNode(Tree_Def *parent, const void* pdata);
 *          添加新节点
 * @param   parent:父类,pdata 数据
 */
Tree_Def *Tree_AddNode(Tree_Def *parent, const void *pdata)
{
    Tree_Def *newNode = Tree_CreateNode(pdata);
    if((parent != NULL) && (newNode != NULL))
    {
        Tree_Append(parent, newNode);
    }
    return newNode;
}



/*!
 * @brief   int16_t Tree_GetChildCount(Tree_Def* treeNode)
 *          获取树节点的子类数量
 * @param   treeNode:树节点
 * @retval  节点数
 */
uint16_t Tree_GetChildCount(Tree_Def *treeNode)
{
    if(treeNode->child != NULL)
    {
        uint16_t childCount = 1;
        Tree_Def *temp_node = treeNode->child;
        while(temp_node->next != NULL)
        {
            temp_node = temp_node->next;
            ++childCount;
        }
        return childCount;
    } else {
        return 0;
    }
}

/*
 * @brief       Tree_Def* Tree_GetItem_At(Tree_Def *treeNode,uint16_t i)
 * @details     获取特定索引节点
 */
Tree_Def *Tree_GetItem_At(Tree_Def *treeNode, uint16_t i)
{
    if(treeNode == NULL)
    {
        return NULL;
    }
    if(treeNode->child == NULL)
    {
        return NULL;
    }
    Tree_Def *node = NULL;
    uint16_t index = 0;
    Tree_Def *temp_node = treeNode->child;
    while(temp_node != NULL)
    {
        if(index == i) {
            node = temp_node;
            break;
        }
        temp_node = temp_node->next;
        ++index;
    }
    return node;
}


/*
 * @brief       uint8_t Tree_IsChild(Tree_Def *parent,Tree_Def* tree)
 * @details     是否为子节点
 */
uint8_t Tree_IsChild(Tree_Def *parent, Tree_Def *tree)
{
    if(parent == NULL) {
        return 0;
    }
    if(parent->child == NULL) {
        return 0;
    }
    if(tree == NULL) {
        return 0;
    }
    Tree_Def *temp_node = parent->child;
    while(temp_node != NULL)
    {
        if(tree == temp_node) {
            return 1;
        }
        if(temp_node->child != NULL) {
            if(0 != Tree_IsChild(temp_node->child, tree)) {
                return 1;
            }
        }
        temp_node = temp_node->next;
    }
    return 0;
}


