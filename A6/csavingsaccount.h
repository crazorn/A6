#pragma once
#include "caccount.h"
class CSavingsAccount :
	virtual public CAccount
{
	double intrestrate;
public:
	CSavingsAccount(CBank* Bank, string IBAN, CCustomer* Customer, CMoney Balance, double Intrestrate)
		: CAccount(Bank, IBAN, Customer, Balance), intrestrate(Intrestrate) {};
	void print();
	double GetIntrestrate() { return intrestrate; }
	virtual ~CSavingsAccount() {
		cout << left << setw(25) << "CSavingsAccount:";
		cout << "Konto: (";
		CAccount::Print_IBAN();
		cout << ") vernichtet!\n";
	}
	static void load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList);

	virtual void write(ostream& stream);

	friend std::ostream& operator<<(std::ostream& stream, CSavingsAccount& acc);
};

