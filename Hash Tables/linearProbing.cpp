#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    hashTable = new block*[tableSize];
    count = 0;
    for(int i = 0; i<tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
}

HashL::~HashL(){
    for(int i = 0; i<tableSize; i++)
    {
    	delete hashTable[i];
    }

    delete hashTable;
}

unsigned long HashL :: hash(string value){
	return bitHash(value);
}

void HashL::resizeTable(){
	int old_size = tableSize;
	tableSize = tableSize*2;
	block** newHashTable = new block*[tableSize];
	for(int i = 0; i<tableSize; i++)
	{
		newHashTable[i] = NULL;
	}

	for(int i = 0; i<old_size; i++)
	{
		if(hashTable[i] != NULL)
		{
			int index = madCompression(hash(hashTable[i]->value), tableSize);
			while(newHashTable[index] != NULL)
			{
				index = (index + 1)%tableSize;
			}
			newHashTable[index] = new block(hash(hashTable[i]->value),hashTable[i]->value);
		}	
			
	}

	for(int i = 0; i< old_size; i++)
	{
		delete hashTable[i];
	}
	delete hashTable;
	hashTable = newHashTable;
}

void HashL::insert(string value){
	if((count * 1.0)/tableSize >= 0.5)
	{
		resizeTable();
	}
	int index = madCompression(hash(value), tableSize);
 	while(hashTable[index] != NULL )
 	{
 		index = (index + 1)% tableSize;
 	}
 	
 	hashTable[index] = new block(hash(value),value);
 	count++;

 	
 	
}

void HashL::deleteWord(string value){
	int index = madCompression(hash(value), tableSize);
	if(hashTable[index] == NULL)
		return;
	if(hashTable[index]->value == value)
	{
		delete hashTable[index];
		hashTable[index] = NULL;
		count--;
	}
	while(hashTable[index] != NULL)
	{
		if(hashTable[index]->value == value)
		{
			delete hashTable[index];
			hashTable[index]= NULL;
			count--;
			return;
		}
		index = (index + 1)% tableSize;
	}
}


block* HashL::lookup(string value)
{
	int index = madCompression(hash(value), tableSize);
	if(hashTable[index] != NULL)
	{
		if(hashTable[index]->value == value)
			return hashTable[index];
	}
	int c = 0;
	while(hashTable[index] != NULL)
	{
		c++;
		if(hashTable[index]->value == value)
		{			
			return hashTable[index];
		}
		else if(c > count)
		{
			return NULL;
		}

		index = (index + 1)% tableSize;
	}

	return NULL;
}
#endif
