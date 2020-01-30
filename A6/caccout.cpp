#include "caccount.h"

CAccount::CAccount(CBank* Bank, string IBAN, CCustomer* Customer, CMoney Balance) {
	Bank->addAccount(this);
	this->bank = Bank;
	this->IBAN = IBAN;
	this->balance = Balance;
	Set_Customer(Customer);
}

CAccount::CAccount(string IBAN)
{
	bank = nullptr;
	this->IBAN = IBAN;
	customer = nullptr;
	balance = NULL;
}

void CAccount::load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList)
{
	string cont;
	string tmp_iban;
	string customer_id;
	string bank_bic;
	CCustomer* tmp_customer = nullptr;
	CBank* tmp_bank = nullptr;
	stringstream balancestream;
	while (stream >> cont) {
		
		//found IBAN
		if (cont.find("<IBAN>") != string::npos) {
			//find rest of iban
			tmp_iban = cont;
			while (cont.find("</IBAN>") == string::npos) {
				stream >> cont;
				tmp_iban += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_iban, "IBAN");
		}

		//found Customer
		if (cont.find("<Customer>") != string::npos) {
			//find rest of iban
			customer_id = cont;
			while (cont.find("</Customer>") == string::npos) {
				stream >> cont;
				customer_id += " " + cont;
			}
			MethodeLib::remove_xmltags(customer_id, "Customer");
			for (auto customer : CustomerList) {
				if (customer->Get_ID() == stoi(customer_id)) {
					tmp_customer = customer;
				}
			}
			if (!tmp_customer) {
				cout << "###########===== Customer-ID" << customer_id << " was not found! =====############" << endl;
				return;
			}
		}

		//found Customer
		if (cont.find("<Bank>") != string::npos) {
			//find rest of iban
			bank_bic = cont;
			while (cont.find("</Bank>") == string::npos) {
				stream >> cont;
				bank_bic += " " + cont;
			}
			MethodeLib::remove_xmltags(bank_bic, "Bank");
			for (auto bank : BankList) {
				if (bank->Get_BIC() == bank_bic) {
					tmp_bank = bank;
				}
			}
			if (!tmp_bank) {
				cout << "###########===== Bank" << bank_bic << " was not found! =====############" << endl;
				return;
			}
		}

		//found Balance
		if (cont == "<Balance>") {
			while (cont != "</Balance>")
			{
				stream >> cont;
				//the blank is just as seperator between strings
				balancestream << cont << " ";

			}
		}
	}
	CAccount* acc = new CAccount(tmp_bank, tmp_iban, tmp_customer,CMoney::load(balancestream));

	return;
}

void CAccount::print() {
	cout << left << setw(12) << "Kunde: " << customer->Get_Name() << " (Kd-Nr. " << customer->Get_ID() << ")\n";
	cout << left << setw(12) << "IBAN/BIC: ";
	Print_IBAN();
	cout << " / " << bank->Get_BIC();
	cout << "\n";
	cout << left << setw(12) << "Kontostand: ";
	balance.print();
}

void CAccount::Print_IBAN()
{
	cout << toString();
}

string CAccount::toString() {
	string tmp_iban = IBAN;
	for (int i = 1; i < 6; i++)
	{
		if (i == 1) {
			tmp_iban.insert(4 * i, " ");
		}
		else
		{
			tmp_iban.insert(4 * i + (i - 1), " ");
		}
	}
	return tmp_iban;
}


void CAccount::Set_Customer(CCustomer* Customer) {
	Customer->addAccount(this);
	this->customer = Customer;
}

void CAccount::write(ostream& stream){
	stream << left << setw(12) << "Kunde: " << customer->Get_Name() << " (Kd-Nr. " << customer->Get_ID() << ")\n";
	stream << left << setw(12) << "IBAN/BIC: ";
	stream << Get_IBAN();
	stream << " / " << bank->Get_BIC();
	stream << "\n";
	stream << left << setw(12) << "Kontostand: ";
	stream << balance.toString();
}

std::ostream& operator<<(std::ostream& stream, CAccount* acc) {
	acc->write(stream);
	return stream;
}