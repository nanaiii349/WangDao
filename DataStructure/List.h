#pragma once
#include<iostream>
#include<cstdio>
#include<stack>
#include<vector>
#include <set>
using namespace std;

typedef struct listNode {
	int data;
	struct listNode* next;
	struct listNode* pre;
}ListNode,*ListPointer;

ListPointer create_Oneway_linkedList_withHead(int a[], int n)
{
	cout << "this is a linklist" << endl;
	ListPointer head = new ListNode();
	head->data = -1;
	head->next = NULL;
	ListPointer pre = head;
	for (int i = 0; i < n; i++)
	{
		ListPointer p = new ListNode();
		p->data = a[i];
		pre->next = p;
		pre = p;
	}
	pre->next = NULL;
	return head;
}

ListPointer create_Oneway_linkedList_withoutHead(int a[], int n)
{
	if (n == 0)
		return NULL;
	cout << "this is a linklist" << endl;
	ListPointer head = new ListNode();
	head->data = a[0];
	head->next = NULL;
	ListPointer pre = head;
	for (int i = 1; i < n; i++)
	{
		ListPointer p = new ListNode();
		p->data = a[i];
		pre->next = p;
		pre = p;
	}
	pre->next = NULL;
	return head;
}

ListPointer create_Twoway_Loop_LinkedList_withoutHead(int a[], int n)
{
	ListPointer head = new ListNode();
	head->data = -1;
	head->next = NULL;
	head->pre = NULL;
	ListNode* pre = head,*p=NULL;
	for (int i = 0; i < n; i++)
	{
		p = new ListNode();
		p->data = a[i];
		p->next = head;
		p->pre = pre;
		pre->next = p;
		pre = p;
	}
	head->pre = p;
	return head;
}

ListPointer create_Twoway_LinkedList_withoutHead(int a[], int n)
{
	ListPointer head = new ListNode();
	ListNode* p = NULL, * pre = head;
	for (int i = 0; i < n; i++)
	{
		p = new ListNode();
		p->data = a[i];
		p->pre = pre;
		pre->next = p;
		p->next = NULL;
		pre = p;
	}
	return head;
}

ListPointer create_Oneway_Loop_LinkedList_withoutHead(int a[], int n)
{
	ListPointer head = new ListNode();
	head->data = -1;
	head->next = NULL;
	ListNode* p = NULL, * pre = head;
	for (int i = 0; i < n; i++)
	{
		p = new ListNode();
		p->data = a[i];
		pre->next = p;
		p->next = head;
		pre = p;
	}
	return head;
}

int get_List_Length(ListPointer head)
{
	ListNode* p = head;
	int cnt = 0;
	while (p)
	{
		cnt++;
		p = p->next;
	}
	return cnt;
}

void output_linkedList(ListPointer head)
{
	while (head)
	{
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void output_Twoway_Loop_LinkedList(ListPointer head)
{
	ListNode*p = head->next;
	cout << "正向"<<endl;
	while (p->data != -1)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl<<"反向"<<endl;
	p = head->pre;
	while (p->data!=-1)
	{
		cout << p->data << " ";
		p = p->pre;
	}
	cout << endl;
}

void output_Oneway_Loop_LinkedList(ListPointer head)
{
	ListNode* p = head->next;
	while (p->data != -1)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

void output_inverse_linkedList(ListPointer head)
{
	stack<int> stk;
	head = head->next;
	while (head)
	{
		stk.push(head->data);
		head = head->next;
	}
	while(!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}
}

void delete_Node(ListPointer &p, ListPointer &pre)
{
	pre->next = p->next;
	free(p);
	p = pre->next;
}

void delete_X_Oneway_linkedList_withoutHead(ListPointer& head, int x)
{
	ListNode* p;
	if (!head)
		return;
	if (head->data == x)
	{
		p = head;
		head = head->next;
		free(p);
		delete_X_Oneway_linkedList_withoutHead(head, x);
	}
	else
		delete_X_Oneway_linkedList_withoutHead(head->next, x);
}

void delete_X_Oneway_linkedList_withHead(ListPointer head, int x)
{
	ListNode* p = head->next, * pre = head;
	while (p)
	{
		if (p->data == x)
			delete_Node(p, pre);
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

void delete_Min_Oneway_linkedList_withHead(ListPointer &head)
{
	head->data = head->next->data;
	ListNode* p = head->next,*pre=head;
	listNode* minp = p, * minpre = pre;
	while (p)
	{
		if (p->data < head->data)
		{
			head->data = p->data;
			minp = p;
			minpre = pre;
		}
		pre = p;
		p = p->next;
	}
	minpre->next = minp->next;
	free(minp);
}

void inverse_Oneway_linkedList_withHead(ListPointer& head)
{
	ListNode* p = head->next;
	head->next = NULL;
	while (p)
	{
		ListNode* tmp = p->next;
		p->next = head->next;
		head->next = p;
		p = tmp;
	}
}

//@brief 将结点q插入节点p前
void insertNode(ListNode* p, ListNode* pre,ListNode* q,ListNode* qpre)
{
	pre->next = q;
	qpre->next = q->next;
	q->next = p;
}

void sort_Oneway_linkedList_withHead(ListPointer& head)
{
	ListNode* p = head->next, *pre = head;
	int sorted = 0;
	while (p)
	{
		ListNode* tmp = head->next,*tmpre=head;
		for (int i = 0; i < sorted; i++)
		{
			if (!tmp)
				break;
			if (p->data < tmp->data)
			{
				insertNode(tmp, tmpre,p,pre);
				break;
			}
			tmpre = tmp;
			tmp = tmp->next;
		}
		pre = p;
		p = p->next;
		sorted++;
	}
}

void delete_between_X_Y_Oneway_linkedList_withHead(ListPointer& head, int x, int y)
{
	ListNode* p = head->next, * pre = head;
	while (p)
	{
		if (p->data >= x && p->data <= y)
			delete_Node(p, pre);
		else
		{
			pre = p;
			p = p->next;
		}
	}
}

ListNode* get_CommonNode(ListPointer& a, ListPointer& b)
{
	int la = get_List_Length(a);
	int lb = get_List_Length(b);
	if (la > lb)
		for (int i = 0; i < la - lb; i++)
			a = a->next;
	if (lb > la)
		for (int i = 0; i < lb - la; i++)
			b = b->next;
	while (a)
	{
		if (a == b)
		{
			return a;
		}
		a = a->next;
		b = b->next;
	}
	return NULL;
}

void spilt_Oneway_linkedList_withHead(ListPointer& head)
{
	ListPointer b = new ListNode();
	ListNode* p = head->next;
	head->next = NULL;
	b->data = -1;
	b->next = NULL;
	ListNode *lastA = head, *lastB = b;
	int flag = 0;
	while (p)
	{
		if (flag %2 == 0)
		{
			lastA->next = p;
			lastA = p;
			p = p->next;
			lastA->next = NULL;
		}
		else
		{
			lastB->next = p;
			lastB = p;
			p = p->next;
			lastB->next = NULL;
		}
		flag++;
	}
	output_linkedList(head);
	output_linkedList(b);
}

void delete_Repeat_Element(ListPointer& head)
{
	set<int> vis;
	ListNode* p = head->next, * pre = head;
	while (p)
	{
		if (vis.count(p->data) == 0)
		{
			vis.insert(p->data);
			pre = p;
			p = p->next;
		}
		else
		{
			ListNode* tmp = p;
			pre->next = p->next;
			p = p->next;
			free(tmp);
		}
	}
}

ListPointer merge_Oneway_linkedList_withHead(ListPointer a,ListPointer b)
{
	ListPointer head = new ListNode();
	head->data = -1;
	ListNode* tmp = NULL;
	while (a&&b)
	{
		if (a->data > b->data)
		{
			tmp = b;
			b = b->next;
		}
		else
		{
			tmp = a;
			a = a->next;
		}
		tmp->next = head->next;
		head->next = tmp;
	}
	if (a)
	{
		while (a)
		{
			tmp = a;
			a = a->next;
			tmp->next = head->next;
			head->next = tmp;
		}
	}
	if (b)
	{
		while (b)
		{
			tmp = b;
			b = b->next;
			tmp->next = head->next;
			head->next = tmp;
		}
	}
	return head;
}

ListPointer get_CommonList(ListPointer a, ListPointer b)
{
	ListPointer head = new ListNode();
	ListNode* pa = a->next,*pb=b->next;
	while (pa && pb)
	{
		if (pa->data == pb->data)
		{
			ListNode* tmp = new ListNode();
			tmp->data = pa->data;
			pa = pa->next;
			pb = pb->next;
			tmp->next = head->next;
			head->next = tmp;
		}
		else if (pa->data < pb->data)
			pa = pa->next;
		else
			pb = pb->next;
	}
	return head;
}

bool is_Subsequence(ListPointer a, ListPointer b)
{
	ListNode* pa = a->next, * pb;
	while (pa)
	{
		ListNode* tmp = pa;
		pb = b->next;
		while (pb)
		{
			if (!tmp || tmp->data != pb->data)
				break;
			else if (tmp->data == pb->data)
			{
				pb = pb->next;
				tmp = tmp->next;
			}
		}
		if (!pb)
			return true;
		pa = pa->next;
	}
	return false;
}

bool is_symmetry_Twoway_Loop_LinkedList_withoutHead(ListPointer head)
{
	ListNode* h = head->next, * t = head->pre;
	while (h->data!=-1)
	{
		if (h->data != t->data)
			return false;
		h = h->next;
		t = t->pre;
	}
	return true;
}

void merge_Twoway_Loop_LinkedList_withoutHead(ListPointer a, ListPointer b)
{
	a->pre->next = b->next;
	b->next->pre = a->pre;
	a->pre = b->pre;
	b->pre->next = a;
	free(b);
}

void delete_Min_Oneway_Loop_LinkedList(ListPointer head)
{
	while (head->next != head)
	{
		ListNode* p = head->next,*pre=head;
		ListNode* minp = p, * minpre = head;
		while (p!=head)
		{
			if (p->data < minp->data)
			{
				minp = p;
				minpre = pre;
			}
			pre = p;
			p = p->next;
		}
		cout << minp->data << " ";
		minpre->next = minp->next;
		free(minp);
	}
	free(head);
}

bool is_Loop(ListPointer head)
{
	ListNode* fast = head, *slow = head;
	int i = 0;
	while (fast->next&&slow)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
			return false;
	}
	return true;
}

ListPointer change_list(ListPointer head)
{
	ListNode* p = head->next,*pre=head,*q=head->next;
	while (q->next)
	{
		pre = pre->next;
		p = p->next;
		q = q->next;
		if(q->next)
			q = q->next;
	}
	pre->next = NULL;
	ListPointer h = new ListNode();
	h->data = -1;
	h->next = NULL;
	while (p)
	{
		ListNode* tmp = p;
		p = p->next;
		tmp->next = h->next;
		h->next = tmp;
	}
	p = head->next;
	pre = head;
	q = h->next;
	while (p&&q)
	{
		ListNode* tmp1 = p, *tmp2 = q;
		p = p->next;
		q = q->next;
		pre->next = tmp1;
		tmp1->next = tmp2;
		tmp2->next = NULL;
		pre = tmp2;
	}
	if (p)
		pre->next = p;
	if (q)
		pre->next = q;
	output_linkedList(head);
	return head;
}

ListNode* get_Kth(ListPointer head, int k)
{
	ListNode* fast = head->next, *slow = head->next;
	while (k--)
	{
		fast = fast->next;
		if (!fast)
			return NULL;
	}
	cout << fast->data << endl;
	while (fast)
	{
		fast = fast->next;
		slow = slow->next;
	}
	cout << slow->data << endl;
	return slow;
}