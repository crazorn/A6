#include "ccurrentaccount.h"

void CCurrentAccount::print() {
	CAccount::print();
	cout << "\n";
	cout << left << setw(12) << "Dispo:";
	disposit->print();
}

void CCurrentAccount::load(stringstream& stream, vector<CBank*> BankList, vector<CCustomer*> CustomerList)
{
	string cont;
	string tmp_iban;
	string customer_id;
	string bank_bic;
	CCustomer* tmp_customer = nullptr;
	CBank* tmp_bank = nullptr;
	stringstream balancestream;
	stringstream dispostream;
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

		//found Dispo
		if (cont == "<Dispo>") {
			while (cont != "</Dispo>")
			{
				stream >> cont;
				//the blank is just as seperator between strings
				dispostream << cont << " ";

			}
		}
	}
	//Error with account delete!!!
	CCurrentAccount* acc = new CCurrentAccount(tmp_bank, tmp_iban, tmp_customer, CMoney::load(balancestream), CMoney::load_ptr(dispostream));
	return;
}

void CCurrentAccount::write(ostream& stream) {
	CAccount::write(stream);
	stream << "\n";
	stream << left << setw(12) << "Dispo:";
	stream << disposit->toString();
}

std::ostream& operator<<(std::ostream& stream, CCurrentAccount& acc) {
	acc.write(stream);
	return stream;
}

