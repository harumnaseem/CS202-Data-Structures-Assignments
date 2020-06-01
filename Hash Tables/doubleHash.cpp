#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    hashTable = new block*[tableSize];

    for(int i = 0; i<tableSize; i++)
    {
    	hashTable[i] = NULL;
    }
    count = 0;
}

unsigned long HashD::hash1(string value)
{
	return madCompression(bitHash(value), tableSize);
}

unsigned long HashD::hash2(string value)
{
	return 13 - (bitHash(value) % 13);
}

HashD::~HashD(){
	for(int i = 0; i<tableSize; i++)
	{
		delete hashTable[i];
	}

	delete hashTable;

}

void HashD::resizeTable(){
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
			unsigned long index = hash1(hashTable[i]->value);
			
			int collision_count = 1;
			unsigned long second_index = hash2(hashTable[i]->value);
			unsigned long temp = index;
			while(newHashTable[temp] != NULL)
			{
				temp = (index + (collision_count*second_index)) % tableSize;
				collision_count++;
			}
			newHashTable[temp] = new block(bitHash(hashTable[i]->value), hashTable[i]->value);

		}
		
	}

	for(int i = 0; i< old_size; i++)
	{
		delete hashTable[i];
	}

	delete hashTable;
	hashTable = newHashTable;
}

void HashD::insert(string value){
	if(count*(1.0)/tableSize >= 0.3)
	{
		resizeTable();
	}

	unsigned long index = hash1(value);
	if(hashTable[index] == NULL)
	{
		hashTable[index] = new block(bitHash(value), value);
		count++;
		return;
	}

	unsigned long second_index = hash2(value);
	unsigned long collision_count = 1;
	while(1)
	{
		unsigned long temp = (index + collision_count*second_index) % tableSize;
		if(hashTable[temp] == NULL)
		{
			hashTable[temp] = new block(bitHash(value), value);
			count++;
			return;
		}
		collision_count++;
	}
}

void HashD::deleteWord(string value){
	unsigned long index = hash1(value) ;
    int counter = 0 ;
    int x = 1 ;

    while((hashTable[index] != NULL) && (hashTable[index] -> value != value))
    {
        index = (hash1(value) + (x * hash2(value))) % tableSize ; 
        x++ ;
    }

    if (hashTable[index] != NULL)
    {
        hashTable[index] = NULL ;
        count-- ;
    }
}

block* HashD::lookup(string value){
	unsigned long index = hash1(value);

	int collision_count = 1;
	unsigned long second_index = hash2(value);
	unsigned long temp = index;
	int c = 0;

	while(hashTable[temp] != NULL)
	{
		
		if(hashTable[temp]->value == value)
			return hashTable[temp];
		temp = (index + (collision_count*second_index)) % tableSize;
		collision_count++;
		c++;
		if(c > count)
			return NULL;

	}  
	
    return NULL;



}

#endif