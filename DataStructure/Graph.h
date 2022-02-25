#pragma once
#include<iostream>
#include<cstdio>
#include <set>
#include <stack>
#include <queue>
using namespace std;

const int MaxVertexNum = 5;
int MAP[MaxVertexNum][MaxVertexNum] = { 
	{-1,1,-1,-1,4},//0
	{0,2,-1,-1,-1},//1
	{-1,1,-1,3,4},//2 
	{-1,-1,2,-1,-1},//3
	{0,-1,2,-1,-1}//4
};
typedef char VertexType;
typedef int EdgeType;
typedef struct {
	int Vex[MaxVertexNum];//顶点表
	EdgeType Edge[MaxVertexNum][MaxVertexNum];//边表
	int vexnum, arcnum;//当前图的顶点数、弧数
}MGraph;

typedef struct ArcNode {//边表节点
	int adjvex;//该弧所指向的顶点位置
	struct ArcNode* next;//指向下一条弧的指针
}ArcNode;

typedef struct VNode {//顶点表节点
	int data;//顶点信息
	ArcNode* first;//指向第一条依附该顶点的弧的指针
}VNode,AdjList[MaxVertexNum];

typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;

MGraph* create_MGraph(int a[][MaxVertexNum],int n)
{
	MGraph* map = new MGraph();
	map->arcnum = 0;
	map->vexnum = n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != -1)
			{
				map->arcnum++;
				map->Edge[i][a[i][j]] = 1;
			}
		}
	}
	return map;
}

ALGraph* create_ALGraph_ByMGraph(MGraph *map)
{
	ALGraph *ALMap = new ALGraph();
	ALMap->arcnum = 0;
	ALMap->vexnum = MaxVertexNum;
	for (int i = 0; i < MaxVertexNum; i++)
	{
		ALMap->vertices[i].data = i;
		ALMap->vertices[i].first = NULL;
	}
	for (int i = 0; i < MaxVertexNum; i++)
	{
		for (int j = 0; j < MaxVertexNum; j++)
		{
			if (map->Edge[i][j] == 1 && i != j)
			{
				ALMap->arcnum++;
				ArcNode* tmpArc = ALMap->vertices[i].first;
				ArcNode* p = new ArcNode();
				p->adjvex = j;
				p->next = NULL;
				if (!tmpArc)
				{
					ALMap->vertices[i].first = p;
				}
				else
				{
					while (tmpArc->next)
					{
						tmpArc = tmpArc->next;
					}
					tmpArc->next = p;
				}
			}
		}
	}
	return ALMap;
}

MGraph* create_MGraph_ByALGraph(ALGraph* ALMap)
{
	MGraph* map = new MGraph();
	map->arcnum = 0;
	map->vexnum = MaxVertexNum;
	memset(&map->Vex, 0, MaxVertexNum * sizeof(int));
	memset(map->Edge, 0, MaxVertexNum * MaxVertexNum * sizeof(int));
	for (int i = 0; i < ALMap->vexnum; i++)
	{
		ArcNode *p = ALMap->vertices[i].first;
		while (p)
		{
			map->arcnum++;
			map->Edge[ALMap->vertices[i].data][p->adjvex] = 1;
			p = p->next;
		}

	}
	return map;
}

int count_Arc_MGraph(MGraph* map)
{
	int cnt = 0;
	for (int i = 0; i < MaxVertexNum; i++)
		for (int j = 0; j < MaxVertexNum; j++)
			if (map->Edge[i][j] == 1)
				cnt++;
	return cnt;
}

int Count_Arc_ALGraph(ALGraph* map)
{
	int cnt = 0;
	for (int i = 0; i < MaxVertexNum; i++)
	{
		ArcNode *arc = map->vertices[i].first;
		while (arc)
		{
			cnt++;
			arc = arc->next;
		}
	}
	return cnt;
}

bool Adjcent_MGraph(MGraph* map,int x,int y)
{
	return map->Edge[x][y] == 1;
}

bool Adjcent_ALGraph(ALGraph* map, int x, int y)
{
	ArcNode *arc = map->vertices[x].first;
	while (arc)
	{
		if (arc->adjvex == y)
			return true;
		arc = arc->next;
	}
	return false;
}

int NextNeighbor_MGraph(MGraph* map, int x, int y)
{
	for (int i = y+1; i < MaxVertexNum; i++)
	{
		if (map->Edge[x][i] == 1)
			return i;
	}
	return -1;
}

int FirstNeighbor_MGraph(MGraph* map, int x)
{
	for (int i = 0; i < MaxVertexNum; i++)
		if (map->Edge[x][i] == 1)
			return i;
	return -1;
}

VNode* NextNeighbor_ALGraph(ALGraph* map, int x, int y)
{
	ArcNode* arc = map->vertices[x].first;
	while (arc)
	{
		if (arc->adjvex == y)
			return arc->next == NULL ? NULL : &map->vertices[arc->next->adjvex];
	}
	return NULL;
}

VNode* FirstNeighbor_ALGraph(ALGraph* map, int x)
{
	if (map->vertices[x].first)
		return &map->vertices[map->vertices[x].first->adjvex];
	else
		return NULL;
}

bool is_Tree_AlGraph(ALGraph* map)
{
	int Vnum = 0, Enum = 0;
	set<int> vised;
	DFS_ALGraph(map, 0, Vnum, Enum, vised);
	return Vnum == map->vexnum && Enum == 2 * (map->arcnum - 1);
}

void DFS_ALGraph(ALGraph* map, int v, int& Vnum, int& Enum, set<int> vised)
{
	vised.insert(v);
	VNode *neighbor = FirstNeighbor_ALGraph(map, v);
	while (neighbor)
	{
		Enum++;
		if (vised.count(neighbor->data) != 1)
			DFS_ALGraph(map, neighbor->data, Vnum, Enum, vised);
		neighbor = NextNeighbor_ALGraph(map, v, neighbor->data);
	}
}

void DFS_Non_RC_ALGraph(ALGraph* map, int x)
{
	stack<VNode*> stk;
	set<VNode*> vised;
	VNode* v = &map->vertices[x];
	stk.push(v);
	vised.insert(v);
	while (!stk.empty())
	{
		v = stk.top();
		stk.pop();
		cout << v->data << "->";
		for (VNode* neighbor = FirstNeighbor_ALGraph(map, x); neighbor != NULL; neighbor = NextNeighbor_ALGraph(map, x, neighbor->data))
		{
			if (vised.count(neighbor) == 0)
			{
				stk.push(neighbor);
				vised.insert(neighbor);
			}
		}
	}
}

void BFS_ALGraph(ALGraph* map,int x)
{
	set<VNode*> vised;
	queue<VNode*> q;
	q.push(&map->vertices[x]);
	vised.insert(&map->vertices[x]);
	while (!q.empty())
	{
		VNode* v = q.front();
		q.pop();
		cout << v->data << " ->";
		for (VNode* neighbor = FirstNeighbor_ALGraph(map, v->data); neighbor != NULL; neighbor = NextNeighbor_ALGraph(map, v->data, neighbor->data))
		{
			if (vised.count(neighbor) == 0)
			{
				vised.insert(neighbor);
				q.push(neighbor);
			}
		}
	}
	return;
}

void Find_Path(ALGraph* map, int start, int end,VNode* now,int path[],int len,set<VNode*>vised)
{
	if (now->data == end)
	{
		cout << path[0];
		for (int i = 1; i < len; i++)
			cout << "-> " << path[i];
		return;
	}
	vised.insert(now);
	path[len++] = now->data;
	for (VNode* neighbor = FirstNeighbor_ALGraph(map, now->data); neighbor; neighbor = NextNeighbor_ALGraph(map, now->data, neighbor->data))
	{
		if(vised.count(neighbor)==0)
			Find_Path(map, start, end, neighbor, path, len, vised);
		len--;
		vised.erase(neighbor);
	}
}