#include "stdafx.h"
#include "HashTable.h"
#include "FullTableException.h"


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
	int i = 0;
	while (this->buckets[bucketNumber].isFull() && i < moduloHashing) {
		bucketNumber = (bucketNumber + 1) % moduloHashing;
		i++;
	}
	if (i = moduloHashing) {
		throw FullTableException();
	}
	this->buckets[bucketNumber].addValue(value);
}

void HashTable::removeValue(int value)
{
}

int HashTable::search(int value)
{
	return 0;
}

