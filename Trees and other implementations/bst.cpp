#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
#include <algorithm>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST()
{
	delete_tree(root);
    // your destructor code goes here
}

template <class T>
void delete_tree(node<T>* p)
{
	if(p != NULL)
	{
		delete_tree(p->left);
		delete_tree(p->right);
		delete p;
	}
}

template <class T>
int BST<T> :: height (node<T>* p)
{
   // your find height code goes here
    if(p == NULL)
    {
    	return 1;
    }
    else 
    {
    	int left_subtree = height(p->left);
    	int right_subtree =  height(p->right);
    	if(left_subtree >= right_subtree)
    		return left_subtree + 1;
    	else
    		return right_subtree + 1;
    }
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    
    return (height(p->left) - height(p->right));
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    p->height = 1 + max(height(p->left), height(p->right));
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    node<T>* temp = p->right;
    p->right = temp->left;
    temp->left = p;
    p->height = height(p);
   	temp->height = height(temp);
   	p = temp;
    return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
    node<T>* temp = p->left;
    p->left = temp->right;
    temp->right = p;
    p->height = height(p);
   	temp->height = height(temp);
    p = temp;
    return p;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){   
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
    int balance_factor = balanceFactor(p);
    fixHeight(p);
    if(balance_factor > 1)
    {
    	int balance_factor2 = balanceFactor(p->left);
    	// Left Left
    	if(balance_factor2 >= 0)
    	{
    		return rotateright(p);
    	}
    	// Left Right
    	else
    	{
    		p->left = rotateleft(p->left);
    		return rotateright(p);
    	}
    }
    else if(balance_factor < -1)
    {
    	int balance_factor2 = balanceFactor(p->right);
    	// Right Left
    	if(balance_factor2 > 0)
    	{
    		p->right = rotateright(p->right);
    		return rotateleft(p);
    	}
    	// Right Right
    	else
    	{
    		return rotateleft(p);
    	}
    	
    }
    fixHeight(p);
    return p;
    
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
	root = insertHelper(value,k,root);
}

// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) 
{ // note we need a helper because we need recursive calls
    // Insertion code goes here.
	if(p == NULL)
	{
		node<T>* temp = new node<T>(k,value);
		return temp;
	}
	else if(p->key > k)
	{
		p->left = insertHelper(value, k, p->left);
		return balance(p);
	}
	else if(p->key < k)
	{
		p->right = insertHelper(value,k, p->right);
		return balance(p);
	}
    
}
template<class T>
node<T>* BST<T> :: search(T key){
	return helpersearch(root, key);
    // Search code goes here.
}

template <class T>
node<T>* helpersearch(node<T>* p, T key)
{
	if(p == NULL)
		return NULL;
	else if(p->key == key)
		return p;
	else if(p->key > key)
		return helpersearch(p->left, key);
	else
		return helpersearch(p->right, key);
}

// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
	node<T>* temp = p;
	while(temp->left != NULL)
		temp = temp->left;

	return temp;
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
	if(p == NULL)
	{
		return p;
	}
	else 
	{
	    if(p->left == NULL)
	    	return p->right;
	    else
	    {
	    	p->left = removemin(p->left);
	    	return balance(p);
	    }
	}


	// This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
	if(p == NULL)
		return p;
	else if(p->key > k)
	{
		p->left = remove(p->left, k);
	}
	else if(p->key < k)
	{
		p->right = remove(p->right, k);
	}
	else
	{
		if(p->right == NULL && p->left == NULL)
		{
			delete p;
			p = NULL;
			return p;
		}
		else if(p->right == NULL)
		{
			node<T>* temp = p;
			p = p->left;
			delete temp;
			return p;
		}
		else if(p->left == NULL)
		{
			node<T>* temp = p;
			p = p->right;
			delete temp;
			return p;
		}
		else
		{
			node<T>* temp = findmin(p->right);
			p-> key = temp->key;
			p->right = removemin(p->right);
		}
	}
	
    return balance(p);
    

    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
