#include "stdafx.h"
#include "Bucket.h"


Bucket::Bucket()
{
	this->values = vector<int>(maxSize);
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
}

int Bucket::search(int value)
{
	return 0;
}

int Bucket::evaluateSeparator()
{
	return 0;
}
