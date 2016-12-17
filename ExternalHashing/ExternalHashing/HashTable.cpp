#include "stdafx.h"
#include "HashTable.h"
#include "FullTableException.h"
#include "ValueNotFoundException.h"
#include <iostream>

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
	
	while (this->separators[bucketNumber] != -1 && signature(value) >= this->separators[bucketNumber]) {
		bucketNumber++;
	}
	int i = 0;
	int j = 0;
	nbAccess++;
	while (j < moduloHashing && i < moduloHashing && this->buckets[bucketNumber].getValues()[i] != -1 && value > this->buckets[bucketNumber].getValues()[i]) {
		i++;
		if (i == moduloHashing) {
			bucketNumber = (bucketNumber + 1) % moduloHashing;
			j++;
			i = 0;
		}
	}
	if (j == moduloHashing) {
		throw FullTableException();
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

/*
int HashTable::removeValueWithSeparator(int value)
{
	int nbAccess = 0;
	int bucketNumber = value % moduloHashing;
	while (this->separators[bucketNumber] != -1 && signature(value) >= this->separators[bucketNumber]) {
		bucketNumber++;
	}

	int i = 0;
	nbAccess++;
	while (i < maxSize) {
		if (this->buckets[bucketNumber].getValues()[i] == value) {
			this->buckets[bucketNumber].setValue(-1, i);
			
		}
		i++;
	}
	throw ValueNotFoundException();
	return 0;
}
*/

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
		bucketNumber = (bucketNumber +1) % moduloHashing;
	}
	throw ValueNotFoundException();
	return SearchResult(nbAccess,-1);
}

SearchResult HashTable::searchWithSeparator(int value)
{
	int nbAccess = 0;
	int bucketNumber = value % moduloHashing;
	while (this->separators[bucketNumber] != -1 && signature(value) >= this->separators[bucketNumber]) {
		bucketNumber++;
	}
	nbAccess++;
	if (this->buckets[bucketNumber].search(value)) {
		return SearchResult(bucketNumber, nbAccess);
	}
	else {
		throw ValueNotFoundException();
	}
}

void HashTable::swapAndSort(int value, int position, int bucketNumber, int& nbAccess)
{
	int tmpValue = this->buckets[bucketNumber].getValues()[position];
	if (tmpValue != -1 && tmpValue < value) {
		if (position < maxSize-1) {
			swapAndSort(value, position + 1, bucketNumber, nbAccess);
			return;
		}
		else {
			swapAndSort(value, 0, bucketNumber + 1, nbAccess);
			return;
		}
	}
	this->buckets[bucketNumber].setValue(value, position);
	nbAccess++;
	//this->buckets[bucketNumber].getValues()[position] = value;
	//std::cout << "value? " << value << "dans bucket? " << this->buckets[bucketNumber].getValues()[position] << std::endl;

	if (tmpValue == -1) {
		return;
	}
	position++;
	if (position >= maxSize) {
		std::cout << "new separator : " << tmpValue << std::endl;
		this->separators[bucketNumber] = tmpValue;
		int newBucket = (bucketNumber + 1) % moduloHashing;
		swapAndSort(tmpValue, 0, newBucket, nbAccess);
	}
	else if (this->buckets[bucketNumber].getValues()[position] == -1) {
		//this->buckets[bucketNumber].getValues()[position] = tmpValue;
		this->buckets[bucketNumber].setValue(tmpValue, position);
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
