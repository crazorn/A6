#pragma once
#include "csavingsaccount.h"
#include "ccurrentaccount.h"
class CFixedDepositAccount :
	public CSavingsAccount, public CCurrentAccount 
{

public:
	void print();
	CFixedDepositAccount(CBank* Bank, string IBAN, CCustomer* Customer, CMoney Balance, double Intrestrate, CMoney* Disposit)
		:CAccount(Bank, IBAN, Customer, Balance), CSavingsAccount(Bank, IBAN, Customer, Balance, Intrestrate), CCurrentAccount(Bank, IBAN, Customer, Balance, Disposit) {}
	virtual ~CFixedDepositAccount() {
		cout << left << setw(25) << "CFixedDepositAccount";
		cout << "Konto: (";
		CAccount::Print_IBAN();
		cout << ") vernichtet!\n";
	}
	virtual void write(ostream& stream);
	friend std::ostream& operator<<(std::ostream& stream, CFixedDepositAccount& acc);

	static void load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList);

	
};

