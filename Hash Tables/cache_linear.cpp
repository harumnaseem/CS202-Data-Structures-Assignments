#ifndef CACHE_LINEAR_CPP
#define CACHE_LINEAR_CPP

#include "cache_linear.h"
#include "hashfunctions.cpp"
#include "cache_linear.cpp"

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
	return madCompression(bitHash(value), tableSize);
}


void HashL::insert(unsigned long key, string value){
	string s = to_string(key);
	unsigned long index = hash(s);
	if(count == tableSize)
	{
		
		int temp_count = hashTable[index]->block_count;
		unsigned long index2 = index;
		for(int i = 0; i<tableSize; i++)
		{
			if(hashTable[i] != NULL)
			{
				if(temp_count > hashTable[i]->block_count)
				{
					temp_count = hashTable[i]->block_count;
					index2 = i;
				}
			}
		}
		hashTable[index2] = new block(key, value);
		return;
	}
 	while(hashTable[index] != NULL)
 	{
 		index = (index + 1)% tableSize;
 	}
 	
 	hashTable[index] = new block(key,value);
 	count++; 	
}

block* HashL::lookup(unsigned long key)
{
	string s = to_string(key);
	int index = hash(s);
	int c = 0;
	while(hashTable[index] != NULL)
	{
		if(hashTable[index]->key == key)
		{		
			hashTable[index]->block_count = hashTable[index]->block_count + 1;	
			return hashTable[index];
		}
		else if(c > count)
		{
			return NULL;
		}
		c++;

		index = (index + 1)% tableSize;
	}

	return NULL;
}
#endif
