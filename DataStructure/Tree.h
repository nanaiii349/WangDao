#pragma once
#ifndef __TREE_H__
#define __TREE_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;
/**
 * @brief 二叉树的数据结构支持索引化
 *
 */
typedef struct BitNode
{
    int data;
    char Cdata;
    int val;
    /**
     * @brief ltag  1表示无子树，索引到前继
     */
    int ltag;
    /**
     * @brief rtag  1表示无子树，索引到后继
     */
    int rtag;
    struct BitNode* lchild, * rchild;
} BiTNode, * BiTree;

void visit(BiTree T);
int Btdepth(BiTree T);
void SearchDeletX(BiTree T, int x);
bool isCompleteBinaryTree(BiTree T);
void DeleteXTree(BiTree T);
void SwapChild(BiTree T);
vector<int> SearchXFather(BiTree T, int x);
int SearchXYFather(BiTree T, int x, int y);

/**
 * @brief 访问结点元素
 *
 * @param T
 */
void visit(BiTree T)
{
    cout << "data:" << T->data << endl;
}
/**
 * @brief 非遍历求二叉树高度
 *
 * @param T
 * @return int
 */
int Btdepth(BiTree T)
{
    if (!T)
        return 0;
    queue<BiTree> q;
    q.push(T);
    BiTree p = T;
    BiTree last = T;
    int level = 0;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        if (p->lchild)
            q.push(p->lchild);
        if (p->rchild)
            q.push(p->rchild);
        if (last == p)
        {
            last = q.back();
            level++;
        }
    }
    return level;
}
/**
 * @brief 判别二叉树是否为完全二叉树
 *
 * @param T
 * @return true
 * @return false
 */
bool isCompleteBinaryTree(BiTree T)
{
    if (!T)
        return true;
    queue<BiTree> q;
    q.push(T);
    int flag = 0;
    while (!q.empty())
    {
        BiTree t = q.front();
        q.pop();
        if (t->lchild)
        {
            if (flag == 1)
                return false;
            q.push(t->lchild);
        }
        else
            flag = 1;
        if (t->rchild)
        {
            if (flag == 1)
                return false;
            q.push(t->rchild);
        }
        else
            flag = 1;
    }
    return true;
}
/**
 * @brief 计算二叉树中所有双分支结点个数
 *
 * @param T
 * @return int
 */
int DsonNodes(BiTree T)
{
    if (!T)
        return 0;
    if (T->lchild && T->rchild)
        return DsonNodes(T->lchild) + DsonNodes(T->rchild) + 1;
    else
        return DsonNodes(T->lchild) + DsonNodes(T->rchild);
}
/**
 * @brief 交换左右子树
 *
 * @param T
 */
void SwapChild(BiTree T)
{
    if (T)
    {
        BiTree tmp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = tmp;
        SwapChild(T->lchild);
        SwapChild(T->rchild);
    }
}
/**
 * @brief 删除以T为根的树
 *
 * @param T
 */
void DeleteXTree(BiTree T)
{
    if (T)
    {
        DeleteXTree(T->lchild);
        DeleteXTree(T->rchild);
        free(T);
    }
}
/**
 * @brief 删除所有以x为值的结点及其子树
 *
 * @param T
 * @param x
 */
void SearchDeletX(BiTree T, int x)
{
    queue<BiTree> q;
    if (!T)
        return;
    if (T->data == x)
    {
        DeleteXTree(T);
        return;
    }
    q.push(T);
    while (!q.empty())
    {
        BiTree p = q.front();
        if (p->lchild)
        {
            if (p->lchild->data == x)
            {
                DeleteXTree(p->lchild);
                p->lchild = NULL;
            }
            else
                q.push(p->lchild);
        }
        if (p->rchild)
        {
            if (p->rchild->data == x)
            {
                DeleteXTree(p->rchild);
                p->rchild = NULL;
            }
            else
                q.push(p->rchild);
        }
        q.pop();
    }
}
/**
 * @brief 寻找以x为值的结点的所有祖先
 *
 * @param T
 * @param x
 *
 * @return vector<int>
 */
vector<int> SearchXFather(BiTree T, int x)
{
    vector<int> res;
    if (!T)
        return res;
    stack<BiTree> stk;
    stack<int> tag;
    BiTree p = T;
    while (p || !stk.empty())
    {
        while (p && p->data != x) //先沿左子树访问
        {
            stk.push(p);
            tag.push(0);
            p = p->lchild;
        }
        if (p && p->data == x)
        {
            int n = stk.size();
            for (int i = 0; i < n; i++)
            {
                cout << "data:" << stk.top()->data << endl;
                res.push_back(stk.top()->data);
                stk.pop();
            }
            return res;
        }
        while (!stk.empty() && tag.top() == 1)
        {
            stk.pop();
            tag.pop();
        }
        if (!stk.empty())
        {
            tag.top() = 1;
            p = stk.top()->rchild;
        }
    }
    return res;
}
/**
 * @brief   寻找x，y最近对共同祖先
 *
 * @param T
 * @param x
 * @param y
 * @return int
 */
int SearchXYFather(BiTree T, int x, int y)
{
    vector<int> fatherX = SearchXFather(T, x);
    vector<int> fatherY = SearchXFather(T, y);
    for (int i = 0; i < int(fatherX.size()); i++)
    {
        for (int j = 0; j < int(fatherY.size()); j++)
            if (fatherX[i] == fatherY[j])
                return fatherX[i];
    }
    return -1;
}
/**
 * @brief 求二叉树的宽度
 *
 * @param T
 * @return int
 */
int BtWidth(BiTree T)
{
    if (!T)
        return -1;
    queue<BiTree> q;
    q.push(T);
    BiTree p = T;
    BiTree last = T;
    int width = 0;
    int maxWidth = 0;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        width++;
        if (p->lchild)
            q.push(p->lchild);
        if (p->rchild)
            q.push(p->rchild);
        if (p == last)
        {
            maxWidth = maxWidth < width ? width : maxWidth;
            width = 0;
            last = q.back();
        }
    }
    return maxWidth;
}
/**
 * @brief 构建叶子结点间的连接
 *
 * @param T
 * @return BiTree
 */
BiTree LinkLeaf(BiTree T)
{
    stack<BiTree> stk;
    BiTree p = T;
    BiTree Head = NULL;
    BiTree pre = NULL;
    while (p || !stk.empty())
    {
        if (p)
        {
            stk.push(p);
            if (!p->lchild && !p->rchild)
            {
                if (Head == NULL)
                {
                    Head = p;
                }
                else
                {
                    pre->rchild = p;
                }
                pre = p;
            }
            p = p->lchild;
        }
        else
        {
            BiTree tmp = stk.top();
            stk.pop();
            visit(tmp);
            p = tmp->rchild;
        }
    }
    return Head;
}
/**
 * @brief 判断两棵树是否相似
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool similar(BiTree a, BiTree b)
{
    if (a == NULL && b == NULL)
        return true;
    else if (a == NULL || b == NULL)
        return false;
    else
    {
        bool leftS = similar(a->lchild, b->lchild);
        bool rightS = similar(a->rchild, b->rchild);
        return leftS && rightS;
    }
}
/**
 * @brief 在二叉树中寻找以x为值的结点
 *
 * @param T
 * @param x
 * @return BiTree
 */
BiTree SearchX(BiTree T, int x)
{
    if (T)
    {
        BiTree p1 = NULL, p2 = NULL;
        if (T->data == x)
            return T;
        if (T->ltag == 0)
            p1 = SearchX(T->lchild, x);
        if (T->rtag == 0)
            p2 = SearchX(T->rchild, x);
        if (p1)
            return p1;
        else
            return p2;
    }
    return NULL;
}
/**
 * @brief Get the Pre Node By Post object
 *
 * @param T
 * @param x
 * @return BiTree
 */
BiTree getPreNodeByPost(BiTree T, int x)
{
    BiTree p = SearchX(T, x);
    if (p->rtag == 0)
        return p->rchild;
    if (p->ltag == 0)
        return p->lchild;
    if (p->lchild == NULL)
        return NULL;
    p = p->lchild;
    while (p->ltag == 1 || !p)
        p = p->lchild;
    return p->lchild;
}
/**
 * @brief 根据满二叉树的先序数组得到后序数组
 *
 * @param a
 * @param b
 * @param al
 * @param ar
 * @param bl
 * @param br
 * @param n
 */
void getPostByPre(int a[], int b[], int al, int ar, int bl, int br, int n)
{
    if (n == 1)
    {
        b[bl] = a[al];
    }
    else
    {
        b[br] = a[al];
        n = (n - 1) / 2;
        getPostByPre(a, b, al + 1, al + n, bl, bl + n - 1, n);
        getPostByPre(a, b, al + n + 1, ar, bl + n, br - 1, n);
    }
}
/**
 * @brief  计算二叉树带权路径长度(WPL)
 *
 * @param T
 * @param depth
 * @return int
 */
int getWPL(BiTree T, int depth)
{
    int sum = 0;
    if (!T)
        return 0;
    if (!T->lchild && !T->rchild)
        return T->data * depth;
    if (T->lchild)
        sum += getWPL(T->lchild, depth + 1);
    if (T->rchild)
        sum += getWPL(T->rchild, depth + 1);
    return sum;
}

/**
 * @brief 由二叉树转换为等价的中缀表达式
 *
 * @param T
 * @param depth
 */
void BtreeToExp(BiTree T, int depth)
{
    if (T == NULL)
        return;
    else if (!T->lchild && !T->rchild)
        cout << T->Cdata;
    else
    {
        if (depth > 1)
            cout << '(';
        BtreeToExp(T->lchild, depth + 1);
        cout << T->Cdata;
        BtreeToExp(T->rchild, depth + 1);
        if (depth > 1)
            cout << ')';
    }
}
/**
 * @brief 计算孩子兄弟树的深度
 *
 * @param T
 * @param depth
 * @return int
 */
int getCSTreeDepth(BiTree T, int depth)
{
    if (!T)
        return depth;
    int dl = depth, dr = depth;
    if (T->lchild)
        dl = getCSTreeDepth(T->lchild, depth + 1);
    if (T->rchild)
        dr = getCSTreeDepth(T->rchild, depth);
    return dl > dr ? dl : dr;
}
/**
 * @brief 计算以孩子兄弟法存储的森林的叶子结点数
 *
 * @param T
 * @return int
 */
int getLeaf(BiTree T)
{
    if (!T)
        return 0;
    if (T->lchild)
        return getLeaf(T->lchild) + getLeaf(T->rchild);
    else
        return 1 + getLeaf(T->rchild);
}

bool isBSTree(BiTree T, int pre)
{

    if (!T)
        return true;
    bool isLeft = isBSTree(T->lchild, pre);
    if (pre > T->data)
        return false;
    bool isRight = isBSTree(T->rchild, T->data);
    return isLeft && isRight;
}

int getMinData(BiTree T)
{
    while (T->lchild)
    {
        T = T->lchild;
    }
    return T->data;
}
int getMaxData(BiTree T)
{
    while (T->rchild)
        T = T->rchild;
    return T->data;
}

bool isAVLTree(BiTree T, int& h)
{
    int hl = 0, hr = 0;
    if (!T)
    {
        h = 0;
        return true;
    }
    else if (!T->lchild && !T->rchild)
    {
        h = 1;
        return true;
    }
    else
    {
        bool bl = isAVLTree(T->lchild, hl);
        bool br = isAVLTree(T->rchild, hr);
        h = (hl > hr ? hl : hr) + 1;
        if (abs(hl - hr) < 2)
            return bl && br;
        else
            return false;
    }
}

void OutputGeK(BiTree T, int x)
{
    if (!T)
        return;
    if (T->data > x)
    {
        OutputGeK(T->rchild, x);
        cout << T->data << ",";
        OutputGeK(T->lchild, x);
    }
    else
    {
        OutputGeK(T->rchild, x);
    }
}

int getXLevel(BiTree T, int x, int level)
{
    if (!T)
        return -1;
    if (T->data > x)
        return getXLevel(T->lchild, x, level + 1);
    else if (T->data == x)
        return level;
    else
        return getXLevel(T->rchild, x, level + 1);
}
#endif