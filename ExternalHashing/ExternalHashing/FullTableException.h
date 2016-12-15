#pragma once
#include <exception>

class FullTableException : public std::exception
{
public:
	FullTableException();
	~FullTableException();
};

