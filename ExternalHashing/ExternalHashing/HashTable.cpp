#include "stdafx.h"
#include "HashTable.h"
#include "FullTableException.h"
#include "ValueNotFoundException.h"


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
	int bucketNumber = value % moduloHashing;
	this->buckets[bucketNumber].removeValue(value);
	//Manage collisions, value could be in another bucket
}

int HashTable::search(int value)
{
	int bucketNumber = value % moduloHashing;
	int i = 0;
	while (i < moduloHashing) {
		if (this->buckets[bucketNumber].search(value)) {
			return bucketNumber;
		}
		i++;
		bucketNumber++;
	}
	throw ValueNotFoundException();
	return 0;
}

ostream & operator<<(ostream & ostr, HashTable & hashtable)
{
	int i = 0;
	for (Bucket& bucket : hashtable.buckets) {
		ostr << "-------Bucket " << i++ << "----------";
		ostr << bucket << std::endl << "-----------------" ;
	}
	return ostr;
}
