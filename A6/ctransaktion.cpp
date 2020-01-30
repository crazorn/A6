#include "ctransaktion.h"

void CTransaktion::print()
{
	cout << "Buchung ueber: " << Amount.toString() << endl;
	cout << "--- von ---" << endl;
	cout << Account;
	cout << endl<< "--- an ---" << endl;
	cout << ContraAccount;
	cout << endl << "--- Verwendungszweck: " << ReasonForPayment << " ---" << endl << endl;
}

void CTransaktion::execute()
{
	//Remove from Base
	ContraAccount->Set_Balance(ContraAccount->Get_Balance() - Amount - TransaktionFee);
	//Add to receiver
	Account->Set_Balance(Account->Get_Balance() + Amount);
}

CTransaktion* CTransaktion::load(stringstream& stream)
{
	string cont;
	long tmp_id(0);
	string account_iban;
	CAccount* tmp_account = nullptr;
	CAccount* tmp_contraaccount = nullptr;
	double tmp_amount(0);
	string tmp_reason;

	while (stream >> cont)
	{
		//found ID
		if (cont.find("<ID>") != string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "ID");
			tmp_id = stol(cont);
			//ID can contain leading zero! 
		}

		//found IBAN-Account
		if (cont.find("<IBAN-Account>") != string::npos) {
			//find rest of iban
			account_iban = cont;
			while (cont.find("</IBAN-Account>") == string::npos) {
				stream >> cont;
				account_iban += " " + cont;
			}
			MethodeLib::remove_xmltags(account_iban, "IBAN-Account");
			tmp_contraaccount = new CAccount(account_iban);
		}

		//found IBAN-ContraAccount
		if (cont.find("<IBAN-ContraAccount>") != string::npos) {
			//find rest of iban
			account_iban = cont;
			while (cont.find("</IBAN-ContraAccount>") == string::npos) {
				stream >> cont;
				account_iban += " " + cont;
			}
			MethodeLib::remove_xmltags(account_iban, "IBAN-ContraAccount");
			tmp_account = new CAccount(account_iban);
		}

		//found Amount
		if (cont.find("<Amount>") != std::string::npos) {
			//exctract Data
			MethodeLib::remove_xmltags(cont, "Amount");
			tmp_amount = stod(cont);
		}

		//found ReasonForPayment
		if (cont.find("<ReasonForPayment>") != string::npos) {
			//find rest of reason
			tmp_reason = cont;
			while (cont.find("</ReasonForPayment>") == string::npos) {
				stream >> cont;
				tmp_reason += " " + cont;
			}
			MethodeLib::remove_xmltags(tmp_reason, "ReasonForPayment");
		}
	}
		
	return new CTransaktion(tmp_id, tmp_account, tmp_contraaccount, CMoney(tmp_amount),/*Transactionfee placeholder*/CMoney(0), tmp_reason);
}
