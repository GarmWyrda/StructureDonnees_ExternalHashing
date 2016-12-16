#include "stdafx.h"
#include "Bucket.h"
#include "ValueNotFoundException.h"


Bucket::Bucket()
{
	this->values = vector<int>(maxSize, this->notInit);
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
	if (this->values.size() < maxSize) {
		std::vector<int>::iterator position = std::find(this->values.begin(), this->values.end(), -1);
		if (position != this->values.end()) { 
			this->values.insert(position, value);
		}
		else {
			//should definitely not happen, it was tested before
		}
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
