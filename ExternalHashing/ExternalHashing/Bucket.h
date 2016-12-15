#pragma once
#include <vector>

using namespace std;

class Bucket
{
private:
	vector<int> values;
public:
	Bucket();
	~Bucket();
	void addValue(int value);
	void removeValue(int value);
	int search(int value);
	int evaluateSeparator();
};

