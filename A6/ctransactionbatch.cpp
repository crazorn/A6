#include "ctransactionbatch.h"
#include "ctransaktion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

CTransactionBatch::CTransactionBatch(string file)
{
	ifstream ifs(file);
	if (ifs) {
		cout << "Datei wurde erfolgreich geoeffnet und wird jetzt eingelesen..." << endl;
	}
	else {
		cout << "Error!" << endl;
		return;
	}
	//read fstream in stringstream 
	string cont;
	while (ifs >> cont) {
		//parsing	
		if (cont == "<TransactionBatch>") {
			while (cont != "</TransactionBatch>")
			{
				//continue reading
				ifs >> cont;
				//found Customer
				if (cont == "<Transaction>") {
					stringstream transactionstream;
					while (cont != "</Transaction>")
					{
						ifs >> cont;
						//the blank is just as seperator between strings
						transactionstream << cont << " ";

					}
					//create new object
					TransactionList.push_back(CTransaktion::load(transactionstream));
				}
			}

		}
	}
	//set time for transaktion

	Timestamp = CTimestamp();
	cout << "Datei wurde eingelesen." << endl;
}


void CTransactionBatch::Remove_Transaction_FromList(CTransaktion* element)
{
	TransactionList.erase(remove(TransactionList.begin(), TransactionList.end(), element), TransactionList.end());
	cout << "Transaktion mit ID:" << element->Get_ID() << " war ungueltig und wurde geloescht!!!!" << endl;
}

void CTransactionBatch::print() {
	cout << "Tranaktionen (";
	Timestamp.print();
	cout << "):" << endl << endl;
	for (auto transa : TransactionList) {
		transa->print();
	}
}
CTransactionBatch::~CTransactionBatch()
{
	for (auto trptr : TransactionList) {
		delete trptr;
	}
}
