#pragma once
#include "ctimestamp.h"
#include "ctransaktion.h"
#include <vector>
#include <algorithm>
class CTransactionBatch
{
	CTimestamp Timestamp;
	vector<CTransaktion*> TransactionList;
public:
	void print();
	vector<CTransaktion*> Get_TransactionList() { return TransactionList; }
	void Remove_Transaction_FromList(CTransaktion* element);
	CTransactionBatch(string file);
	~CTransactionBatch();
};

