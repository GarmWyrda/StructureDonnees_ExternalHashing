#pragma once
#include <exception>

class ValueNotFoundException: public std::exception
{
public:
	ValueNotFoundException();
	~ValueNotFoundException();
};

