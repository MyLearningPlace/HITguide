#pragma once
#ifndef initall_h
#define initall_h
#include "bus.h"
#include "plane.h"
#include "train.h"
#include "match.h"
#include "btree.h"
using namespace std;
/**********************全局变量区********************/
Bus *bus = new Bus[9];
Train *train = new Train[3];
Plane *plane = new Plane[3];
wifstream in("input.txt");
ifstream inedge("inedge.txt");
wifstream in2("input2.txt");
ifstream inedge2("inedge2.txt");
wifstream in3("input3.txt");
ifstream inedge3("inedge3.txt");
wifstream in4("input4.txt");
ifstream inedge4("inedge4.txt");
wifstream in5("input5.txt");
ifstream inedge5("inedge5.txt");
wofstream out("output.txt", ios::app);
/***********************程序区********************/
void InitBus(){
	bus[0].No =0;
	bus[0].time = {10,0,16,0,30};
	bus[0].locate = {18,23};
	bus[0].min = 10;
	bus[1].No = 63;
	bus[1].time = { 6,0,21,30,20 };
	bus[1].locate = { 9,14};
	bus[1].min = 15;
	bus[2].No = 82;
	bus[2].time = { 6,30,22,0,20 };
	bus[2].locate = { 9,30};
	bus[2].min = 15;
	bus[3].No = 25;
	bus[3].time = { 7,0,22,0,60 };
	bus[3].locate = { 55,14};
	bus[3].min = 10;
	bus[4].No = 84;
	bus[4].time = { 7,0,21,30,25 };
	bus[4].locate = { 55,24 };
	bus[4].min = 20;
	bus[5].No = 63;
	bus[5].time = { 6,0,21,30,20 };
	bus[5].locate = {9,0};
	bus[5].min = 3;
	bus[6].No = 82;
	bus[6].time = { 6,30,22,0,20 };
	bus[6].locate = { 9,0 };
	bus[6].min = 17;
	bus[7].No = 63;
	bus[7].time = { 6,0,21,30,20 };
	bus[7].locate = { 14,0 };
	bus[7].min = 12;
	bus[8].No = 82;
	bus[8].time = { 6,30,22,0,20 };
	bus[8].locate = { 30,0 };
	bus[8].min = 12;
	train[0].time = {6,24,6};
	train[0].times = 6;
	train[0].prize = 600;
	train[1].time = { 6,22,8 };
	train[1].times = 10;
	train[1].prize = 1000;
	train[2].time = { 4,24,4 };
	train[2].times = 12;
	train[2].prize = 1200;
	plane[0].time = {12,24,12};
	plane[0].times = 2;
	plane[0].prize = 1580;
	plane[1].time = { 12,24,12 };
	plane[1].times = 3;
	plane[1].prize = 2220;
	plane[2].time = { 12,24,12 };
	plane[2].times = 4;
	plane[2].prize = 2790;
}
void Menu() {
	cout << "*******************************************************************************************" << endl;
	cout << "                                      ***欢迎使用哈工大校园导航***" << endl;
	cout << "*******************************************************************************************" << endl;
	cout << "                     ***导航使用说明：                                     ***" << endl;
	cout << "                     ***                      本导航共收录五个校区100个地点***" << endl;
	cout << "                     ***                  基本包括所有三个区地点，所以用此 ***" << endl;
	cout << "                     ***                  导航，你可以到你想到的任何校内的 ***" << endl;
	cout << "                     ***                  地点！                           ***" << endl;
	cout << "*******************************************************************************************" << endl;
	out << "*******************************************************************************************" << endl;
	out << "                                      ***欢迎使用哈工大校园导航***" << endl;
	out << "*****************************************************************************************" << endl;
	out << "                   ***导航使用说明：                                     ***" << endl;
	out << "                   ***                      本导航共收录五个校区100个地点***" << endl;
	out << "                   ***                  基本包括所有三个区地点，所以用此 ***" << endl;
	out << "                   ***                  导航，你可以到你想到的任何校内的 ***" << endl;
	out << "                   ***                  地点！                           ***" << endl;
	out << "*****************************************************************************************" << endl;

}
int InitMap(Map *Campus) {
	in >> Campus->N;
	tree[0].n = Campus->N;
	Campus->No = 1;
	int n = Campus->N;
	for (int i = 0; i < n; i++){
		in >> tree[0].PlaceName[i];
		tree[0].Insert(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			inedge >> Campus->EdgeMatrix[i][j];
			if (Campus->EdgeMatrix[i][j]>0) {
				Campus->EdgeMatrix[j][i] = Campus->EdgeMatrix[i][j];
				Campus->E++;
			}
		}
	}
	return n;
}
int InitMap2(Map *Campus) {
	in2 >> Campus->N;
	tree[1].n = Campus->N;
	Campus->No = 2;
	int n = Campus->N;
	for (int i = 0; i < n; i++){
		in2 >> tree[1].PlaceName[i];
		tree[1].Insert(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			inedge2 >> Campus->EdgeMatrix[i][j];
			if (Campus->EdgeMatrix[i][j]>0) {
				Campus->EdgeMatrix[j][i] = Campus->EdgeMatrix[i][j];
				Campus->E++;
			}
		}
	}
	return n;
}
int InitMap3(Map *Campus) {
	in3 >> Campus->N;
	tree[2].n = Campus->N;
	Campus->No = 3;
	int n = Campus->N;
	for (int i = 0; i < n; i++){
		in3 >> tree[2].PlaceName[i];
		tree[2].Insert(i);
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++) {
			inedge3 >> Campus->EdgeMatrix[i][j];
			if (Campus->EdgeMatrix[i][j]>0) {
				Campus->EdgeMatrix[j][i] = Campus->EdgeMatrix[i][j];
				Campus->E++;
			}
		}
	}
	return n;
}
int InitMap4(Map *Campus) {
	in4 >> Campus->N;
	tree[3].n = Campus->N;
	Campus->No = 4;
	int n = Campus->N;
	for (int i = 0; i < n; i++) {
		in4 >> tree[3].PlaceName[i];
		tree[3].Insert(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			inedge4 >> Campus->EdgeMatrix[i][j];
			if (Campus->EdgeMatrix[i][j]>0) {
				Campus->EdgeMatrix[j][i] = Campus->EdgeMatrix[i][j];
				Campus->E++;
			}
		}
	}
	return n;
}
int InitMap5(Map *Campus) {
	in5 >> Campus->N;
	tree[4].n = Campus->N;
	Campus->No = 5;
	int n = Campus->N;
	for (int i = 0; i < n; i++) {
		in5 >> tree[4].PlaceName[i];
		tree[4].Insert(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			inedge5 >> Campus->EdgeMatrix[i][j];
			if (Campus->EdgeMatrix[i][j]>0) {
				Campus->EdgeMatrix[j][i] = Campus->EdgeMatrix[i][j];
				Campus->E++;
			}
		}
	}
	return n;
}
#endif;
