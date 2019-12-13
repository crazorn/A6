#include <iostream>

using namespace std;

#include "ctimestamp.h"
#include "ctransactionbatch.h"
#include "cbankmanager.h"

void printNow()
{
	CTimestamp Now;

	cout << "Aktueller Zeitstempel: " << printDateTime << Now << endl << endl;
}

int main()
{
	printNow();

	CBankManager BankManager("daten.xml");

	BankManager += new CTransactionBatch("transactions.xml");
	cout << endl;

	BankManager.printTransactions(); // gibt alle Stapel mit allen Transaktionen aus
	cout << endl;

	BankManager.printCustomerList(); // Übersicht der Kunden mit kompletter Kontenausgabe
	cout << endl;

	BankManager.printBankList(); // Übersicht der Konten mit geänderten Kontoständen
	cout << endl;

	printNow();

	return 0;
}