#pragma once
#include "caccount.h"
#include "cmoney.h"
#include <string>

class CTransaktion
{
	long ID;
	CAccount* Account;
	CAccount* ContraAccount;
	CMoney Amount;
	CMoney TransaktionFee;
	std::string ReasonForPayment;
public:
	CTransaktion(long id, CAccount* account, CAccount* contraaccount, CMoney amount, CMoney transaktionfee, std::string reasonforpayment) : 
		ID(id), Account(account), ContraAccount(contraaccount), Amount(amount), TransaktionFee(transaktionfee), ReasonForPayment(reasonforpayment) {}

	void print();
	void Set_Account(CAccount* acc) { Account = acc; }
	long Get_ID() { return ID; }
	void Set_ContraAccount(CAccount* acc) { ContraAccount = acc; }
	void Reassigne_Account(CAccount* acc) {
		delete Account;
		Account = acc;
	}
	void Reassigne_ContraAccount(CAccount* acc) {
		delete ContraAccount;
		ContraAccount = acc;
	}
	void execute();
	CAccount* Get_Account() { return Account; }
	CAccount* Get_ContraAccount() { return ContraAccount; }

	static CTransaktion* load(stringstream& stream);
};

