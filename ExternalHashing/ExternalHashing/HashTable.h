#pragma once
#include <vector>
#include "Bucket.h"
using namespace std;

#define moduloHashing 5

class HashTable
{
private:
	vector<Bucket> buckets;
public:
	HashTable();
	~HashTable();
	void addValue(int value);
	void removeValue(int value);
	int search(int value);
	friend ostream& operator<<(ostream& ostr, HashTable& hashtable);
};

