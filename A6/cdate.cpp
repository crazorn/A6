#include "cdate.h"
#include <sstream>

CDate CDate::load(std::stringstream& stream)
{
	int tmp_day(0);
	int tmp_month(0);
	int tmp_year(0);
	std::string cont("");

	while (stream >> cont)
	{
		//found Day
		if (cont.find("<Day>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Day");
			tmp_day = stoi(cont); 
		}

		//found Month
		if (cont.find("<Month>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Month");
			tmp_month = stoi(cont); 
		}

		//found Year
		if (cont.find("<Year>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Year");
			tmp_year = stoi(cont);
		}
	}
	return CDate(tmp_day, tmp_month, tmp_year);
}
