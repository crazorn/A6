#pragma once
#include <string>
#include <vector>
#include "cdate.h"
#include "caddress.h"
#include "caccount.h"
#include "MethodeLib.h"
using namespace std;

class CAccount;
class CCustomer {
	long id;
	string name;
	CDate birthday;
	CAddress address;
	vector<CAccount*> accountList;
public:
	CCustomer(long Id, string Name, CDate Birthday, CAddress Address, vector<CAccount*> AccountList = {}): id(Id), name(Name), birthday(Birthday), address(Address){
		if (!AccountList.empty())
			this->accountList = AccountList;
	}
	~CCustomer() {
		cout << "Kunde " << name << " wird vernichtet.\n";
	}

	static CCustomer* load(stringstream& stream);
	void addAccount(CAccount* account);
	string Get_Name() { return name; }
	long Get_ID() { return id; }
	vector<CAccount*> Get_Accountlist() { return accountList; }
	void print();
	
};
