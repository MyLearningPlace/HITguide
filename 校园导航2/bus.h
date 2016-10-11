#pragma once
#ifndef bus_h
#define bus_h
#include "match.h"
#include <windows.h>
using namespace std;
typedef struct time{
	int firsthour;
	int firstmin;
	int lasthour;
	int lastmin;
	int betmin;
} TimeTable;
typedef struct zone {
	int head;
	int tail;
} Station;
/***********************³ÌÐòÇø********************/
class Bus{
public:
	int No;
	TimeTable time;
	Station locate;
	int min;
	Bus(){

	}
	~Bus(){

	}
public:
	double GetTime(double walk,double run);
};
double Bus::GetTime(double walk,double run){
	SYSTEMTIME ST;
	double min;
	GetLocalTime(&ST);
	int times = (int)(this->time.lasthour - this->time.firsthour + (this->time.lastmin - this->time.firstmin) / 60.0)/(this->time.betmin/60.0);
	double time[Max];
	for (int i = 0; i < times; i++){
		time[i] = this->time.firsthour + (this->time.firstmin + i*this->time.betmin)/60.0;
	}
	double now = ST.wHour + (ST.wMinute+walk)/60.0;
	for (int i = 0; i < times; i++){
		if (time[i] >= now){
			min = time[i] - now;
			return min+walk+run+this->time.betmin;
		}
	}
	return INF;
}

#endif