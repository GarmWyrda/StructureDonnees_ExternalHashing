#pragma once
#include <vector>
#include "Bucket.h"
#include "SearchResult.h"
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
	int addValue(int value);
	int addValueWithSeparator(int value);
	int removeValue(int value);
	//int removeValueWithSeparator(int value);
	SearchResult search(int value);
	SearchResult searchWithSeparator(int value);
	void swapAndSort(int value, int position, int bucketNumber, int& nbAccess);
	int signature(int value);
	friend ostream& operator<<(ostream& ostr, HashTable& hashtable);
};

