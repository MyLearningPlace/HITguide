#pragma once
#ifndef match_h
#define match_h
#include "leastline.h"
#include "btree.h"
using namespace std;
BTree *tree = new BTree[5];

/***********************³ÌÐòÇø********************/
bool KMP(Place text, Place pattern,int next[]);
int Locate(Place place,int next[]){
	for (int i = 0; i < 5; i++){
		if (tree[i].Search(tree[i].Root, place) >= 0) return tree[i].Search(tree[i].Root, place) + i * 100;
	}
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < tree[j].n; i++) {
			if (KMP(place, tree[j].PlaceName[i],next)) return i + j * 100;
		}
	}
	return -1;
}
void Next(Place pattern, int next[]) {
	int tsize, k;
	int psize = (int)wcslen(pattern);
	next[0] = 0;
	for (tsize = 1, k = 0; tsize < psize; tsize++) {
		while (k > 0 && pattern[tsize] != pattern[k])
			k = next[k - 1];
		if (pattern[tsize] == pattern[k]) {
			k++;
		}
		next[tsize] = k;
	}
}
bool KMP(Place text, Place pattern,int next[]){
	Next(pattern,next);
	int psize = (int)wcslen(pattern);
	int tsize = (int)wcslen(text);
	int i, k;
	for (int j = 0; j < psize; j++) {
		if (text[0] == pattern[j]){
			for (i = 0, k = j; i < tsize, k < psize; i++, k++) {
				if (pattern[k] != text[i]) break;
			}
			if (i == tsize && pattern[k - 1] == text[i - 1]) return true;
		}
	}
	return false;
	/*
	for (int i = 0, j = 0; i < tsize; i++) {
		while (j > 0 && pattern[j] != text[i])
			j = next[j - 1];
		if (pattern[j] == text[i])  j++;
		if (j == psize - 1){
			return true;
		}
	}
	return false;
	*/
}
#endif;