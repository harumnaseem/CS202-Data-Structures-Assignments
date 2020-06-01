#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){
	unsigned long sum = 0;
	int length_of_string = value.length();

	for(int i = 0; i < length_of_string; i++)
	{
		int ascii = (int) value[i];
		sum = sum + (pow(a, length_of_string - 1 - i)* ascii);
	}
	return sum;
}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	unsigned long hash_code = 0;
	int length_of_string = value.length();

	for(int i = 0; i < length_of_string; i++)
	{
		int ascii = (int) value[i];
		hash_code ^= (hash_code << 5) + (hash_code >> 2) + ascii;
	}

	return hash_code;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
	unsigned long index = hash % size;
	return index;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
	unsigned long index = (a*hash + m) % size;
	return index;
}
#endif
// you may write your own program to test these functions.

// int main()
// {
// 	string input; 
// 	cout<<"Enter a word: ";
// 	cin>> input;
// 	unsigned long hash_code1 = polyHash(input, 9);
// 	cout<<"Polynomial Hash Code: "<< hash_code1 <<endl;
// 	cout<<"Index after division compression: "<< divCompression(hash_code1, 100)<<endl;
// 	cout<<"Index after MAD compression: "<< madCompression(hash_code1, 100)<<endl<<endl;

// 	cout<<"Enter a word: ";
// 	cin>> input;
// 	unsigned long hash_code2 = bitHash(input);
// 	cout<<"Bitwise Hash code: "<< hash_code2 <<endl;
// 	cout<<"Index after division compression: "<< divCompression(hash_code2, 100)<<endl;
// 	cout<<"Index after MAD compression: "<< madCompression(hash_code2, 100)<<endl<<endl;
// 	return 0;
//}