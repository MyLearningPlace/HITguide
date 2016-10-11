#pragma once
#ifndef hrbxq_h
#define hrbxq_h
#include "initall.h"
#include "leastline.h"
#include <cmath>

/**********************全局变量区********************/
Map *Campus = new Map[5];
MTGraph *G = new MTGraph[5];
Place from, to;
int fromflag, toflag;
int next2[Max];
/***********************程序区********************/
void Input() {
	InitMap(&Campus[0]);
	InitMap2(&Campus[1]);
	InitMap3(&Campus[2]);
	InitMap4(&Campus[3]);
	InitMap5(&Campus[4]);
	do {
		cout << "请输入搜索起点：";
		wcin >> from;
		out << "搜索起点为：" << from << endl;
		fromflag = Locate(from,next2);
	} while (fromflag < 0);
	do {
		cout << "请输入搜索终点：";
		wcin >> to;
		out << "搜索终点为：" << to<< endl;
		toflag = Locate(to,next2);
	} while (toflag < 0);
}
void HrbXq() {
	 if (fromflag / 100 == toflag / 100) {
		 Dijkstra(&G[fromflag/100], &Campus[fromflag/100], fromflag % 100);
		 if (Distance[toflag % 100] < 1000){
			cout << "两地距离为：" << Distance[toflag % 100] << "M" << "（";
			out << "两地距离为：" << Distance[toflag % 100] << "M" <<endl;
			Read(Distance[toflag % 100]);
			cout << "米）" << endl;
		}
		else {
			double distance = Distance[toflag % 100] / 1000.0;
			cout << "两地距离为：" << distance << "KM" << "（";
			out << "两地距离为：" << distance << "KM" << endl;
			Read((Distance[toflag % 100] / 1000));
			cout << "点";
			ReadPoint(Distance[toflag % 100]);
			cout << "千米）" << endl;
		}
		cout << "最短路线为：" << endl;
		out << "最短路线为：" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[tmp] << "M" << endl;
			}
			else {
				double distance = Distance[tmp] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime == INF) cout << "第二段：建议打的!" << "乘车地点：";
			else if (bus[number].No == 0) cout << "第二段：建议乘坐校车！" << "乘车地点：";
			else cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			wcout << tree[0].PlaceName[tmp];
			cout << "\t到达地点：";
			wcout << tree[1].PlaceName[tmp2] << endl;
			cout << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime != INF) cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[tmp2] << "M" << endl;
				out << "\t路程为：" << Distance[tmp2] << "M" << endl;

			}
			else {
				double distance = Distance[tmp2] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "第二段：建议打的！" << "乘车地点：";
				out << "第二段：建议打的！" << "乘车地点：";
			}
			else if (bus[number].No == 0) {
				cout << "第二段：建议乘坐校车！" << "乘车地点：";
				out << "第二段：建议乘坐校车！" << "乘车地点：";
			}
			else {
				cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
				out << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			}
			wcout << tree[1].PlaceName[tmp2];
			cout << "到达地点：";
			wcout << tree[0].PlaceName[tmp] << endl;
			cout << "第三段（步行）：";
			out << tree[1].PlaceName[tmp2];
			out << "到达地点：";
			out << tree[0].PlaceName[tmp] << endl;
			out << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
				out << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[9] << "M" << endl;
				out << "\t路程为：" << Distance[9] << "M" << endl;
			}
			else {
				double distance = Distance[9] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (number == 0) {
				cout << "第二段：建议步行!" << "起点：";
				out << "第二段：建议步行!" << "起点：";
			}
			else {
				cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
				out << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			}
			wcout << tree[0].PlaceName[9];
			cout << "\t到达地点：";
			wcout << tree[2].PlaceName[0] << endl;
			cout << "第三段（步行）：";
			out << tree[0].PlaceName[9];
			out << "\t到达地点：";
			out << tree[2].PlaceName[0] << endl;
			out << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
			out << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
			}
			if (number == 0) {
				cout << "第二段：建议步行!" << "起点：";
				out << "第二段：建议步行!" << "起点：";
			}
			else {
				cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
				out << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			}
			wcout << tree[2].PlaceName[0];
			cout << "\t到达地点：";
			wcout << tree[0].PlaceName[9] << endl;
			cout << "第三段（步行）：";
			out << tree[2].PlaceName[0];
			out << "\t到达地点：";
			out << tree[0].PlaceName[9] << endl;
			out << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
			out << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[tmp] << "M" << endl;
				out << "\t路程为：" << Distance[tmp] << "M" << endl;
			}
			else {
				double distance = Distance[tmp] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "第二段：建议打的!" << "乘车起点：";
				out << "第二段：建议打的!" << "乘车起点：";
			}
			else {
				cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
				out << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			}
			wcout << tree[1].PlaceName[tmp];
			cout << "\t到达地点：";
			wcout << tree[2].PlaceName[0] << endl;
			cout << "第三段（步行）：";
			out << tree[1].PlaceName[tmp];
			out << "\t到达地点：";
			out << tree[2].PlaceName[0] << endl;
			out << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
				out << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
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
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime == INF) {
				cout << "第二段：建议打的!" << "乘车起点：";
				out << "第二段：建议打的!" << "乘车起点：";
			}
			else {
				cout << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
				out << "第二段：建议乘坐" << bus[number].No << "路车！" << "乘车地点：";
			}
			wcout << tree[2].PlaceName[0];
			cout << "\t到达地点：";
			wcout << tree[1].PlaceName[tmp] << endl;
			cout << "第三段（步行）：";
			out << tree[2].PlaceName[0];
			out << "\t到达地点：";
			out << tree[1].PlaceName[tmp] << endl;
			out << "第三段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			if (mintime != INF) {
				cout << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
				out << "总耗时大约：" << ceil(mintime) << "分钟" << endl;
			}
		}
	}
	else if (fromflag / 100 == 3) {
		if (toflag / 100 == 4) {
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[1].GetTime(wtap, wfap) <= train[1].GetTime(wtts,wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[3].PlaceName[0];
				cout << "到达地点：" << "威海机场" << endl;
				cout << "第三段：乘坐威海到深圳飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：深圳机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[3].PlaceName[0];
				out << "到达地点：" << "威海机场" << endl;
				out << "第三段：乘坐威海到深圳飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：深圳机场";
			}
			else{
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[3].PlaceName[0];
				cout << "到达地点：" << "威海火车站" << endl;
				cout << "第三段：乘坐威海到深圳火车！" << endl;
				cout<< "第四段：建议打的！" << "乘车地点：深圳火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[3].PlaceName[0];
				out << "到达地点：" << "威海火车站" << endl;
				out << "第三段：乘坐威海到深圳火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：深圳火车站";
			}
			cout << "到达地点：";
			wcout<< tree[4].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[4].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag%100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag%100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
		else {
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[0].GetTime(wtap, wfap) <= train[0].GetTime(wtts, wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[3].PlaceName[0];
				cout << "到达地点：" << "太平机场" << endl;
				cout << "第三段：乘坐威海到哈尔滨飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：太平机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[3].PlaceName[0];
				out << "到达地点：" << "太平机场" << endl;
				out << "第三段：乘坐威海到哈尔滨飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：太平机场";
			}
			else {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[3].PlaceName[0];
				cout << "到达地点：" << "哈尔滨火车站" << endl;
				cout << "第三段：乘坐威海到哈尔滨火车！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：哈尔滨火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[3].PlaceName[0];
				out << "到达地点：" << "哈尔滨火车站" << endl;
				out << "第三段：乘坐威海到哈尔滨火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：哈尔滨火车站";
			}
			cout << "到达地点：";
			wcout << tree[toflag/100].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[toflag / 100].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
	}
	else if (fromflag / 100 ==4) {
		if (toflag / 100 == 3){
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[1].GetTime(wtap, wfap) <= train[1].GetTime(wtts, wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[4].PlaceName[0];
				cout << "到达地点：" << "深圳机场" << endl;
				cout << "第三段：乘坐深圳到威海飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：威海机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[4].PlaceName[0];
				out << "到达地点：" << "深圳机场" << endl;
				out << "第三段：乘坐深圳到威海飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：威海机场";
			}
			else {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[4].PlaceName[0];
				cout << "到达地点：" << "深圳火车站" << endl;
				cout << "第三段：乘坐深圳到威海火车！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：威海火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[4].PlaceName[0];
				out << "到达地点：" << "深圳火车站" << endl;
				out << "第三段：乘坐深圳到威海火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：威海火车站";
			}
			cout << "到达地点：";
			wcout << tree[3].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[3].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
		else {
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[2].GetTime(wtap, wfap) <= train[2].GetTime(wtts, wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[4].PlaceName[0];
				cout << "到达地点：" << "深圳机场" << endl;
				cout << "第三段：乘坐深圳到哈尔滨飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：太平机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[4].PlaceName[0];
				out << "到达地点：" << "深圳机场" << endl;
				out << "第三段：乘坐深圳到哈尔滨飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：太平机场";
			}
			else {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[4].PlaceName[0];
				cout << "到达地点：" << "深圳火车站" << endl;
				cout << "第三段：乘坐深圳到哈尔滨火车！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：哈尔滨火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[4].PlaceName[0];
				out << "到达地点：" << "深圳火车站" << endl;
				out << "第三段：乘坐深圳到哈尔滨火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：哈尔滨火车站";
			}
			cout << "到达地点：";
			wcout << tree[toflag / 100].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[toflag / 100].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
	}
	else {
		if (toflag / 100 == 3) {
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[0].GetTime(wtap, wfap) <= train[0].GetTime(wtts, wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "到达地点：" << "太平机场" << endl;
				cout << "第三段：乘坐哈尔滨到威海飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：威海机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[fromflag / 100].PlaceName[0];
				out << "到达地点：" << "太平机场" << endl;
				out << "第三段：乘坐哈尔滨到威海飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：威海机场";
			}
			else {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "到达地点：" << "哈尔滨火车站" << endl;
				cout << "第三段：乘坐哈尔滨到威海火车！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：威海火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[fromflag / 100].PlaceName[0];
				out << "到达地点：" << "哈尔滨火车站" << endl;
				out << "第三段：乘坐哈尔滨到威海火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：威海火车站";
			}
			cout << "到达地点：";
			wcout << tree[3].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[3].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
		else {
			cout << "最短路线为：" << endl;
			cout << "第一段（步行）：";
			out << "最短路线为：" << endl;
			out << "第一段（步行）：";
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
				cout << "\t路程为：" << Distance[0] << "M" << endl;
				out << "\t路程为：" << Distance[0] << "M" << endl;
			}
			else {
				double distance = Distance[0] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
			double wtts = 1, wtap = 2, wfts = 1, wfap = 2;
			if (plane[2].GetTime(wtap, wfap) <= train[2].GetTime(wtts, wfap)) {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "到达地点：" << "太平机场" << endl;
				cout << "第三段：乘坐哈尔滨到深圳飞机！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：深圳机场";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[fromflag / 100].PlaceName[0];
				out << "到达地点：" << "太平机场" << endl;
				out << "第三段：乘坐哈尔滨到深圳飞机！" << endl;
				out << "第四段：建议打的！" << "乘车地点：深圳机场";
			}
			else {
				cout << "第二段：建议打的！" << "乘车地点：";
				wcout << tree[fromflag/100].PlaceName[0];
				cout << "到达地点：" << "哈尔滨火车站" << endl;
				cout << "第三段：乘坐哈尔滨到深圳火车！" << endl;
				cout << "第四段：建议打的！" << "乘车地点：深圳火车站";
				out << "第二段：建议打的！" << "乘车地点：";
				out << tree[fromflag / 100].PlaceName[0];
				out << "到达地点：" << "哈尔滨火车站" << endl;
				out << "第三段：乘坐哈尔滨到深圳火车！" << endl;
				out << "第四段：建议打的！" << "乘车地点：深圳火车站";
			}
			cout << "到达地点：";
			wcout << tree[4].PlaceName[0] << endl;
			cout << "第五段（步行）：";
			out << "到达地点：";
			out << tree[4].PlaceName[0] << endl;
			out << "第五段（步行）：";
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
				cout << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
				out << "\t路程为：" << Distance[toflag % 100] << "M" << endl;
			}
			else {
				double distance = Distance[toflag % 100] / 1000.0;
				cout << "\t路程为：" << distance << "KM" << endl;
				out << "\t路程为：" << distance << "KM" << endl;
			}
		}
	}
}
#endif;