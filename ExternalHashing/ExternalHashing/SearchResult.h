#pragma once
class SearchResult
{
private:
	int bucketNumber;
	int nbAccess;
public:
	SearchResult();
	SearchResult(int bucketNumber, int nbAccess);
	~SearchResult();
	int getBucketNumber();
	int getNbAccess();
};

