#pragma once
#include<vector>
#include"cbank.h"
#include"ccustomer.h"
#include"ctransactionbatch.h"
#include"ctransaktion.h"

using namespace std;

class CBankManager
{
private:
	vector<CBank*> BankList;
	vector<CCustomer*> CustomerList;
	vector<CTransactionBatch*> TransactionsList;
	
public:
	CBankManager(string file);
	~CBankManager();
	void printCustomerList();
	void printBankList();
	void printTransactions();
	friend CBankManager& operator+=(CBankManager& man, CTransactionBatch* batch);
};

