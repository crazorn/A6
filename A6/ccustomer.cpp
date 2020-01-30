#include "ccustomer.h"


void CCustomer::print()
{
	cout << name << " (Kd-Nr. " << id << ")\n";
	address.print();
	cout << "\ngeboren am: ";
	this->birthday.print();
	cout << "\nKonten:\n";
	for (auto account : accountList)
	{
		cout << account << endl;
	}
}

CCustomer* CCustomer::load(stringstream& stream)
{
	string cont;
	long tmp_id(0);
	string tmp_name("");
	stringstream birthdaystream;
	stringstream addressstream;

	while (stream >> cont)
	{
		//found ID
		if (cont.find("<ID>") != string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "ID");
			tmp_id = stol(cont);
			//ID can contain leading zero! 
		}
		//found Name
		if (cont.find("<Name>") != string::npos) {
			//find rest of name (surname is seperated)
			tmp_name = cont;
			while (cont.find("</Name>") == string::npos) {
				stream >> cont;
				tmp_name += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_name, "Name");
		}
		//found Birthday
		if (cont == "<Birthday>") {
			while (cont != "</Birthday>")
			{
				stream >> cont;
				//the blank is just as seperator between strings
				birthdaystream << cont << " ";

			}
		}
		//found Address
		if (cont == "<Address>") {
			while (cont != "</Address>")
			{
				stream >> cont;
				//the blank is just as seperator between strings
				addressstream << cont << " ";

			}
		}
	}
	return new CCustomer(tmp_id,tmp_name, CDate::load(birthdaystream), CAddress::load(addressstream));
}

void CCustomer::addAccount(CAccount* account) {
	accountList.push_back(account);
}