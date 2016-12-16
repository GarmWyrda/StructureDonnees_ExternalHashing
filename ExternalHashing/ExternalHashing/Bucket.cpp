#include "stdafx.h"
#include "Bucket.h"
#include "ValueNotFoundException.h"
#include <algorithm>


Bucket::Bucket()
{
	this->values = vector<int>(maxSize, notInit);
}


Bucket::~Bucket()
{
}

vector<int> Bucket::getValues()
{
	return this->values;
}

bool Bucket::isFull()
{
	int i = 0;
	while (i < maxSize) {
		if (this->values[i] == -1) {
			return false;
		}
		i++;
	}
	return true;
}

void Bucket::addValue(int value)
{
	if (!this->isFull()) {
		int intToFind = -1;
		int Position = find_if(this->values.begin(), this->values.end(), [intToFind](const int integer) {return integer == intToFind; }) - this->values.begin();
		this->values[Position] = value;
		
	}
}

void Bucket::removeValue(int value)
{
	std::vector<int>::iterator position = std::find(this->values.begin(), this->values.end(), value);
	if (position != this->values.end()) { // == myVector.end() means the element was not found
		this->values.erase(position);
	}
	else {
		throw ValueNotFoundException();
		//Manage collisions, value could be in another bucket
	}
}

bool Bucket::search(int value)
{
	std::vector<int>::iterator position = std::find(this->values.begin(), this->values.end(), value);
	if (position != this->values.end()) { // == myVector.end() means the element was not found
		return true;
	}
	return false;
}

int Bucket::evaluateSignature()
{
	return 0;
}

ostream & operator<<(ostream & ostr, Bucket bucket)
{
	for (int value : bucket.values) {
		if (value == Bucket::notInit) {
			ostr << "VIDE" << " ";
		}
		else {
			ostr << value << " ";
		}
	}
	ostr << std::endl;
	return ostr;
}
