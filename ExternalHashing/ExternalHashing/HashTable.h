#pragma once
#include <vector>
#include "Bucket.h"
using namespace std;

#define moduloHashing 5

class HashTable
{
private:
	vector<Bucket> buckets;
	vector<int> separators;
public:
	HashTable();
	~HashTable();
	void addValue(int value);
	void addValueWithSeparator(int value);
	void removeValue(int value);
	int search(int value);
	void swapAndSort(int value, int position, int bucketNumber);
	int signature(int value);
	friend ostream& operator<<(ostream& ostr, HashTable& hashtable);
};

