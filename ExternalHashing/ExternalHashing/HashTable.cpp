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

void HashTable::addValue(int value)
{
	int bucketNumber = value % moduloHashing;
	int i = 0;
	while (this->buckets[bucketNumber].isFull() && i < moduloHashing) {
		bucketNumber = (bucketNumber + 1) % moduloHashing;
		i++;
	}
	if (i == moduloHashing) {
		throw FullTableException();
	}
	this->buckets[bucketNumber].addValue(value);
}

void HashTable::addValueWithSeparator(int value)
{
	int bucketNumber = value % moduloHashing;
	//std::cout << bucketNumber << std::endl;
	//std::cout << this->separators[bucketNumber] << std::endl;
	while (this->separators[bucketNumber] != -1 && signature(value) > this->separators[bucketNumber]) {
		bucketNumber++;
	}
	int i = 0;
	while (i < moduloHashing && this->buckets[bucketNumber].getValues()[i] != -1 && value > this->buckets[bucketNumber].getValues()[i]) {
		i++;
		if (i == moduloHashing) {
			bucketNumber++;
			i = 0;
		}
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
	return -1;
}

void HashTable::swapAndSort(int value, int position, int bucketNumber)
{
	int tmpValue = this->buckets[bucketNumber].getValues()[position];
	this->buckets[bucketNumber].setValue(value, position);
	//this->buckets[bucketNumber].getValues()[position] = value;
	//std::cout << "value? " << value << "dans bucket? " << this->buckets[bucketNumber].getValues()[position] << std::endl;

	if (tmpValue == -1) {
		return;
	}
	position++;
	if (position >= maxSize) {
		std::cout << "new separator : " << tmpValue << std::endl;
		this->separators[bucketNumber] = tmpValue;
		swapAndSort(tmpValue, 0, bucketNumber + 1);
	}
	else if (this->buckets[bucketNumber].getValues()[position] == -1) {
		//this->buckets[bucketNumber].getValues()[position] = tmpValue;
		this->buckets[bucketNumber].setValue(tmpValue, position);
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
