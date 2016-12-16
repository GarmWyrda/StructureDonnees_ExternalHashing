#pragma once
#include <string>
#include <iostream>
#include "HashTable.h"
using std::string;
class CommandProcessor
{
private:
	bool& shouldExit;
	HashTable* hashTable;
public:
	CommandProcessor(HashTable* hashTable,bool& shouldExit);
	virtual ~CommandProcessor();
	void printHelp();
	void processCommand(string command);
	void quit();
};

