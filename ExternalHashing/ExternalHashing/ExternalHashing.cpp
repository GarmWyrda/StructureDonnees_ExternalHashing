// ExternalHashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
#include "CommandProcessor.h"
#include <cstdlib>
#include <ctime>
#define MAX_VALUE 200

using std::stoi;
int main()
{
	//Creating Hashtable and filling it with random values
	string input;
	std::srand(std::time(0)); // use current time as seed for random generator
	bool shouldExit = false;
	std::cout << "Combien d'entrees voulez vous ajouter a la table ?" << std::endl;
	getline(std::cin, input);
	std::cout << "Generation de la table" << std::endl;
	int n = stoi(input);
	HashTable table1 = HashTable();
	for (int i = 0; i < n; i++) {
		int random_variable = std::rand();
		//table1.addValue(random_variable % MAX_VALUE);
		table1.addValueWithSeparator(random_variable % MAX_VALUE);
	}
	CommandProcessor cmdProcessor = CommandProcessor(&table1,shouldExit);
	cmdProcessor.processCommand("afficher");
	cmdProcessor.printHelp();
	std::cout << std::endl;
	while (!shouldExit) {
		std::cout << "Commande : ";
		getline(std::cin, input);
		cmdProcessor.processCommand(input);
		std::cout << std::endl;
	}
    return 0;
}

