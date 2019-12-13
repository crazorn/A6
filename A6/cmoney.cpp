#include "cmoney.h"


CMoney CMoney::load(stringstream& stream)
{
	string cont;
	string tmp_curr;
	double tmp_amount = 0;
	while (stream >> cont)
	{
		//found amount
		if (cont.find("<Amount>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Amount");
			tmp_amount = stod(cont);
		}

		//found currency
		if (cont.find("<Currency>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Currency");
			tmp_curr = cont;
		}
	}

	return CMoney(tmp_amount, tmp_curr);
}

CMoney* CMoney::load_ptr(stringstream& stream)
{
	string cont;
	string tmp_curr;
	double tmp_amount = 0;
	while (stream >> cont)
	{
		//found Day
		if (cont.find("<Amount>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Amount");
			tmp_amount = stod(cont);
		}

		//found Month
		if (cont.find("<Currency>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Currency");
			tmp_curr = cont;
		}
	}

	return new CMoney(tmp_amount, tmp_curr);
}
