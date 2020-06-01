//include any header files as required
#include "cache_linear.h"
#include "cache_linear.cpp"
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <sstream>

string find_in_dictionary(unsigned long num)
{
	ifstream dictionaryfile("dictionary.txt");
	string line, value;
	unsigned long num2;
	for(int i = 0; i<= num; i++)
	{
		getline(dictionaryfile, line);
	}
	stringstream lstream(line);
	lstream >> num2;
	lstream >> value;
	dictionaryfile.close();
	return value;
}

int main()
{
	ifstream secretfile;
	string secretfile2, comma, word;
	HashL* hash = new HashL();
	int withorwithout, num, secretfilechoice;
	while(1)
	{
		cout<<endl<<"Press 1 to test without cache"<<endl;
		cout<<"Press 2 to test with cache"<<endl;
		cout<<"Press 3 to exit"<<endl;
		cin>> withorwithout;

		if(withorwithout == 3)
			break;
		else if(withorwithout == 1)
		{
			cout<<endl<<endl<<"Press 1 to test in secret1.txt"<<endl;
			cout<<"Press 2 to test in secret2.txt"<<endl;
			cout<<"Press 3 to test in secret3.txt"<<endl;
			cout<<"Press 4 to test in secret4.txt"<<endl;
			cin>> secretfilechoice;
			if(secretfilechoice == 1)
			{
				secretfile.open("secret1.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					cout<<find_in_dictionary(num)<<endl;
					secretfile>>comma;
				
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken without cache to read secret1.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 2)
			{
				secretfile.open("secret2.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					cout<<find_in_dictionary(num)<<endl;
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken without cache to read secret2.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 3)
			{
				secretfile.open("secret3.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					cout<<find_in_dictionary(num)<<endl;
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken without cache to read secret3.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 4)
			{
				secretfile.open("secret4.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					cout<<find_in_dictionary(num)<<endl;
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken without cache to read secret4.txt: "<< time_taken <<endl;
				continue;
			}
			else
			{
				break;
			}
		}
		else if(withorwithout == 2)
		{
			cout<<endl<<endl<<"Press 1 to test in secret1.txt"<<endl;
			cout<<"Press 2 to test in secret2.txt"<<endl;
			cout<<"Press 3 to test in secret3.txt"<<endl;
			cout<<"Press 4 to test in secret4.txt"<<endl;
			cin>> secretfilechoice;
			
			if(secretfilechoice == 1)
			{
				secretfile.open("secret1.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					
					block* found = hash->lookup(num);
					if(found != NULL)
					{
						cout<<found->value<<endl;
					}
					else
					{
						word = find_in_dictionary(num);
						cout<<word<<endl;
						hash->insert(num,word);					
					}
					secretfile>>comma;
					
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken with cache to read secret1.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 2)
			{
				secretfile.open("secret2.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					block* found = hash->lookup(num);
					if(found != NULL)
					{
						cout<<found->value<<endl;
					}
					else
					{
						word = find_in_dictionary(num);
						cout<<word<<endl;
						hash->insert(num,word);					
					}
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken with cache to read secret2.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 3)
			{
				secretfile.open("secret3.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					block* found = hash->lookup(num);
					if(found != NULL)
					{
						cout<<found->value<<endl;
					}
					else
					{
						word = find_in_dictionary(num);
						cout<<word<<endl;
						hash->insert(num,word);					
					}
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken with cache to read secret3.txt: "<< time_taken <<endl;
				continue;
			}
			else if(secretfilechoice == 4)
			{
				secretfile.open("secret4.txt");
				clock_t t = clock();

				while(secretfile >> num)
				{
					block* found = hash->lookup(num);
					if(found != NULL)
					{
						cout<<found->value<<endl;
					}
					else
					{
						word = find_in_dictionary(num);
						cout<<word<<endl;
						hash->insert(num,word);					
					}
					secretfile>>comma;
				}
				secretfile.close();
				t = clock() - t;
				double time_taken = ((double)t) /CLOCKS_PER_SEC;
				cout<<"Time taken with cache to read secret4.txt: "<< time_taken <<endl;
				continue;
			}
			else
			{
				break;
			}
		}

	}

	



	return 0;
}