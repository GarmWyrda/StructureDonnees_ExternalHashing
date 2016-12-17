#include "stdafx.h"
#include "SearchResult.h"


SearchResult::SearchResult()
{
	nbAccess = 0;
	bucketNumber = -1;
}

SearchResult::SearchResult(int bucketNumber, int nbAccess) : bucketNumber(bucketNumber), nbAccess(nbAccess)
{
}



SearchResult::~SearchResult()
{
}

int SearchResult::getBucketNumber()
{
	return bucketNumber;
}

int SearchResult::getNbAccess()
{
	return nbAccess;
}
