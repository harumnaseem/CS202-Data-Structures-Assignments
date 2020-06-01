#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include "bst.h"
#include "bst.cpp"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;
Dictionary::Dictionary() {
	wordsTree = NULL; 
	
}

Dictionary::~Dictionary(){
    // BST destructor gets called automatically
}

void Dictionary::initialize(string wordsFile) {

	ifstream file;
	file.open(wordsFile);
	int count = 0;
	string word;
	int c;
	// wordsTree = new BST<string>;
	cout<<"Enter how many words you want to insert in the tree from the file words.txt: ";
	cin>> c;
	cout<<endl;
	while(file>>word)
	{
		insertWord(word);
		count++;

		if(count == c)
			break;

	}
	file.close();
	cout<<"Words have been inserted."<<endl;
	cout<<"Total words: "<< count <<endl;
	
	
}


bool Dictionary::deleteWord(string word){
		wordsTree->delete_node(word);
		return true; 
	
}
bool Dictionary::editWord(string oldWord, string newWord) {
	node<string>* word_found = findWord(oldWord);
	if(word_found == NULL)
		return false;
 

	deleteWord(oldWord);

	insertWord(newWord);
	return true;
}
bool Dictionary::insertWord(string word) {

	if(wordsTree == NULL)
	{
		wordsTree = new BST<string>;
		wordsTree->insert(word, word);
		cout<< word << " inserted"<<endl;
		return true;
	}
    wordsTree->insert(word, word);
    cout<< word <<" inserted"<<endl;
	return true;
}

node<string>* Dictionary::findWord(string word) {
	clock_t t; 
    t = clock();
    // TODO your code here
    auto begin = std::chrono::high_resolution_clock::now();
   	node<string>* p = wordsTree->search(word);
   	auto end = std::chrono::high_resolution_clock::now();
   	cout<<endl<<"NANOSECONDS: "<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()<<endl;
    t = clock() - t; 

    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
    cout << "findWord() took " << time_taken << "sec to search for " << word << endl;  
    return p;
     // TODO
}

#endif

int main() {
	Dictionary test;
	test.initialize("words.txt");
	while(true)
	{
	int s;
	cout<<endl<<"MENU:"<<endl;
	cout<<"Enter 1 to insert a word."<<endl;
	cout<<"Enter 2 to search a word."<<endl;
	cout<<"Enter 3 to delete a word."<<endl;
	cout<<"Enter 4 to edit a word."<<endl;
	cout<<"Enter any other number to exit."<<endl<<endl;
	cout<<"Choice: ";
	cin>> s;


	if(s == 1)
	{
		string word;
		cout<<endl<<"Enter the word: ";
		cin>>word;
		test.insertWord(word);

		cout<<endl;
	}
	else if(s == 2)
	{
		string word;
		cout<<endl<<"Enter the word: ";
		cin>> word;
		node<string> * p = test.findWord(word);
		if(p==NULL)
			cout<<endl<<"Word not found."<<endl;
		else
			cout<<endl<<"Word found."<<endl;
	}
	else if(s == 3)
	{
		string word;
		cout<<endl<<"Enter the word: ";
		cin>> word;
		bool p = test.deleteWord(word);
		if(p== false)
			cout<<endl<<"Word not found."<<endl;
		else
			cout<<endl<<"Word deleted."<<endl;
	}
	else if(s == 4)
	{
		string word1, word2;
		cout<<endl<<"Enter the word you want to edit: ";
		cin>>word1;
		cout<<endl<<"Enter the new word: ";
		cin>>word2;
		bool p = test.editWord(word1,word2);
		if(p==false)
			cout<<endl<<"Word not found."<<endl;
		else
			cout<<endl<<"Word editted."<<endl;

	}
	else
		break;
	}
	return 0;
}
