#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "caccount.h"

using namespace std;
class CAccount;

class CBank
{
	string name;
	string BIC;
	vector<CAccount*> accountlist;
public:
	CBank(string Name, string BIC, vector<CAccount*> Accountlist = {}) :name(Name), BIC(BIC) {
		if (!Accountlist.empty()) {
			this->accountlist = Accountlist;
		}
	}
	~CBank();

	static CBank* load(stringstream& stream);
	string Get_BIC() { return BIC; }
	vector<CAccount*> Get_AccountList() { return accountlist; }
	void print();
	void addAccount(CAccount*);
};

