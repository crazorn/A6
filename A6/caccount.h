#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "cmoney.h"
#include "ccustomer.h"
#include "cbank.h"
using namespace std;
class CCustomer;
class CBank;

class CAccount {
	string IBAN;
	CMoney balance;
	CCustomer* customer;
	CBank* bank;
public:
	CAccount(CBank* Bank, string IBAN, CCustomer* Customer, CMoney Balance);
	CAccount(string IBAN);
	virtual ~CAccount() { 
		cout << left << setw(25) << "CAccount:";
		cout << "Konto: (";
		Print_IBAN();
		cout << ") vernichtet!\n";
	}
	static void load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList);
	virtual void print();
	void Print_IBAN();
	string Get_IBAN() { return IBAN; }
	string toString();
	void Set_IBAN(string IBAN) { this->IBAN = IBAN; }
	CMoney Get_Balance() { return balance; }
	void Set_Balance(CMoney Balance) { this->balance = Balance; }
	CCustomer* Get_Customer() { return customer; }
	void Set_Customer(CCustomer* Customer);
	
	virtual void write(ostream& str);

	friend std::ostream& operator<<(std::ostream& stream, CAccount* acc);
};
