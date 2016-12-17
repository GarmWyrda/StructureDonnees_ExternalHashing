#include "stdafx.h"
#include "CommandProcessor.h"
#include "FullTableException.h"
#include "ValueNotFoundException.h"

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
		//int nbAccess = hashTable->addValue(value);
		try {
			int nbAccess = hashTable->addValueWithSeparator(value);
			std::cout << "Valeur ajoutee dans le bucket, nobmre d'acces disque :  " << nbAccess << "." << std::endl;
		}
		catch (FullTableException ex) {
			std::cout << "Impossible, la table est pleine" << std::endl;
		}
	}
	else if (command == "supprimer") {
		string input;
		std::cout << "Valeur a supprimer ? ";
		getline(std::cin, input);
		int value = stoi(input);
		try {
			int nbAccess = hashTable->removeValue(value);
			std::cout << "Valeur supprimee dans le bucket, nobmre d'acces disque :  " << nbAccess << "." << std::endl;
		}
		catch (ValueNotFoundException) {
			std::cout << "Valeur non trouvee "<< std::endl;
		}
		
	}
	else if (command == "afficher") {
		printHashTable();
	}
	else if (command == "rechercher") {
		string input;
		std::cout << "Valeur a rechercher ? ";
		getline(std::cin, input);
		int value = stoi(input);
		try{
			SearchResult result = hashTable->searchWithSeparator(value);
			std::cout << "Valeur trouvee dans le Bucket " << result.getBucketNumber() << " - Nombre d'acces disque (avec separateurs) : "  << result.getNbAccess() << std::endl;
			SearchResult resultNoSeparator = hashTable->search(value);
			std::cout << "Valeur trouvee dans le Bucket " << resultNoSeparator.getBucketNumber() << " - Nombre d'acces disque (sans separateurs) : " << resultNoSeparator.getNbAccess() << std::endl;
		}
		catch (ValueNotFoundException) {
			std::cout << "Valeur non trouvee " << std::endl;
		}
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

