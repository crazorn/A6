#pragma once
#include "ctime.h"
#include "cdate.h"
#include "cweekday.h"
#include <time.h>
#include <iomanip>
#include <iostream>


class CTimestamp :
	public CTime, public CDate
{
	CWeekday weekday;
public:
	
	static bool fulldate;

	CTimestamp(int day, int month, int year,int Hour, int Minute, int Second = 0):CDate(year, month, day),CTime(Hour, Minute, Second) {
		std::tm time_in = { Second, Minute, Hour, day, month - 1, year };
		time_t time_tmp = mktime(&time_in);
		std::tm local;
		localtime_s(&local, &time_tmp);
		weekday = CWeekday(local.tm_wday);
	}
	CTimestamp(): CDate(), CTime() {
		time_t rawtime;
		time(&rawtime);
		struct tm local;
		localtime_s(&local, &rawtime);
		//nochmal debuggen
		weekday = CWeekday(local.tm_wday);
	}
	void print();
	~CTimestamp() {}

	friend std::ostream& operator<<(std::ostream& stream, CTimestamp& time);
};



inline std::ostream& printDateTime(std::ostream& stream) {
	CTimestamp::fulldate = true;
	return stream;
}

inline std::ostream& printOnlyDate(std::ostream& stream) {
	CTimestamp::fulldate = false;
	return stream;
}

