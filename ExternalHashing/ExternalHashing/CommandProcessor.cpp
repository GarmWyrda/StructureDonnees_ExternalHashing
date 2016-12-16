#include "stdafx.h"
#include "CommandProcessor.h"


CommandProcessor::CommandProcessor(HashTable* hashTable, bool& shouldExit) : shouldExit(shouldExit)
{
	this->hashTable = hashTable;
}

CommandProcessor::~CommandProcessor()
{
}

void CommandProcessor::printHelp()
{
	std::cout << "---------------Help----------------" << std::endl;
	std::cout << "Voici les commandes disponibles" << std::endl;
	std::cout << "inserer : Inserer une valeur" << std::endl;
	std::cout << "supprimer : Supprimer une valeur" << std::endl;
	std::cout << "rechercher : Recherche une valeur et renvoie le bucket dans lequel elle se trouve" << std::endl;
	std::cout << "afficher : affiche la table de hachage" << std::endl;
	std::cout << "aide,? : Affiche la liste des commandes" << std::endl;
	std::cout << "quitter : Quitte l'application" << std::endl;
}

void CommandProcessor::printHashTable()
{
	std::cout << "Affichage de la table" << std::endl << *hashTable << std::endl;
}

void CommandProcessor::processCommand(string command)
{
	if (command == "aide" || command == "?") {
		printHelp();
	}
	else if(command == "quitter"){
		quit();
	}
	else if (command == "inserer") {
		string input;
		std::cout << "Valeur a inserer ? ";
		getline(std::cin, input);
		int value = stoi(input);
		hashTable->addValue(value);
	}
	else if (command == "supprimer") {
		string input;
		std::cout << "Valeur a supprimer ? ";
		getline(std::cin, input);
		int value = stoi(input);
		hashTable->removeValue(value);
	}
	else if (command == "afficher") {
		printHashTable();
	}
	else if (command == "rechercher") {
		string input;
		std::cout << "Valeur a rechercher ? ";
		getline(std::cin, input);
		int value = stoi(input);
		int bucketIndex = hashTable->search(value);
		std::cout << "Valeur trouvee dans le Bucket " << bucketIndex << std::endl;
	}
	else {
		std::cout << "Commande invalide. Usage : " << std::endl;
		printHelp();
	}
}

void CommandProcessor::quit()
{
	this->shouldExit = true;
}

