#pragma once
#include <string>
#include "cliste.h"
#include <sstream>
#include "caccount.h"

using namespace std;
class CAccount;

class CBank
{
	string name;
	string BIC;
	Liste<CAccount*> accountlist;
public:
	CBank(string Name, string BIC, Liste<CAccount*> Accountlist = {}) :name(Name), BIC(BIC) {
		if (!Accountlist.empty()) {
			this->accountlist = Accountlist;
		}
	}
	~CBank();

	static CBank* load(stringstream& stream);
	string Get_BIC() { return BIC; }
	Liste<CAccount*> Get_AccountList() { return accountlist; }
	void print();
	void addAccount(CAccount*);
};

