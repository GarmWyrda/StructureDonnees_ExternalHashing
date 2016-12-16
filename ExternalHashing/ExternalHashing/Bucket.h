#pragma once
#include <vector>
#include <ostream>
using namespace std;

#define maxSize 5


class Bucket
{
private:
	vector<int> values;
public:
	const static int notInit = -1;
	Bucket();
	~Bucket();
	vector<int> getValues();
	bool isFull();
	void addValue(int value);
	void removeValue(int value);
	bool search(int value);
	friend ostream& operator<<(ostream& ostr, Bucket bucket);
	int evaluateSignature();
};

