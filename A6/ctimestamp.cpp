#include "ctimestamp.h"
#include <iomanip>

bool CTimestamp::fulldate = true;


void CTimestamp::print()
{
	std::string tmp_weekday;
	switch (weekday)
	{
	case CWeekday::Monday:
		tmp_weekday = "Mo";
		break;
	case CWeekday::Tuesday:
		tmp_weekday = "Di";
		break;
	case CWeekday::Wednesday:
		tmp_weekday = "Mi";
		break;
	case CWeekday::Thursday:
		tmp_weekday = "Do";
		break;
	case CWeekday::Friday:
		tmp_weekday = "Fr";
		break;
	case CWeekday::Saturday:
		tmp_weekday = "Sa";
		break;
	case CWeekday::Sunday:
		tmp_weekday = "So";
		break;
	default:
		tmp_weekday = "Unknown";
		break;
	}
	std::cout << std::setw(4)<< tmp_weekday;
	std::cout << " ";
	CDate::print();
	std::cout << " ";
	CTime::print();
}

std::ostream& operator<<(std::ostream& stream, CTimestamp& time) {
	std::string tmp_weekday;
	switch (time.weekday)
	{
	case CWeekday::Monday:
		tmp_weekday = "Mo";
		break;
	case CWeekday::Tuesday:
		tmp_weekday = "Di";
		break;
	case CWeekday::Wednesday:
		tmp_weekday = "Mi";
		break;
	case CWeekday::Thursday:
		tmp_weekday = "Do";
		break;
	case CWeekday::Friday:
		tmp_weekday = "Fr";
		break;
	case CWeekday::Saturday:
		tmp_weekday = "Sa";
		break;
	case CWeekday::Sunday:
		tmp_weekday = "So";
		break;
	default:
		tmp_weekday = "Unknown";
		break;
	}
	stream << std::setw(4) << tmp_weekday << "," ;
	stream << " " << time.getRefDate() << ";  ";
	
	if (time.fulldate) {
		stream << time.getRefTime();
	}
	
	return stream;
}


