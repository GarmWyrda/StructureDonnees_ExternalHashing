#include "stdafx.h"
#include "HashTable.h"
#include "FullTableException.h"
#include "ValueNotFoundException.h"


HashTable::HashTable()
{
	this->buckets = vector<Bucket>(moduloHashing);
	this->separators = vector<int>(moduloHashing,-1);
}


HashTable::~HashTable()
{
}

int HashTable::addValue(int value)
{
	int nbAccess = 0;
	int bucketNumber = value % moduloHashing;
	int i = 0;
	nbAccess++;
	while (this->buckets[bucketNumber].isFull() && i < moduloHashing) {
		nbAccess++;
		bucketNumber = (bucketNumber + 1) % moduloHashing;
		i++;
	}
	if (i == moduloHashing) {
		throw FullTableException();
	}
	this->buckets[bucketNumber].addValue(value);
	return nbAccess;
}

int HashTable::addValueWithSeparator(int value)
{
	int nbAccess = 0;
	int bucketNumber = value % moduloHashing;
	while (signature(value) > this->separators[bucketNumber]) {
		bucketNumber++;
	}
	int i = 0;
	vector<int> values = this->buckets[bucketNumber].getValues();
	while (value > values[i]) {
		i++;
	}
	swapAndSort(value, i, bucketNumber, nbAccess);
	return nbAccess;
}

int HashTable::removeValue(int value)
{
	int nbAccess = 0;
	int bucketNumber = value % moduloHashing;
	int i = 0;
	bool found = false;
	nbAccess++;
	vector<int> bucket = this->buckets[bucketNumber].getValues();
	while (!found && i < moduloHashing) {
		std::vector<int>::iterator position = std::find(bucket.begin(), bucket.end(), value);
		if (position == bucket.end()) { // == myVector.end() means the element was not found
			bucketNumber = (bucketNumber + 1) % moduloHashing;
			bucket = this->buckets[bucketNumber].getValues();
			nbAccess++;
		}
		else {
			found = true;
		}
		i++;
	}
	this->buckets[bucketNumber].removeValue(value);
	return nbAccess;
	/*
	int bucketNumber = value % moduloHashing;
	this->buckets[bucketNumber].removeValue(value);
	//Manage collisions, value could be in another bucket
	*/
}

SearchResult HashTable::search(int value)
{
	int bucketNumber = value % moduloHashing;
	int i = 0;
	int nbAccess = 0;
	while (i < moduloHashing) {
		nbAccess++;
		if (this->buckets[bucketNumber].search(value)) {
			return SearchResult(bucketNumber,nbAccess);
		}
		i++;
		bucketNumber++;
	}
	throw ValueNotFoundException();
	return SearchResult(nbAccess,-1);
}

void HashTable::swapAndSort(int value, int position, int bucketNumber, int& nbAccess)
{
	int tmpValue = this->buckets[bucketNumber].getValues()[position];
	this->buckets[bucketNumber].getValues()[position] = value;
	nbAccess++;
	position++;
	if (position > maxSize) {
		swapAndSort(tmpValue, 0, bucketNumber + 1, nbAccess);
	}
	else if (this->buckets[bucketNumber].getValues()[position] == -1) {
		this->buckets[bucketNumber].getValues()[position] = tmpValue;
	}
	else {
		swapAndSort(tmpValue, position, bucketNumber, nbAccess);
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
		ostr << "-------Bucket " << i << "----------" << std::endl;
		ostr << bucket;
		if (hashtable.separators[i] != -1) {
			ostr << "Separateur : " << hashtable.separators[i] << std::endl;
		}
		else {
			ostr << "Separateur : Pas encore de separateur" << std::endl;
		}
		i++;
	}
	return ostr;
}
