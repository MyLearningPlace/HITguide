#pragma once
#ifndef leastline_h
#define leastline_h
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <atlbase.h>
#include "read.h"
#define Max 100
#define INF 65535
using namespace std;
int next[100];
typedef struct Node {
	int N, E;
	int EdgeMatrix[Max][Max];
	int No;
} Map;
typedef struct{
	int n, e;
	int edge[Max][Max];
	int vertex[Max];
} MTGraph;
typedef wchar_t Place[Max];
struct node {
	int x, d;
	node() {}
	node(int a, int b) { x = a; d = b; }
	bool operator < (const node & a) const {
		if (d == a.d) return x<a.x;
		else return d > a.d;
	}
};
/**********************全局变量区********************/
int n, m;
vector<node> eg[Max];
int Distance[Max];
int DPath[Max], Short[Max];
/***********************程序区********************/
void CreateMTGraph(MTGraph *G, Map *Campus) {
	n = G->n = Campus->N;
	m = G->e = Campus->N;
	for (int i = 0; i<n; i++) {
		G->vertex[i] = i;
	}
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			G->edge[i][j] = INF;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Campus->EdgeMatrix[i][j]>0) {
				G->edge[i][j] = G->edge[j][i] = Campus->EdgeMatrix[i][j];
				eg[i].push_back(node(j, Campus->EdgeMatrix[i][j]));
				eg[j].push_back(node(i, Campus->EdgeMatrix[i][j]));
			}
		}
	}
}
void Dijkstra(MTGraph *G, Map *Campus, int fromflag) {
	CreateMTGraph(G, Campus);
	for (int i = 0; i <n; i++) Distance[i] = INF;
	Distance[fromflag] = 0;
	priority_queue<node> q;
	q.push(node(fromflag, Distance[fromflag]));
	while (!q.empty()){
		node x = q.top(); 
		q.pop();
		for (int i = 0; i<(int)eg[x.x].size(); i++) {
			node y = eg[x.x][i];
			if (Distance[y.x]>x.d + y.d) {
				Distance[y.x] = x.d + y.d;
				q.push(node(y.x, Distance[y.x]));
			}
		}
	}
}
void Dijkstra(MTGraph *G, int v) {
	int final[Max];
	for (int i = 0; i<G->n; i++){
		final[i] = 0;
		DPath[i] = G->edge[v][i];
		Short[i] = 0;
	}
	DPath[v] = 0;
	Short[v] = -1;
	final[v] = 1;
	for (int i = 1; i<G->n; i++) {
		int min = INF;
		int k = 0;
		for (int j = 0; j<G->n; j++) {
			if (!final[j] && DPath[j] < min) {
				k = j;
				min = DPath[j];
			}
		}
		final[k] = 1;
		for (int j = 0; j<G->n; j++) {
			if (!final[j] && (min + G->edge[k][j]<DPath[j])) {
				DPath[j] = min + G->edge[k][j];
				Short[j] = k;
			}
		}
	}
}
#endif;