#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size)
{
	tableSize = size;
	hashTable = new LinkedList<string>[tableSize];

}
HashC::~HashC(){

}

unsigned long HashC :: hash(string input)
{
	return bitHash(input);
	
}

void HashC::insert(string word)
{
	int index = madCompression(hash(word), tableSize);
 	hashTable[index].insertAtHead(word);
} 

ListItem<string>* HashC :: lookup(string word){
	int index = madCompression(hash(word), tableSize);
	ListItem<string> * a = hashTable[index].searchFor(word);
	return a;
}

void HashC :: deleteWord(string word){
	int index = madCompression(hash(word), tableSize);
	hashTable[index].deleteElement(word);	
}


#endif