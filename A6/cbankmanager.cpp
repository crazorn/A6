#include "cbankmanager.h"
#include<string>
#include<ios>
#include<iostream>
#include<fstream>
#include "ccurrentaccount.h"
#include "csavingsaccount.h"
#include "cfixeddepositaccount.h"
CBankManager::CBankManager(string file) {
	cout << "Datei wurde erfolgreich geoeffnet und wird jetzt eingelesen..." << endl;
	ifstream ifs(file);
	if (ifs) {
		cout << "Datei wurde eingelesen." << endl;
	}
	else {
		cout << "Error!" << endl;
		return;
	}

	//read fstream in stringstream 
	string cont;
	while (ifs >> cont) {
		//parsing	
		if (cont == "<Data>") {
			while (cont != "</Data>")
			{
				//continue reading
				ifs >> cont;

				//found Customer
				if (cont == "<Customer>") {
					stringstream customerstream;
					while (cont != "</Customer>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						customerstream << cont << " ";

					}
					//create new object
					CustomerList.push_back(CCustomer::load(customerstream));
				}

				//found Bank
				if (cont == "<Bank>") {
					stringstream bankstream;
					while (cont != "</Bank>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						bankstream << cont << " ";

					}
					//create new object
					BankList.push_back(CBank::load(bankstream));
				}

				//found Account
				if (cont == "<Account>") {
					stringstream accountstream;
					while (cont != "</Account>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						accountstream << cont << " ";

					}
					//create new object
					CAccount::load(accountstream, BankList, CustomerList);
				}

				//found CurrentAccount
				if (cont == "<CurrentAccount>") {
					stringstream accountstream;
					while (cont != "</CurrentAccount>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						accountstream << cont << " ";

					}
					//create new object
					CCurrentAccount::load(accountstream, BankList, CustomerList);
				}

				//found SavingsAccount
				if (cont == "<SavingsAccount>") {
					stringstream accountstream;
					while (cont != "</SavingsAccount>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						accountstream << cont << " ";

					}
					//create new object
					CSavingsAccount::load(accountstream, BankList, CustomerList);
				}

				//found FixedDepositAccount
				if (cont == "<FixedDepositAccount>") {
					stringstream accountstream;
					while (cont != "</FixedDepositAccount>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						accountstream << cont << " ";

					}
					//create new object
					CFixedDepositAccount::load(accountstream, BankList, CustomerList);
				}
			}
		}
	}

	//parsing
	

	ifs.close();
}
CBankManager::~CBankManager() {
	for (auto cptr : CustomerList) {
		delete cptr;
	}
	for (auto bptr : BankList) {
		delete bptr;
	}
	for (auto btchptr : TransactionsList) {
		delete btchptr;
	}

}

void CBankManager::printCustomerList() {
	for (auto customer : CustomerList) {
		customer->print();
		cout << "\n" << endl;
	}
}

void CBankManager::printBankList() {
	for (auto bank : BankList) {
		bank->print();
		cout << endl;
	}
}

void CBankManager::printTransactions()
{
	if (TransactionsList.empty()) {
		cout << "keine Transaktionen vorhanden" << endl;
		return;
	}
	for (auto batch : TransactionsList) {
		batch->print();
	}
}


CBankManager& operator+=(CBankManager& man, CTransactionBatch* batch) {
	//more sure

	for (auto trans : batch->Get_TransactionList()) {
		//match account
		for (auto bank : man.BankList) {
			for (auto account : bank->Get_AccountList()) {
				if (trans->Get_Account()->Get_IBAN() == account->Get_IBAN()) {
					trans->Reassigne_Account(account);
				}
				if (trans->Get_ContraAccount()->Get_IBAN() == account->Get_IBAN()) {
					trans->Reassigne_ContraAccount(account);
				}
			}
		}
		if (trans->Get_Account()->Get_Customer() == nullptr || trans->Get_ContraAccount()->Get_Customer() == nullptr) {
			//invalid transaction found
			cout << "Fehler! Account wurde nicht gefunden!" << endl;
			batch->Remove_Transaction_FromList(trans);
			continue;
		}
		//execute transaction
		trans->execute();
	}
	man.TransactionsList.push_back(batch);
	return man;
}

