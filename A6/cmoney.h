#pragma once
#include "MethodeLib.h"
#include <string>
#include <iostream>
#include <sstream> 
using namespace std;
class CMoney {	
	double amount;
	string currency;
public:
	CMoney() {
		amount = 0;
		currency = "EUR";
	}
	CMoney(double Amount, string Currenzy = "EUR"): amount(Amount), currency(Currenzy) {}
	~CMoney(){}
	void print() {
		cout << toString();
	}
	string toString() {
		stringstream buffer;
		buffer.precision(2);
		buffer << fixed << amount << " " << currency;
		return buffer.str();
	}
	static CMoney load(stringstream& stream);
	static CMoney* load_ptr(stringstream& stream);
	double Get_Amount() { return amount; }
	void Set_Amount(double Amount) { this->amount = Amount; }
	string Get_Currency() { return currency; }
	void Set_Currency(string Currency) { this->currency = Currency; }
	friend CMoney operator+(CMoney a, CMoney b) {
		return CMoney(a.amount + b.amount, a.currency);
	}
	friend CMoney operator-(CMoney a, CMoney b) {
		return CMoney(a.amount - b.amount, a.currency);
	}
};