#include "stdafx.h"
#include "HashTable.h"


HashTable::HashTable()
{
	this->buckets = vector<Bucket>(moduloHashing);
}


HashTable::~HashTable()
{
}

void HashTable::addValue(int value)
{
	int bucketNumber = value % moduloHashing;
	this->buckets[bucketNumber].addValue(value);
}

void HashTable::removeValue(int value)
{
}

int HashTable::search(int value)
{
	return 0;
}

