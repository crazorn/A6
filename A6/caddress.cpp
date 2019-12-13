#include "caddress.h"
#include "MethodeLib.h"

CAddress CAddress::load(stringstream& stream)
{
	string tmp_street("");
	string tmp_postcode("");
	string tmp_town("");
	string cont("");

	while (stream >> cont)
	{
		//found Street
		if (cont.find("<Street>") != string::npos) {
			//find rest of street (number is seperated)
			tmp_street = cont;
			while (cont.find("</Street>") == string::npos) {
				stream >> cont;
				tmp_street += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_street, "Street");
		}

		//found Postcode
		if (cont.find("<Postcode>") != string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Postcode");
			tmp_postcode = cont;
		}

		//found City
		if (cont.find("<Town>") != string::npos) {
			//find rest of city-name (just in case...)
			tmp_town = cont;
			while (cont.find("</Town>") == string::npos) {
				stream >> cont;
				tmp_town += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_town, "Town");
		}

	}
	return CAddress(tmp_street, tmp_postcode, tmp_town);
}
