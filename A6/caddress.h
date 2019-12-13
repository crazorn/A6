#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class CAddress {
	string street;
	string postcode;
	string town;
public:
	CAddress(string Street, string Postcode, string Town):street(Street), postcode(Postcode),town(Town) {}
	~CAddress(){}
	void print() {
		cout << street << "\n" << postcode <<" "<< town;
	}
	static CAddress load(stringstream& stream);
	string Get_Street() { return street; }
	void Set_Street(string Street) { this->street = Street; }
	string Get_Postcode() { return postcode; }
	void Set_Postcode(string Postcode) { this->postcode = Postcode; }
	string Get_Town() { return town; }
	void Set_TownU(string Town) { this->town = Town; }
};