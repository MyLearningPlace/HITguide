#pragma once
#ifndef train_h
#define train_h
#include "initall.h"
using namespace std;
typedef struct time3 {
	int firsthour;
	int lasthour;
	int bethour;
} Times;
class Train {
public:
	Times time;
	int times;
	double prize;
public:
	double GetTime(double hour1,double hour2);
};
double Train::GetTime(double hour1,double hour2) {
	SYSTEMTIME ST;
	GetLocalTime(&ST);
	int times = (this->time.lasthour - this->time.firsthour) / this->time.bethour + 1;
	int timein[Max];
	for (int i = 0; i < times; i++){
		timein[i] = this->time.firsthour + this->time.bethour*i;
	}
	for (int i = 0; i < times; i++){
		if (timein[i] >= hour1 + ST.wHour + ST.wMinute / 60.0){
			return (timein[i] - ST.wHour - ST.wMinute / 60.0 + hour2+this->times)/this->prize;
		}
	}
	return INF;
}
#endif;