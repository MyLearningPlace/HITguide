#pragma once
#ifndef btree_h
#define btree_h
#include "initall.h"
#include <iomanip>
#include <queue>
using namespace std;
typedef wchar_t Elem;
#define M 5

class BTree{
public:
	typedef struct lue {
		int value;
		Elem e;
	} Value;
	typedef struct de {
		bool IsLeaf;
		int num;
		Value value[2 * M - 1];
		de *child[2 * M];
		de(bool b = true, int n = 0)
			:IsLeaf(b), num(n) {}
	} BTreeNode;
	BTreeNode * Root;  
	Place PlaceName[Max];
	int n;
public:
	BTree() {
		Root = NULL;  
	}
	~BTree() {
		free(Root);
	}
int PlaceSearch(Elem *e){
	for (int i = 0; i <n; i++){
		if(wcscmp(e, PlaceName[i]) == 0) return i;
	}
	return -1;
}
void Insert(int key){
	if (Search(Root,PlaceName[key])>=0) return;
	else{
			if (!Root) Root = new BTreeNode();
			if (Root->num == 2*M-1){
				BTreeNode *p = new BTreeNode();  
				p->IsLeaf = false;
				p->child[0] = Root;
				Split(p,Root,0);
			   Root = p; 
			}
			InsertNode(Root, key);
		}
	}
int Search(BTreeNode *p,Elem *e){
       int key=-1;
	   if(PlaceSearch(e)>=0)  key= PlaceSearch(e);
		if (!p) return -1;
		else{
			int i;
			for (i = 0; i<p->num && key>p->value[i].value; i++);
			if (i<p->num && key == p->value[i].value) return key;
			else{
				if (p->IsLeaf)   return - 1;
				else return Search(p->child[i], e);
			}
		}
	}
void Split(BTreeNode *p,BTreeNode *q, int key){
		BTreeNode *rchild = new BTreeNode();
		rchild->IsLeaf = q->IsLeaf;
	     rchild->num = M-1;
		int i;
		for (i = 0; i<M-1; i++){
			rchild->value[i] = q->value[i + M];
		}
		if (!q->IsLeaf){
			for (i = 0; i<M; i++){
				rchild->child[i] = q->child[i + M];
			}
		}
		q->num = M-1;  //更新左子树的关键字个数
		for (i = p->num; i>key; i--){
			p->child[i + 1] = p->child[i];
			p->value[i] = p->value[i - 1];
		}
		p->num++;  //更新父节点的关键字个数
		p->child[key + 1] = rchild;  //存储右子树指针
		p->value[key] = q->value[M-1];//把节点的中间值提到父节点
	}
void InsertNode(BTreeNode *p, int key){
		int i = p->num;  
		if (p->IsLeaf){
			for (; i > 0 && key < p->value[i - 1].value; i--) {
				p->value[i] = p->value[i - 1];  
			}
			p->value[i].value = key;  
			wcscpy(&p->value[i].e,PlaceName[key]);
			p->num++; 
		}else{
			for (; i > 0 && key < p->value[i - 1].value;i--);
			BTreeNode *t = p->child[i];   
			if (t->num == 2*M-1){
				Split(p,t,i);
				if (key>p->value[i].value)  
					t = p->child[i + 1];
			}
			InsertNode(t, key); 
		}
	}
/*void Order(){
		queue<BTreeNode*> q;
		BTreeNode *p = Root;
		if (p) {
			q.push(p);
			while (!q.empty()) {
				p = q.front();
				for (int i = 0; i <p->num; i++) {
					if (p->child[i]) q.push(p->child[i]);
					cout << setw(5) << p->value[i].value;
				}
				if (p->child[p->num]) q.push(p->child[p->num]);
				q.pop();
			}
		}
	}*/
};
#endif;