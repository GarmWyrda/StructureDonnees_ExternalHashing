#include "stdafx.h"
#include "HashTable.h"
#include "FullTableException.h"
#include "ValueNotFoundException.h"


HashTable::HashTable()
{
	this->buckets = vector<Bucket>(moduloHashing);
	this->separators = vector<int>();
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

void HashTable::addValueWithSeparator(int value)
{
	int bucketNumber = value % moduloHashing;
	while (signature(value) > this->separators[bucketNumber]) {
		bucketNumber++;
	}
	int i = 0;
	while (value > this->buckets[bucketNumber].getValues()[i]) {
		i++;
	}
	swapAndSort(value, i, bucketNumber);
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

void HashTable::swapAndSort(int value, int position, int bucketNumber)
{
	int tmpValue = this->buckets[bucketNumber].getValues()[position];
	this->buckets[bucketNumber].getValues()[position] = value;

	position++;
	if (position > maxSize) {
		swapAndSort(tmpValue, 0, bucketNumber + 1);
	}
	else if (this->buckets[bucketNumber].getValues()[position] == -1) { //test à revoir
		this->buckets[bucketNumber].getValues()[position] = tmpValue;
	}
	else {
		swapAndSort(tmpValue, position, bucketNumber);
	}
}

int HashTable::signature(int value)
{
	return value;
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
