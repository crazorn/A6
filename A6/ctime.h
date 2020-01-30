#pragma once
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

class CTime {
	int hour;
	int minute;
	int second;
public:
	CTime() {
		time_t rawtime;
		time(&rawtime);
		struct tm local;
		localtime_s(&local, &rawtime);
		hour = local.tm_hour;
		minute = local.tm_min;
		second = local.tm_sec;

	}
	CTime(int Hour, int Minute, int Second = 0): hour(Hour), minute(Minute), second(Second) {}
	void print() {
		printf("%02d:%02d:%02d", hour, minute, second);
	}

	CTime& getRefTime() { return *this; }

	friend std::ostream& operator<<(std::ostream& stream, CTime& time) {
		char fill = stream.fill('0');
		stream <<  setw(2)<<time.hour << flush << ":" << setw(2)<< time.minute << flush << ":" << setw(2)<< time.second << flush;
		stream.fill(fill);
		return stream;
	}
	~CTime(){}
};
