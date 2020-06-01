#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
	TreeItem* new_node= new TreeItem();
	new_node->id = 1;
	new_node->latest_data = data;

	VCS_node n(data,0);
	new_node->container.push_back(n);
	root = new_node;
	// write the rest of the code here
}

Tree::~Tree()
{
	if(root == NULL)
		delete root;

	for(int i = 0; i< (root->child).size(); i++)
	{
		for(int j = 0; j< ((root->child[i])->child).size(); j++)
		{
			delete (root->child[i]->child[j]);
		}
	}

	for(int i = 0; i < (root->child).size(); i++)
	{
		delete (root->child[i]);
	}

	delete root;

}


void Tree::branch(int id)
{	
	string id_of_parent = to_string(id);
	TreeItem* parent_node = get_node(id);
	if(parent_node == NULL)
	 	return;
	else
	{
		int size_of_child = (parent_node->child).size();
		if(size_of_child >= 9)
			return;
		else
		{
			string i = to_string(size_of_child + 1);
			string child_id = id_of_parent + i;
			int child_idd = stoi(child_id);
			TreeItem* new_child = new TreeItem; 
			new_child->id = child_idd;
			new_child->latest_data = parent_node->latest_data;
			VCS_node p(parent_node->latest_data,0);
			(new_child->container).push_back(p);
			(parent_node->child).push_back(new_child);
		}
		
	}
	
}

void Tree::merge(int src_id,int dst_id)
{
	TreeItem* src_node = get_node(src_id);
	TreeItem* dst_node = get_node(dst_id);
	if(src_node != NULL && dst_node != NULL)
	{
		dst_node->latest_data = dst_node->latest_data + src_node->latest_data;
		int s = (dst_node->container).size() - 1;
		(dst_node->container[s]).data = dst_node->latest_data;
		merge_state state;
		state.src_id = src_id;
		state.dst_id = dst_id;
		history.push_back(state);
	}

}

void Tree::commit(int src_id,string new_data)
{ 
	TreeItem* current = get_node(src_id);
	if(current != NULL)
	{
		string new_d = current->latest_data + new_data;
		int size_of_con = (current->container).size();
		VCS_node n(new_d, size_of_con);
		(current->container).push_back(n);
		current->latest_data = new_d;
	}
}

string Tree::get_file(int id, int t_stamp)
{
	TreeItem* temp = get_node(id);
	if(temp == NULL)
		return "";
	else
	{
		int size_of_con = (temp->container).size();
		for(int i = 0; i<size_of_con; i++)
		{
			if((temp->container[i]).time_stamp == t_stamp)
				return (temp->container[i]).data;
		}

		return "";
	}
} 

TreeItem* Tree::get_node(int iD)
{
	
	if(iD == 1)
		return root;

	if(iD >= 11 && iD <= 19)
	{
		if(root->child.empty())
			return NULL;
		else
		{
			vector<TreeItem*>::iterator newp;
			for(newp = root->child.begin(); newp != root->child.end(); newp++)
			{
				if((*newp)->id == iD)
					return (*newp);
			}
		}
		return NULL;

	}
	else if(iD >= 111 && iD <= 199)
	{
		if(root->child.empty())
		{
			return NULL;
		}
		else
		{
			int sc_id = iD/10;
			vector<TreeItem*>::iterator i;
			for(i = root->child.begin(); i != root->child.end(); i++)
			{
				if((*i)->id == sc_id)
				{
					TreeItem* sc = (*i);
					if((sc->child).empty())
					{
						return NULL;
					}

					for(i = (sc->child).begin(); i != (sc->child).end(); i++)
					{
						if((*i)->id == iD)
							return (*i);
					}
				}
			}
			
		}
		return NULL;
	}

	return NULL;
	
} 

vector<merge_state> Tree::merge_history()
{
	return history;
}

void Tree::level_traversal() 
{ 
	if(root == NULL)
		return;
	else
		cout<<"ID: "<< root->id <<endl;
		cout<<"Latest data: "<< root->latest_data<<endl;

	if(!(root->child).empty())
	{
		for(int i = 0; i < (root->child).size(); i++)
		{
			cout<<"ID: "<< (root->child[i])->id <<endl;
			cout<<"Latest data: "<< (root->child[i])->latest_data <<endl;
		}
	}
	else
		return;

	for(int i = 0; i< (root->child).size(); i++)
	{
		for(int j = 0; j< ((root->child[i])->child).size(); j++)
		{
			cout<<"ID: "<< ((root->child[i])->child[j])->id <<endl;
			cout<<"Latest data: "<< ((root->child[i])->child[j])->latest_data <<endl;
		}
	}
	
} 


#endif
