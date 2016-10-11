#pragma once
#ifndef read_h
#define read_h
#include <iostream>
#include <string>
#include "initall.h"
#define MAX 11
using namespace std;
/**********************全局变量区********************/
long int number;
int elem[MAX] = { 0 }, i = 0;
string num[10] = { "零","一","二","三","四","五","六","七","八","九" };
/***********************程序区********************/
int numsize(int &number) {
	while (number>0) {
		elem[i] = number % 10;
		number /= 10;
		i++;
	}
	return i;
}
int FirstThree(int &numsize) {
	if (numsize >= 9) {
		for (int j = numsize; j >= 9; j--) {
			if (j == 11 && elem[j - 1] != 0) cout << num[elem[j - 1]] << "百";
			if (j == 10) {
				if (elem[j - 1] == 0 && elem[j - 2] != 0) cout << "零";
				else if (elem[j - 1] != 0) {
					if (numsize == 10 && elem[i - 1] == 1) cout << "十";
					else cout << num[elem[j - 1]] << "十";
				}
			}
			if (j == 9 && elem[j - 1] != 0) cout << num[elem[j - 1]];
		}
		cout << "亿";
		numsize = 8;
		return 1;
	}
	return 0;
}
int CenterFour(int &numsize, int m) {
	if (m == 1) {
		if (elem[8] == 0 && (elem[7] != 0 || elem[6] != 0 || elem[5] != 0 || elem[4] != 0)) cout << "零";
	}
	if (numsize >= 5) {
		for (int i = numsize; i >= 5; i--) {
			if (i == 8) {
				if (elem[i - 1] == 0 && (elem[i - 2] != 0 || elem[i - 3] != 0 || elem[i - 4] != 0)) cout << "零";
				else if (elem[i - 1] != 0) cout << num[elem[i - 1]] << "千";
			}
			if (i == 7) {
				if (elem[i - 1] == 0 && elem[i] != 0 && (elem[i - 2] != 0 || elem[i - 3] != 0)) cout << "零";
				else if (elem[i - 1] != 0) cout << num[elem[i - 1]] << "百";
			}
			if (i == 6) {
				if (elem[i - 1] == 0 && elem[i] != 0 && elem[i - 2] != 0) cout << "零";
				else if (elem[i - 1] != 0) {
					if (numsize == 6 && elem[i - 1] == 1) cout << "十";
					else cout << num[elem[i - 1]] << "十";
				}
			}
			if (i == 5 && elem[i - 1] != 0) cout << num[elem[i - 1]];
		}
		for (int j = numsize; j >= 5; j--) {
			if (elem[j - 1] != 0) {
				cout << "万";
				break;
			}
		}
		numsize = 4;
		return 1;
	}
	return 0;
}
void LastFour(int &numsize, int &n) {
	if (n == 1) {
		if (elem[4] == 0 && (elem[3] != 0 || elem[2] != 0 || elem[1] != 0 || elem[0] != 0)) {
			cout << "零";
		}
		else if (elem[4] != 0 && elem[3] == 0 && (elem[2] != 0 || elem[1] != 0 || elem[0] != 0)) {
			cout << "零";
		}
	}
	for (int i = numsize; i >= 0; i--) {
		if (i == 4 && elem[i - 1] != 0) {
			cout << num[elem[i - 1]] << "千";
		}
		if (i == 3){
			if (elem[i - 1] == 0 && elem[i] != 0 && (elem[i - 2] != 0 || elem[i - 3] != 0)) {
				cout << "零";
			}
			else if (elem[i - 1] != 0) {
				cout << num[elem[i - 1]] << "百";
			}
		}
		if (i == 2) {
			if (elem[i - 1] == 0 && elem[i] != 0 && elem[i - 2] != 0) {
				cout << "零";
			}
			else if (elem[i - 1] != 0) {
				if (numsize == 2 && elem[i - 1] == 1) {
					cout << "十";
				}
				else {
					cout << num[elem[i - 1]] << "十";
				}
			}
		}
		if (i == 1 && elem[i - 1] != 0) {
			cout << num[elem[i - 1]];
		}
	}
}
void Read(int number) {
	int nusize = numsize(number);
	int m = FirstThree(nusize);
	int n = CenterFour(nusize, m);
	LastFour(nusize, n);
}
void ReadPoint(int number) {
	int g, s, b;
	g = number % 10;
	s = (number / 10) % 10;
	b = (number / 100) % 10;
	cout << num[b] << num[s] << num[g];
}
#endif;