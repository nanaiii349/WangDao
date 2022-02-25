#pragma once
#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include <set>
#include <string>
using namespace std;

const int MAXSIZE = 50;

typedef struct STACK {
	int data[MAXSIZE];
	int size;
	int top;
	int top1,top2;//Ë«ÏòÕ»Ê¹ÓÃ
}Stack;

typedef struct QUEUE {
	int data[MAXSIZE];
	int front, rear;
	int tag;
}SqQUeue;

bool Judge(int a[], int n)
{
	int size = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 1)
			size++;
		if (a[i] == 0)
			if (--size < 0)
				return false;
	}
	return size==0;
}

bool isSys(int a[], int n)
{
	stack<int> stk;
	int flag = n % 2;
	for (int i = 0; i < n; i++)
	{
		if (i < n / 2)
			stk.push(a[i]);
		else if (i == n / 2 && n % 2 == 1)
			continue;
		else
		{
			int tmp = stk.top();
			stk.pop();
			if (tmp != a[i])
				return false;
		}
	}
	return true;

}

Stack* create_TwowayStack()
{
	Stack *stk = new Stack();
	stk->top1 = -1;
	stk->top2 = MAXSIZE;
	return stk;
}

bool Push_TwowayStack(int i, int val,Stack *stk)
{
	if (stk->top1 == stk->top2 - 1)
		return false;
	switch (i)
	{
	case(1):
		stk->data[++stk->top1] = val;
		break;
	case(2):
		stk->data[--stk->top2] = val;
		break;
	default:
		return false;
	}
	return true;
}

int Pop_TwowayStack(int i, Stack* stk)
{
	if (i == 1)
	{
		if (stk->top1 == -1)
			return -1;
		return stk->data[stk->top1--];
	}
	if (i == 2)
	{
		if (stk->top2 == MAXSIZE)
			return -1;
		return stk->data[stk->top2++];
	}
	return -1;
}

bool Push_LoopQueue(int val, SqQUeue* q)
{
	if (q->rear == q->front&&q->tag == 1)
		return false;
	q->data[q->rear] = val;
	q->rear = (q->rear + 1) % MAXSIZE;
	q->tag = 1;
	return true;
}

int Pop_LoopQueue(SqQUeue* q)
{
	if (q->front == q->rear && q->tag == 0)
		return -1;
	int res = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	q->tag = 0;
	return res;
}

void inverse_Queue(queue<int> q, stack<int> stk)
{
	while (!q.empty())
	{
		stk.push(q.front());
		q.pop();
	}
	while (!stk.empty())
	{
		q.push(stk.top());
		stk.pop();
	}
	return;
}

bool bracket(char a[],int n)
{
	stack<char> bracket;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == '(' || a[i] == '{' || a[i] == '[')
			bracket.push(a[i]);
		else if (a[i] == ')' || a[i] == '}' || a[i] == ']')
		{
			if (bracket.top() == a[i])
				bracket.pop();
			else
				return false;
		}
	}
	return bracket.empty();
}

void Train_Arrange()
{
	string train = "HHSSSH";
	stack<char> station;
	for (auto item = train.begin(); item != train.end(); item++)
	{
		if (*item == 'S')
			cout << *item << " ";
		else
			station.push(*item);
	}
	while (!station.empty())
	{
		cout << station.top()<<" ";
		station.pop();
	}
	return;
}

long Pn(int x,int n)
{
	stack<long> res;
	for(int i=0;i<=n;i++)
	{
		if (i == 0)
			res.push(1);
		else if (i == 1)
			res.push(2 * x);
		else
		{
			long x1 = res.top();
			res.pop();
			long x2 = res.top();
			res.push(x1);
			long x3 = x1 * 2 * x - x2 * 2 * (i - 1);
			printf_s("i:%2d,x1=%10ld  x2=%10ld	x3=%10ld\n", i, x1, x2, x3);
			res.push(x3);
		}
	}
	return res.top();
}