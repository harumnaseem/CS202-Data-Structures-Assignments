#ifndef VCS_CPP
#define VCS_CPP
#include <sstream>
#include<string>
#include<iomanip>
#include "VCS.h"

//base constructor, init
VCS::VCS(string fname)
{
	curr_size=0;
	filename = fname; 
}

//destructor
VCS::~VCS()
{
	curr_size = 0;
	// container1.~Stack();
	// container2.~Stack();
}


//time to commit
void VCS::commit(string msg)
{
	VCS_node* n = new VCS_node;
    n->message = msg;
    n->time_stamp = curr_size;

	ifstream version;
    version.open((filename+".txt").c_str());

    ostringstream str1;

    str1 << curr_size;
   	string num = str1.str();
    ofstream version2;
    version2.open((filename + num +".txt").c_str());

  	string ch;
  	while(!version.eof())
  	{
  		while(getline(version,ch))
  		{
  			version2<<ch;
  	
  		}
	}
    version.close();

    
    curr_size++;

    container1.push(*n); 
    


}

//print status of every version
void VCS::status()
{
	for(int i=0; i<5; i++)
	{
		VCS_node n = container1.top();
		cout<<endl<<"Message: "<< n.message;
		cout<<endl<<"Time stamp: "<< n.time_stamp<<endl;
		VCS_node n2 = container1.pop();
		container2.push(n2);
	}
	
	for(int i=0; i<5; i++)
	{
		VCS_node n2 = container2.pop();
		container1.push(n2);
	}
}

//goes one step back
string VCS::undo()
{

	container2.push(container1.pop());
	VCS_node n2 = container1.top();
	ostringstream str1;

    str1 << n2.time_stamp;
   	string num = str1.str();
    ifstream version2;
    version2.open((filename + num +".txt").c_str());

	ofstream version;
    version.open((filename+".txt").c_str());

    
  	string ch,line;
  	
  		while(getline(version2,ch))
  		{
  			version<<ch;
  			line = ch;
  		
  		}
  	
  	
    version2.close();
    version.close();

	return line;

}

//one step ahead
string VCS::redo()
{
	container1.push(container2.pop());
	VCS_node n2 = container1.top();
	ostringstream str1;

    str1 << n2.time_stamp;
   	string num = str1.str();
    ifstream version2;
    version2.open((filename + num +".txt").c_str());

	ofstream version;
    version.open((filename+".txt").c_str());

    
  	string ch,line;
  	
  		while(getline(version2,ch))
  		{
  			version<<ch;
  			line = ch;
  		
  		}
  	
  	
    version2.close();
    version.close();

	return line;

}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
	VCS_node N = container1.top();
	string x;
	if(t_stamp < N.time_stamp)
	{
		while(N.time_stamp != t_stamp)
		{
			x = undo();
			N = container1.top();
		}

		return x;
	}	

	else
	{
		while(N.time_stamp != t_stamp)
		{
			x= redo();
			N = container1.top();
		}

		return x;
	}

}

#endif