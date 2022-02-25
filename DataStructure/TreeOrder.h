#pragma once
#ifndef __ORDER_H__
#define __ORDER_U__
#include "Tree.h"

void preOrder(BiTree T);
void inOrder(BiTree T);
void postOrder(BiTree T);
void levelOrder(BiTree T);
void inOrder2(BiTree T);
void preOrder2(BiTree T);
void postOrder2(BiTree T);
void levelOrder2(BiTree T);
BiTree Firstnode(BiTree T);
BiTree Nextnode(BiTree T);
void inOrderInThread(BiTree T);
void preOrderPreThread(BiTree T);
/**
 * @brief 先序遍历
 *
 * @param T
 */
void preOrder(BiTree T)
{
    if (T == NULL)
        return;
    visit(T);
    if (T->ltag != 1)
        preOrder(T->lchild);
    if (T->rtag != 1)
        preOrder(T->rchild);
}

/**
 * @brief 非递归的先序遍历
 *
 * @param T
 */
void preOrder2(BiTree T)
{
    stack<BiTree> stk;
    BiTree p = T;
    while (p || !stk.empty())
    {
        if (p)
        {
            visit(p);
            stk.push(p);
            p = p->lchild;
        }
        else
        {
            //BiTree tmp=stk.top();
            p = stk.top()->rchild;
            stk.pop();
        }

        /* code */
    }
}
/**
 * @brief 非递归的中序遍历
 *
 * @param T
 */
void inOrder2(BiTree T)
{
    stack<BiTree> stk;
    BiTree p = T;
    while (p || !stk.empty())
    {
        if (p)
        {
            stk.push(p);
            p = p->lchild;
        }
        else
        {
            BiTree tmp = stk.top();
            stk.pop();
            visit(tmp);
            p = tmp->rchild;
        }
        /* code */
    }
}
/**
 * @brief 中序遍历
 *
 * @param T
 */
void inOrder(BiTree T)
{
    if (T == NULL)
        return;
    inOrder(T->lchild);
    visit(T);
    inOrder(T->rchild);
}
/**
 * @brief 后序遍历
 *
 * @param T
 */
void postOrder(BiTree T)
{
    if (T == NULL)
        return;
    postOrder(T->lchild);
    postOrder(T->rchild);
    visit(T);
}
/**
 * @brief 非递归的后序遍历
 *
 * @param T
 */
void postOrder2(BiTree T)
{
    stack<BiTree> stk;
    BiTree p = T;
    BiTree pre = NULL;
    while (p || !stk.empty())
    {
        if (p)
        {
            stk.push(p);
            p = p->lchild;
        }
        else
        {
            BiTree tmp = stk.top();
            if (tmp->rchild && tmp->rchild != pre)
            {
                p = tmp->rchild;
            }
            else
            {
                visit(tmp);
                stk.pop();
                pre = tmp;
                tmp = NULL; //访问完一个结点相当于遍历完以该节点为根的子树
            }
        }
    }
}
/**
 * @brief   层次遍历(自下而上，自右至左)
 *
 * @param T
 */
void levelOrder(BiTree T)
{
    queue<BiTree> q;
    stack<BiTree> stk;
    q.push(T);
    while (!q.empty())
    {
        BiTree t = q.front();
        q.pop();
        stk.push(t);
        if (t->lchild)
            q.push(t->lchild);
        if (t->rchild)
            q.push(t->rchild);
    }
    while (!stk.empty())
    {
        BiTree p = stk.top();
        visit(p);
        stk.pop();
    }
}
/**
 * @brief   层次遍历
 *
 * @param T
 */
void levelOrder2(BiTree T)
{
    queue<BiTree> q;
    q.push(T);
    while (!q.empty())
    {
        BiTree t = q.front();
        q.pop();
        visit(t);
        if (t->lchild)
            q.push(t->lchild);
        if (t->rchild)
            q.push(t->rchild);
    }
}

BiTree Firstnode(BiTree T)
{
    while (T->ltag != 1)
        T = T->lchild;
    return T;
}
BiTree Nextnode(BiTree T)
{
    if (T->rtag != 1)
        return Firstnode(T->rchild);
    return T->rchild;
}
/**
 * @brief 遍历中序线索树
 *
 * @param T
 */
void inOrderInThread(BiTree T)
{
    for (BiTree i = Firstnode(T); i != NULL; i = Nextnode(i))
        visit(i);
}
/**
 * @brief 遍历先序线索树
 *
 * @param T
 */
void preOrderPreThread(BiTree T)
{
    while (T)
    {
        visit(T);
        if (T->ltag != 1)
            T = T->lchild;
        else
            T = T->rchild;
    }
}
#endif