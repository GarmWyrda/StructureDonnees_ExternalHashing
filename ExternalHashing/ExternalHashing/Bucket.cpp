#include "stdafx.h"
#include "Bucket.h"


Bucket::Bucket()
{
	this->values = vector<int>(5);
}


Bucket::~Bucket()
{
}

void Bucket::addValue(int value)
{
	if(this->values.size)
	this->values.push_back(value);
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
