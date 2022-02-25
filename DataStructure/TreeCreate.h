#pragma once
#ifndef __CREATE_H__
#define __CREATE_H__
#include "Tree.h"

int BST_Insert(BiTree& T, int v);
BiTree Create_BST(int a[], int n);
void Create_InThread(BiTree T);
void Create_PreThread(BiTree T);
void InThread(BiTree& p, BiTree& pre);
void PreThread(BiTree& p, BiTree& pre);
int getIndex(int a[], int x, int n);
BiTree create_Tree(int a[], int b[], int l1, int l2, int r1, int r2, int n);
int getIndex(int a[], int x, int n);

/**
 * @brief 二叉排序树插入
 *
 * @param T
 * @param v
 * @return int
 */
int BST_Insert(BiTree& T, int v)
{
    if (v == T->data)
    {
        cout << "already in tree" << endl;
        return 0;
        /* code */
    }
    else if (v < T->data)
    {
        if (T->lchild == NULL)
        {
            BiTree new_T = (BiTNode*)malloc(sizeof(BiTNode));
            new_T->data = v;
            new_T->ltag = 0;
            new_T->rtag = 0;
            new_T->lchild = NULL;
            new_T->rchild = NULL;
            T->lchild = new_T;
            return 1;
        }
        else
            return BST_Insert(T->lchild, v);
        /* code */
    }
    else
    {
        if (T->rchild == NULL)
        {
            BiTree new_T = (BiTNode*)malloc(sizeof(BiTNode));
            new_T->data = v;
            new_T->ltag = 0;
            new_T->rtag = 0;
            new_T->lchild = NULL;
            new_T->rchild = NULL;
            T->rchild = new_T;
            return 1;
        }
        else
            return BST_Insert(T->rchild, v);
    }
}

/**
 * @brief 二叉排序树建立
 *
 * @param T
 */
BiTree Create_BST(int a[], int n)
{
    BiTree T = (BiTNode*)malloc(sizeof(BiTNode));
    T->lchild = NULL;
    T->rchild = NULL;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            T->data = a[i];
            continue;
            /* code */
        }
        BST_Insert(T, a[i]);
    }
    return T;
}
/**
 * @brief 中序遍历建立线索二叉树
 *
 * @param T
 */
void Create_InThread(BiTree T)
{
    BiTree pre = NULL;
    if (T != NULL)
    {
        InThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}
/**
 * @brief 先序遍历建立线索二叉树
 *
 * @param T
 */
void Create_PreThread(BiTree T)
{
    BiTree pre = NULL;
    if (T != NULL)
    {
        PreThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}
/**
 * @brief 中序遍历对二叉树线索化
 *
 * @param p
 * @param pre
 */
void InThread(BiTree& p, BiTree& pre)
{
    if (p != NULL)
    {
        p->ltag = p->lchild == NULL ? 1 : 0;
        p->rtag = p->rchild == NULL ? 1 : 0;
        InThread(p->lchild, pre);
        if (p->lchild == NULL)
        {
            p->lchild = pre;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p;
            /* code */
        }
        pre = p;
        InThread(p->rchild, pre);
    }
}
/**
 * @brief 先序遍历对二叉树线索化
 *
 * @param p
 * @param pre
 */
void PreThread(BiTree& p, BiTree& pre)
{
    if (p != NULL)
    {
        if (p->lchild == NULL)
        {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = p;
            pre->rtag = 1;
            /* code */
        }
        pre = p;
        if (p->ltag != 1)
            PreThread(p->lchild, pre);
        if (p->rtag != 1)
            PreThread(p->rchild, pre);
    }
}
/**
 * @brief 根据先序遍历与中序遍历构造二叉树
 *
 * @param a 先序数组
 * @param b 中序数组
 * @param l1 先序遍历数组起始位置
 * @param l2 中序遍历数组起始位置
 * @param r1 先序遍历数组结束位置
 * @param r2 中序遍历数组结束位置
 * @param n 数组长度
 * @return BiTree
 *
 * @par paragraph title
 *
 *
 * @remarks  {int b[] = {3, 5, 6, 9, 12, 19, 34, 54};}
 * @remarks int c[] = {19, 5, 3, 6, 9, 12, 34, 54};
 */
BiTree create_Tree(int a[], int b[], int l1, int r1, int l2, int r2, int n)
{
    int index = 0;
    for (index = 0; a[l1] != b[index]; index++)
        ;
    int llen = index - l2;
    int rlen = r2 - index;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = a[l1];
    root->lchild = NULL;
    root->rchild = NULL;
    if (llen)
        root->lchild = create_Tree(a, b, l1 + 1, l1 + llen, l2, l2 + llen - 1, n);
    if (rlen)
        root->rchild = create_Tree(a, b, r1 - rlen + 1, r1, r2 - rlen + 1, r2, n);
    return root;
}
/**
 * @brief 根据题目要求构建二叉树
 */
BiTree create_Char_Tree()
{

    char v;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    BiTree p = root;
    printf("The root val:");
    scanf("%c", &v);
    p->Cdata = v;
    p->lchild = NULL;
    p->rchild = NULL;
    stack<BiTree> stk;
    stk.push(p);
    while (!stk.empty())
    {
        char vl, vr;
        p = stk.top();
        stk.pop();
        printf("this node is %c \n", p->Cdata);
        printf("Build left tree:");
        cin >> vl;
        if (vl != '#')
        {
            BiTree tmp = (BiTree)malloc(sizeof(BiTNode));
            tmp->Cdata = vl;
            tmp->lchild = NULL;
            tmp->rchild = NULL;
            p->lchild = tmp;
            stk.push(tmp);
        }
        printf("Build right tree:");
        cin >> vr;
        if (vr != '#')
        {
            BiTree tmp = (BiTree)malloc(sizeof(BiTNode));
            tmp->Cdata = vr;
            tmp->lchild = NULL;
            tmp->rchild = NULL;
            p->rchild = tmp;
            stk.push(tmp);
        }
    }
    return root;
}
/**
 * @brief Create a CSTree Degree object
 *
 * @param a
 * @param b
 * @param n
 * @return BiTree
 */
BiTree create_CSTree_Degree(int a[], int b[], int n)
{
    int last = 0;
    BiTree* pointer = new BiTree[n];
    for (int i = 0; i < n; i++)
    {
        pointer[i]->data = a[i];
        pointer[i]->lchild = pointer[i]->rchild = NULL;
    }
    for (int i = 0; i < n;)
    {
        if (b[i])
        {
            last++;
            pointer[i]->lchild = pointer[last];
            for (int j = 0; j < b[i] - 1; j++)
            {
                pointer[last]->rchild = pointer[last + 1];
                last++;
            }
        }
    }
    return pointer[0];
}
#endif