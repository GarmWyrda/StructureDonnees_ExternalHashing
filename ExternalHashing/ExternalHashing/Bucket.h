#pragma once
#include <vector>

using namespace std;

#define maxSize 5

class Bucket
{
private:
	vector<int> values;
	const static int notInit = -1;
public:
	Bucket();
	~Bucket();
	vector<int> getValues();
	bool isFull();
	void addValue(int value);
	void removeValue(int value);
	bool search(int value);
	int evaluateSignature();
};

