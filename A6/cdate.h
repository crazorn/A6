#pragma once
#include <time.h>
#include <iostream>
#include "MethodeLib.h"

class CDate
{
	int Day;
	int Month;
	int Year;
public:
	CDate(){
		time_t rawtime;
		time(&rawtime);
		struct tm local;
		localtime_s(&local, &rawtime);
		Day = local.tm_mday;
		Month = local.tm_mon + 1;
		Year = local.tm_year +1900;
	}
	CDate(int day, int month, int year): Day(day), Month(month), Year(year){}
	~CDate(){}

	CDate& getRefDate() { return *this; }
	static CDate load(std::stringstream& stream);
	void print() {
		printf("%02d.%02d.%04d", Day, Month, Year);
	}
	friend std::ostream& operator<<(std::ostream& stream, CDate& date) {
		stream << date.Day << "." << date.Month << "." << date.Year;
		return stream;
	}
};
