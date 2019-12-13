#include "cbank.h"


CBank::~CBank()
{
	{
		for (auto account : accountlist) {
			delete account;
		}
		cout << "Bank " << name << " wird vernichtet.\n";
	}
}

CBank* CBank::load(stringstream& stream)
{
	string cont;
	string tmp_bic("");
	string tmp_name("");

	while (stream >> cont) {
		
		//found BIC
		if (cont.find("<BIC>") != string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "BIC");
			tmp_bic = cont;
		}
		
		//found Name
		if (cont.find("<Name>") != string::npos) {
			//find rest of street (number is seperated)
			tmp_name = cont;
			while (cont.find("</Name>") == string::npos) {
				stream >> cont;
				tmp_name += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_name, "Name");
		}
	}
	
	
	return new CBank(tmp_name, tmp_bic);
}



void CBank::print() {
	cout << name << "\n";
	cout << "BLZ " << BIC << "\n";
	cout << "Anzahl der Konten: " << accountlist.size() << "\n";
	cout << "Kontoliste:\n";
	

	long long IBAN_wd = 30;
	long long Kundenn_wd = 15;
	long long Anz_wd = 12;
	long long Kontost_wd = 12;
	cout << left << setw(IBAN_wd) << "IBAN";
	cout << " | ";
	cout << left << setw(Kundenn_wd) << "Kundenname";
	cout << " | ";
	cout << left << setw(Anz_wd) << "Anz. Buchungen";
	cout << " | ";
	cout << left << setw(Kontost_wd) << "Kontostand";
	cout << "\n";
	cout << string(IBAN_wd + 1, '-') << "|" << string(Kundenn_wd + 2, '-') << "|" << string(Anz_wd + 4, '-') << "|" << string(Kontost_wd + 8, '-');
	cout << "\n";
	for (auto account : accountlist) {
		cout << left << setw(IBAN_wd + long long(1)) << account->toString();
		cout << "|";
		cout << left << setw(Kundenn_wd + long long(2)) << account->Get_Customer()->Get_Name();
		cout << "|";
		cout << right << setw(Anz_wd + long long(4)) << "0"; //Placeholder until Transaction implementaition
		cout << "|";
		cout << right << setw(Kontost_wd + long long(8)) <<  account->Get_Balance().toString();
		cout << "\n";
	}

}

void CBank::addAccount(CAccount* account) {
	if (account != nullptr) {
		accountlist.push_back(account);
	}
	else {
		cout << "AccountPointer not valid!\n";
	}
}