#pragma once
#ifndef hrbxq_h
#define hrbxq_h
#include "initall.h"
#include "leastline.h"
#include <cmath>

/**********************ȫ�ֱ�����********************/
Map *Campus = new Map[5];
MTGraph *G = new MTGraph[5];
Place from, to;
int fromflag, toflag;
int next2[Max];
/***********************������********************/
void Input() {
	InitMap(&Campus[0]);
	InitMap2(&Campus[1]);
	InitMap3(&Campus[2]);
	InitMap4(&Campus[3]);
	InitMap5(&Campus[4]);
	do {
		cout << "������������㣺";
		wcin >> from;
		out << "�������Ϊ��" << from << endl;
		fromflag = Locate(from,next2);
	} while (fromflag < 0);
	do {
		cout << "�����������յ㣺";
		wcin >> to;
		out << "�����յ�Ϊ��" << to<< endl;
		toflag = Locate(to,next2);
	} while (toflag < 0);
}
void HrbXq() {
	 if (fromflag / 100 == toflag / 100) {
		 Dijkstra(&G[fromflag/100], &Campus[fromflag/100], fromflag % 100);
		 if (Distance[toflag % 100] < 1000){
			cout << "���ؾ���Ϊ��" << Distance[toflag % 100] << "M" << "��";
			out << "���ؾ���Ϊ��" << Distance[toflag % 100] << "M" <<endl;
			Read(Distance[toflag % 100]);
			cout << "�ף�" << endl;
		}
		else {
			double distance = Distance[toflag % 100] / 1000.0;
			cout << "���ؾ���Ϊ��" << distance << "KM" << "��";
			out << "���ؾ���Ϊ��" << distance << "KM" << endl;
			Read((Distance[toflag % 100] / 1000));
			cout << "��";
			ReadPoint(Distance[toflag % 100]);
			cout << "ǧ�ף�" << endl;
		}
		cout << "���·��Ϊ��" << endl;
		out << "���·��Ϊ��" << endl;
		Dijkstra(&G[fromflag/100], fromflag % 100);
		Stack *line = new Stack();
		int j = toflag % 100;
		while (Short[j] != -1 && Short[j] != 0) {
			j = Short[j];
			Push(line, j);
		}
		wcout << tree[fromflag/100].PlaceName[fromflag % 100] << "-->";
		out << tree[fromflag / 100].PlaceName[fromflag % 100] << "-->";
		while (!IsEmpty(*line)) {
			wcout << tree[fromflag/100].PlaceName[Top(*line)] << "-->";
			out << tree[fromflag / 100].PlaceName[Top(*line)] << "-->";
			Pop(line);
		}
		wcout << tree[fromflag/100].PlaceName[toflag % 100] << endl;
		out << tree[fromflag / 100].PlaceName[toflag % 100] << endl;

	}
	else if ((fromflag / 100 == 0 && toflag / 100 == 1) || (fromflag / 100 == 1 && toflag / 100 == 0)) {
		if (fromflag / 100 == 0) {
			Dijkstra(&G[0], &Campus[0], fromflag % 100);
			double walk1 = Distance[9] / 60.0;
			double walk2 = Distance[55] / 60.0;
			double walk3 = Distance[18] / 60.0;
			Dijkstra(&G[1], &Campus[1], toflag % 100);
			double walk4 = Distance[14] / 60.0;
			double walk5 = Distance[30] / 60.0;
			double walk6 = Distance[24] / 60.0;
			double walk7 = Distance[23] / 60.0;
			double timehold[5];
			timehold[0] = bus[0].GetTime(walk3, walk7);
			timehold[1] = bus[1].GetTime(walk1, walk4);
			timehold[2] = bus[2].GetTime(walk1, walk5);
			timehold[3] = bus[3].GetTime(walk2, walk4);
			timehold[4] = bus[4].GetTime(walk2, walk6);
			double mintime = timehold[0];
			int number = 0;
			for (int i = 1; i < 5; i++) {
				if (timehold[i] < mintime) {
					mintime = timehold[i];
					number = i;
				}
			}
			int tmp, tmp2;
			if (mintime == INF) {
				tmp = walk1 >= walk2 ? 55 : 9;
				tmp2 = walk4 >= walk5 ? 30 : 14;
			}
			else {
				tmp = bus[number].locate.head;
				tmp2 = bus[number].locate.tail;
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			Dijkstra(&G[0], fromflag % 100);
			Stack *line = new Stack();
			int j = tmp;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[0].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[0].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[0].PlaceName[tmp];
			Dijkstra(&G[0], &Campus[0], fromflag % 100);
			if (Distance[tmp] < 1000) {
				cout << "\t·��Ϊ��" << Distance[tmp] << "M" << endl;
			}
			else {
				double distance = Distance[tmp] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime == INF) cout << "�ڶ��Σ�������!" << "�˳��ص㣺";
			else if (bus[number].No == 0) cout << "�ڶ��Σ��������У����" << "�˳��ص㣺";
			else cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			wcout << tree[0].PlaceName[tmp];
			cout << "\t����ص㣺";
			wcout << tree[1].PlaceName[tmp2] << endl;
			cout << "�����Σ����У���";
			Dijkstra(&G[1], tmp2);
			Stack *line2 = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line2, j);
			}
			wcout << tree[1].PlaceName[tmp2] << "-->";
			while (!IsEmpty(*line2)) {
				wcout << tree[1].PlaceName[Top(*line2)] << "-->";
				Pop(line2);
			}
			wcout << tree[1].PlaceName[toflag % 100];
			Dijkstra(&G[1], &Campus[1], tmp2);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime != INF) cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
		}
		else {
			Dijkstra(&G[0], &Campus[0], toflag % 100);
			double walk1 = Distance[9] / 60.0;
			double walk2 = Distance[55] / 60.0;
			double walk3 = Distance[18] / 60.0;
			Dijkstra(&G[1], &Campus[1], fromflag % 100);
			double walk4 = Distance[14] / 60.0;
			double walk5 = Distance[30] / 60.0;
			double walk6 = Distance[24] / 60.0;
			double walk7 = Distance[23] / 60.0;
			double timehold[5];
			timehold[0] = bus[0].GetTime(walk3, walk7);
			timehold[1] = bus[1].GetTime(walk1, walk4);
			timehold[2] = bus[2].GetTime(walk1, walk5);
			timehold[3] = bus[3].GetTime(walk2, walk4);
			timehold[4] = bus[4].GetTime(walk2, walk6);
			double mintime = timehold[0];
			int number = 0;
			for (int i = 1; i < 5; i++) {
				if (timehold[i] < mintime) {
					mintime = timehold[i];
					number = i;
				}
			}
			int tmp, tmp2;
			if (mintime == INF) {
				tmp = walk1 >= walk2 ? 55 : 9;
				tmp2 = walk4 >= walk5 ? 30 : 14;
			}
			else {
				tmp = bus[number].locate.head;
				tmp2 = bus[number].locate.tail;
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[1], fromflag % 100);
			Stack *line = new Stack();
			int j = tmp2;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[1].PlaceName[fromflag % 100] << "-->";
			out << tree[1].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[1].PlaceName[Top(*line)] << "-->";
				out << tree[1].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[1].PlaceName[tmp2];
			out << tree[1].PlaceName[tmp2];
			Dijkstra(&G[1], &Campus[1], fromflag % 100);
			if (Distance[tmp2] < 1000) {
				cout << "\t·��Ϊ��" << Distance[tmp2] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[tmp2] << "M" << endl;

			}
			else {
				double distance = Distance[tmp2] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
			}
			else if (bus[number].No == 0) {
				cout << "�ڶ��Σ��������У����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������У����" << "�˳��ص㣺";
			}
			else {
				cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			}
			wcout << tree[1].PlaceName[tmp2];
			cout << "����ص㣺";
			wcout << tree[0].PlaceName[tmp] << endl;
			cout << "�����Σ����У���";
			out << tree[1].PlaceName[tmp2];
			out << "����ص㣺";
			out << tree[0].PlaceName[tmp] << endl;
			out << "�����Σ����У���";
			Dijkstra(&G[0], tmp);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[0].PlaceName[tmp] << "-->";
			out << tree[0].PlaceName[tmp] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[0].PlaceName[Top(*line)] << "-->";
				out << tree[0].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[0].PlaceName[toflag % 100];
			out << tree[0].PlaceName[toflag % 100];
			Dijkstra(&G[0], &Campus[0], tmp);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
				out << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
			}
		}
	}
	else if ((fromflag / 100 == 0 && toflag / 100 == 2) || (fromflag / 100 == 2 && toflag / 100 == 0)) {
		if (fromflag / 100 == 0) {
			Dijkstra(&G[0], &Campus[0], fromflag % 100);
			double walk1 = Distance[9] / 60.0;
			Dijkstra(&G[2], &Campus[2], toflag % 100);
			double walk2 = Distance[0] / 60.0;
			double timehold[2];
			timehold[0] = bus[5].GetTime(walk1, walk2);
			timehold[1] = bus[6].GetTime(walk1, walk2);
			double mintime = walk1 + walk2 + 8.0;
			int number = 0;
			for (int i = 0; i < 1; i++) {
				if (timehold[i] < mintime) {
					mintime = timehold[i];
					number = i + 5;
				}
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[0], fromflag % 100);
			Stack *line = new Stack();
			int j = 9;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[0].PlaceName[fromflag % 100] << "-->";
			out << tree[0].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[0].PlaceName[Top(*line)] << "-->";
				out << tree[0].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[0].PlaceName[9];
			out << tree[0].PlaceName[9];
			Dijkstra(&G[0], &Campus[0], fromflag % 100);
			if (Distance[9] < 1000) {
				cout << "\t·��Ϊ��" << Distance[9] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[9] << "M" << endl;
			}
			else {
				double distance = Distance[9] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (number == 0) {
				cout << "�ڶ��Σ����鲽��!" << "��㣺";
				out << "�ڶ��Σ����鲽��!" << "��㣺";
			}
			else {
				cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			}
			wcout << tree[0].PlaceName[9];
			cout << "\t����ص㣺";
			wcout << tree[2].PlaceName[0] << endl;
			cout << "�����Σ����У���";
			out << tree[0].PlaceName[9];
			out << "\t����ص㣺";
			out << tree[2].PlaceName[0] << endl;
			out << "�����Σ����У���";
			Dijkstra(&G[2], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[2].PlaceName[0] << "-->";
			out << tree[2].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[2].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[2].PlaceName[toflag % 100];
			out << tree[2].PlaceName[toflag % 100];
			Dijkstra(&G[2], &Campus[2], 0);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
			out << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
		}
		else {
			Dijkstra(&G[0], &Campus[0], toflag % 100);
			double walk1 = Distance[9] / 60.0;
			Dijkstra(&G[2], &Campus[2], fromflag % 100);
			double walk2 = Distance[0] / 60.0;
			double timehold[2];
			timehold[0] = bus[5].GetTime(walk1, walk2);
			timehold[1] = bus[6].GetTime(walk1, walk2);
			double mintime = walk1 + walk2 + 8.0;
			int number = 0;
			for (int i = 0; i < 1; i++) {
				if (timehold[i] < mintime) {
					mintime = timehold[i];
					number = i + 5;
				}
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[2], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[2].PlaceName[fromflag % 100] << "-->";
			out << tree[2].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[2].PlaceName[Top(*line)] << "-->";
				out << tree[2].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[2].PlaceName[0];
			out << tree[2].PlaceName[0];
			Dijkstra(&G[2], &Campus[2], fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (number == 0) {
				cout << "�ڶ��Σ����鲽��!" << "��㣺";
				out << "�ڶ��Σ����鲽��!" << "��㣺";
			}
			else {
				cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			}
			wcout << tree[2].PlaceName[0];
			cout << "\t����ص㣺";
			wcout << tree[0].PlaceName[9] << endl;
			cout << "�����Σ����У���";
			out << tree[2].PlaceName[0];
			out << "\t����ص㣺";
			out << tree[0].PlaceName[9] << endl;
			out << "�����Σ����У���";
			Dijkstra(&G[0], 9);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[0].PlaceName[9] << "-->";
			out << tree[0].PlaceName[9] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[0].PlaceName[Top(*line)] << "-->";
				out << tree[0].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[0].PlaceName[toflag % 100];
			out << tree[0].PlaceName[toflag % 100];
			Dijkstra(&G[0], &Campus[0], 9);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
			out << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
		}
	}
	else if ((fromflag / 100 == 1 && toflag / 100 == 2) || (fromflag / 100 == 2 && toflag / 100 == 1)) {
		if (fromflag / 100 == 1) {
			Dijkstra(&G[1], &Campus[1], fromflag % 100);
			double walk1 = Distance[14] / 60.0;
			double walk2 = Distance[30] / 60.0;
			Dijkstra(&G[2], &Campus[2], toflag % 100);
			double walk3 = Distance[0] / 60.0;
			double timehold[2];
			timehold[0] = bus[7].GetTime(walk1, walk3);
			timehold[1] = bus[8].GetTime(walk3, walk2);
			double mintime;
			int number;
			if (timehold[0] < timehold[1]) {
				mintime = timehold[0];
				number = 7;
			}
			else {
				mintime = timehold[1];
				number = 8;
			}
			int tmp;
			if (mintime == INF) {
				tmp = walk1 >= walk2 ? 30 : 14;
			}
			else {
				tmp = bus[number].locate.head;
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[1], fromflag % 100);
			Stack *line = new Stack();
			int j = tmp;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[1].PlaceName[fromflag % 100] << "-->";
			out << tree[1].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[1].PlaceName[Top(*line)] << "-->";
				out << tree[1].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[1].PlaceName[tmp];
			out << tree[1].PlaceName[tmp];
			Dijkstra(&G[1], &Campus[1], fromflag % 100);
			if (Distance[tmp] < 1000) {
				cout << "\t·��Ϊ��" << Distance[tmp] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[tmp] << "M" << endl;
			}
			else {
				double distance = Distance[tmp] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "�ڶ��Σ�������!" << "�˳���㣺";
				out << "�ڶ��Σ�������!" << "�˳���㣺";
			}
			else {
				cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			}
			wcout << tree[1].PlaceName[tmp];
			cout << "\t����ص㣺";
			wcout << tree[2].PlaceName[0] << endl;
			cout << "�����Σ����У���";
			out << tree[1].PlaceName[tmp];
			out << "\t����ص㣺";
			out << tree[2].PlaceName[0] << endl;
			out << "�����Σ����У���";
			Dijkstra(&G[2], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[2].PlaceName[0] << "-->";
			out << tree[2].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[2].PlaceName[Top(*line)] << "-->";
				out << tree[2].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[2].PlaceName[toflag % 100];
			out << tree[2].PlaceName[toflag % 100];
			Dijkstra(&G[2], &Campus[2], 0);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
				out << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
			}
		}
		else{
			Dijkstra(&G[2], &Campus[2], fromflag % 100);
			double walk1 = Distance[0] / 60.0;
			Dijkstra(&G[1], &Campus[1], toflag % 100);
			double walk2 = Distance[14] / 60.0;
			double walk3 = Distance[30] / 60.0;
			double timehold[2];
			timehold[0] = bus[7].GetTime(walk1, walk2);
			timehold[1] = bus[8].GetTime(walk1, walk3);
			double mintime;
			int number;
			if (timehold[0] < timehold[1]) {
				mintime = timehold[0];
				number = 7;
			}
			else {
				mintime = timehold[1];
				number = 8;
			}
			int tmp;
			if (mintime == INF) {
				tmp = walk2 >= walk3 ? 30 : 14;
			}
			else {
				tmp = bus[number].locate.head;
			}
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[2], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[2].PlaceName[fromflag % 100] << "-->";
			out << tree[2].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[2].PlaceName[Top(*line)] << "-->";
				out << tree[2].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[2].PlaceName[0];
			out << tree[2].PlaceName[0];
			Dijkstra(&G[2],&Campus[2],fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "�ڶ��Σ�������!" << "�˳���㣺";
				out << "�ڶ��Σ�������!" << "�˳���㣺";
			}
			else {
				cout << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
				out << "�ڶ��Σ��������" << bus[number].No << "·����" << "�˳��ص㣺";
			}
			wcout << tree[2].PlaceName[0];
			cout << "\t����ص㣺";
			wcout << tree[1].PlaceName[tmp] << endl;
			cout << "�����Σ����У���";
			out << tree[2].PlaceName[0];
			out << "\t����ص㣺";
			out << tree[1].PlaceName[tmp] << endl;
			out << "�����Σ����У���";
			Dijkstra(&G[1], tmp);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[1].PlaceName[tmp] << "-->";
			out << tree[1].PlaceName[tmp] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[1].PlaceName[Top(*line)] << "-->";
				out << tree[1].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[1].PlaceName[toflag % 100];
			out << tree[1].PlaceName[toflag % 100];
			Dijkstra(&G[1], &Campus[1], tmp);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
				out << "�ܺ�ʱ��Լ��" << ceil(mintime) << "����" << endl;
			}
		}
	}
	else if (fromflag / 100 == 3) {
		if (toflag / 100 == 4) {
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[3], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[3].PlaceName[fromflag % 100] << "-->";
			out << tree[3].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[3].PlaceName[Top(*line)] << "-->";
				out << tree[3].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[3].PlaceName[0];
			out << tree[3].PlaceName[0];
			Dijkstra(&G[3], &Campus[3], fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[1].GetTime(wtap, wfap) <= train[1].GetTime(wtts,wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[3].PlaceName[0];
				cout << "����ص㣺" << "��������" << endl;
				cout << "�����Σ��������������ڷɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ���";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[3].PlaceName[0];
				out << "����ص㣺" << "��������" << endl;
				out << "�����Σ��������������ڷɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ���";
			}
			else{
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[3].PlaceName[0];
				cout << "����ص㣺" << "������վ" << endl;
				cout << "�����Σ��������������ڻ𳵣�" << endl;
				cout<< "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ�վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[3].PlaceName[0];
				out << "����ص㣺" << "������վ" << endl;
				out << "�����Σ��������������ڻ𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ�վ";
			}
			cout << "����ص㣺";
			wcout<< tree[4].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[4].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[4], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0){
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[4].PlaceName[0] << "-->";
			out << tree[4].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[4].PlaceName[Top(*line)] << "-->";
				out << tree[4].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[4].PlaceName[toflag%100];
			out << tree[4].PlaceName[toflag % 100];
			Dijkstra(&G[4], &Campus[4], 0);
			if (Distance[toflag%100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag%100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag%100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
		else {
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[3], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[3].PlaceName[fromflag % 100] << "-->";
			out << tree[3].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[3].PlaceName[Top(*line)] << "-->";
				out << tree[3].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[3].PlaceName[0];
			out << tree[3].PlaceName[0];
			Dijkstra(&G[3], &Campus[3], fromflag % 100);
			if (Distance[0] < 1000){
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[0].GetTime(wtap, wfap) <= train[0].GetTime(wtts, wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[3].PlaceName[0];
				cout << "����ص㣺" << "̫ƽ����" << endl;
				cout << "�����Σ������������������ɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺̫ƽ����";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[3].PlaceName[0];
				out << "����ص㣺" << "̫ƽ����" << endl;
				out << "�����Σ������������������ɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺̫ƽ����";
			}
			else {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[3].PlaceName[0];
				cout << "����ص㣺" << "��������վ" << endl;
				cout << "�����Σ������������������𳵣�" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺��������վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[3].PlaceName[0];
				out << "����ص㣺" << "��������վ" << endl;
				out << "�����Σ������������������𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺��������վ";
			}
			cout << "����ص㣺";
			wcout << tree[toflag/100].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[toflag / 100].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[toflag/100], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[toflag/100].PlaceName[0] << "-->";
			out << tree[toflag / 100].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[toflag/100].PlaceName[Top(*line)] << "-->";
				out << tree[toflag / 100].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[toflag/100].PlaceName[toflag %100];
			out << tree[toflag / 100].PlaceName[toflag % 100];
			Dijkstra(&G[toflag/100], &Campus[toflag/100], 0);
			if (Distance[toflag %100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
	}
	else if (fromflag / 100 ==4) {
		if (toflag / 100 == 3){
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[4], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[4].PlaceName[fromflag % 100] << "-->";
			out << tree[4].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)){
				wcout << tree[4].PlaceName[Top(*line)] << "-->";
				out << tree[4].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[4].PlaceName[0];
			out << tree[4].PlaceName[0];
			Dijkstra(&G[4], &Campus[4], fromflag % 100);
			if (Distance[0] < 1000){
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[1].GetTime(wtap, wfap) <= train[1].GetTime(wtts, wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[4].PlaceName[0];
				cout << "����ص㣺" << "���ڻ���" << endl;
				cout << "�����Σ��������ڵ������ɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺��������";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[4].PlaceName[0];
				out << "����ص㣺" << "���ڻ���" << endl;
				out << "�����Σ��������ڵ������ɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺��������";
			}
			else {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[4].PlaceName[0];
				cout << "����ص㣺" << "���ڻ�վ" << endl;
				cout << "�����Σ��������ڵ������𳵣�" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺������վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[4].PlaceName[0];
				out << "����ص㣺" << "���ڻ�վ" << endl;
				out << "�����Σ��������ڵ������𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺������վ";
			}
			cout << "����ص㣺";
			wcout << tree[3].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[3].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[3], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[3].PlaceName[0] << "-->";
			out << tree[3].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[3].PlaceName[Top(*line)] << "-->";
				out << tree[3].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[3].PlaceName[toflag % 100];
			out << tree[3].PlaceName[toflag % 100];
			Dijkstra(&G[3], &Campus[3], 0);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
		else {
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[3], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[4].PlaceName[fromflag % 100] << "-->";
			out << tree[4].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[4].PlaceName[Top(*line)] << "-->";
				out << tree[4].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[4].PlaceName[0];
			out << tree[4].PlaceName[0];
			Dijkstra(&G[4], &Campus[4], fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[2].GetTime(wtap, wfap) <= train[2].GetTime(wtts, wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[4].PlaceName[0];
				cout << "����ص㣺" << "���ڻ���" << endl;
				cout << "�����Σ��������ڵ��������ɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺̫ƽ����";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[4].PlaceName[0];
				out << "����ص㣺" << "���ڻ���" << endl;
				out << "�����Σ��������ڵ��������ɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺̫ƽ����";
			}
			else {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[4].PlaceName[0];
				cout << "����ص㣺" << "���ڻ�վ" << endl;
				cout << "�����Σ��������ڵ��������𳵣�" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺��������վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[4].PlaceName[0];
				out << "����ص㣺" << "���ڻ�վ" << endl;
				out << "�����Σ��������ڵ��������𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺��������վ";
			}
			cout << "����ص㣺";
			wcout << tree[toflag / 100].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[toflag / 100].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[toflag/100], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[toflag / 100].PlaceName[0] << "-->";
			out << tree[toflag / 100].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[toflag / 100].PlaceName[Top(*line)] << "-->";
				out << tree[toflag / 100].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[toflag / 100].PlaceName[toflag % 100];
			out << tree[toflag / 100].PlaceName[toflag % 100];
		    Dijkstra(&G[toflag/100], &Campus[toflag/100], 0);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
	}
	else {
		if (toflag / 100 == 3) {
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[fromflag/100], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[fromflag/100].PlaceName[fromflag % 100] << "-->";
			out << tree[fromflag / 100].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[fromflag/100].PlaceName[Top(*line)] << "-->";
				out << tree[fromflag / 100].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[fromflag/100].PlaceName[0];
			out << tree[fromflag / 100].PlaceName[0];
			Dijkstra(&G[fromflag/100], &Campus[fromflag/100], fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[0].GetTime(wtap, wfap) <= train[0].GetTime(wtts, wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "����ص㣺" << "̫ƽ����" << endl;
				cout << "�����Σ������������������ɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺��������";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[fromflag / 100].PlaceName[0];
				out << "����ص㣺" << "̫ƽ����" << endl;
				out << "�����Σ������������������ɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺��������";
			}
			else {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "����ص㣺" << "��������վ" << endl;
				cout << "�����Σ������������������𳵣�" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺������վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[fromflag / 100].PlaceName[0];
				out << "����ص㣺" << "��������վ" << endl;
				out << "�����Σ������������������𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺������վ";
			}
			cout << "����ص㣺";
			wcout << tree[3].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[3].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[3], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[3].PlaceName[0] << "-->";
			out << tree[3].PlaceName[0] << "-->";
			while (!IsEmpty(*line)){
				wcout << tree[3].PlaceName[Top(*line)] << "-->";
				out << tree[3].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[3].PlaceName[toflag % 100];
			out << tree[3].PlaceName[toflag % 100];
			Dijkstra(&G[3], &Campus[3], 0);
			if (Distance[toflag % 100] < 1000){
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
		else {
			cout << "���·��Ϊ��" << endl;
			cout << "��һ�Σ����У���";
			out << "���·��Ϊ��" << endl;
			out << "��һ�Σ����У���";
			Dijkstra(&G[2], fromflag % 100);
			Stack *line = new Stack();
			int j = 0;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[fromflag/100].PlaceName[fromflag % 100] << "-->";
			out << tree[fromflag / 100].PlaceName[fromflag % 100] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[fromflag/100].PlaceName[Top(*line)] << "-->";
				out << tree[fromflag / 100].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[fromflag/100].PlaceName[0];
			out << tree[fromflag / 100].PlaceName[0];
			Dijkstra(&G[fromflag/100], &Campus[fromflag/100], fromflag % 100);
			if (Distance[0] < 1000) {
				cout << "\t·��Ϊ��" << Distance[0] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[2].GetTime(wtap, wfap) <= train[2].GetTime(wtts, wfap)) {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "����ص㣺" << "̫ƽ����" << endl;
				cout << "�����Σ����������������ڷɻ���" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ���";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[fromflag / 100].PlaceName[0];
				out << "����ص㣺" << "̫ƽ����" << endl;
				out << "�����Σ����������������ڷɻ���" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ���";
			}
			else {
				cout << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "����ص㣺" << "��������վ" << endl;
				cout << "�����Σ����������������ڻ𳵣�" << endl;
				cout << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ�վ";
				out << "�ڶ��Σ������ģ�" << "�˳��ص㣺";
				out << tree[fromflag / 100].PlaceName[0];
				out << "����ص㣺" << "��������վ" << endl;
				out << "�����Σ����������������ڻ𳵣�" << endl;
				out << "���ĶΣ������ģ�" << "�˳��ص㣺���ڻ�վ";
			}
			cout << "����ص㣺";
			wcout << tree[4].PlaceName[0] << endl;
			cout << "����Σ����У���";
			out << "����ص㣺";
			out << tree[4].PlaceName[0] << endl;
			out << "����Σ����У���";
			Dijkstra(&G[4], 0);
			line = new Stack();
			j = toflag % 100;
			while (Short[j] != -1 && Short[j] != 0) {
				j = Short[j];
				Push(line, j);
			}
			wcout << tree[4].PlaceName[0] << "-->";
			out << tree[4].PlaceName[0] << "-->";
			while (!IsEmpty(*line)) {
				wcout << tree[4].PlaceName[Top(*line)] << "-->";
				out << tree[4].PlaceName[Top(*line)] << "-->";
				Pop(line);
			}
			wcout << tree[4].PlaceName[toflag % 100];
			out << tree[4].PlaceName[toflag % 100];
			Dijkstra(&G[4], &Campus[4], 0);
			if (Distance[toflag % 100] < 1000) {
				cout << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
				out << "\t·��Ϊ��" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t·��Ϊ��" << distance << "KM" << endl;
				out << "\t·��Ϊ��" << distance << "KM" << endl;
			}
		}
	}
}
#endif;