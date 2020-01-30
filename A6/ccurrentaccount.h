#pragma once
#include "caccount.h"
class CCurrentAccount :
	virtual public CAccount
{
	CMoney* disposit;
public:
	void print();
	CCurrentAccount(CBank* Bank, string IBAN, CCustomer* Customer, CMoney Balance, CMoney* Disposit) 
		: CAccount(Bank, IBAN, Customer, Balance), disposit(Disposit) {};
	virtual ~CCurrentAccount() {
		delete disposit;
		cout << left << setw(25) << "CCurrentAccount:";
		cout << "Konto: (";
		CAccount::Print_IBAN();
		cout << ") vernichtet!\n";
	}
	static void load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList);
	virtual void write(ostream& stream);
	};

