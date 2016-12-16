#include "stdafx.h"
#include "Bucket.h"
#include "ValueNotFoundException.h"


Bucket::Bucket()
{
	this->values = vector<int>();
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
	return this->values.size() >= maxSize;
}

void Bucket::addValue(int value)
{
	if (this->values.size() < maxSize) {
		this->values.push_back(value);
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

int Bucket::search(int value)
{
	return 0;
}

int Bucket::evaluateSeparator()
{
	return 0;
}
