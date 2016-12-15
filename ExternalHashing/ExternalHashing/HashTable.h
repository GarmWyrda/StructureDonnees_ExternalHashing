#pragma once
#include <vector>
#include "Bucket.h"
using namespace std;

class HashTable
{
private:
	vector<Bucket> buckets;
public:
	HashTable();
	~HashTable();
};

