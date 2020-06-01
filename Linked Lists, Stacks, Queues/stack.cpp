#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
	// list.head = NULL;
	// list.tail = NULL;
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
	list.~LinkedList();
	ListItem<T>* h = (otherStack.list).getHead();
    if (h != NULL)
    {
        while (h!=NULL)
        {
            list.insertAtTail(h->value);
            h=h->next;
        }
    } 
}

template <class T>
Stack<T>::~Stack()
{
	list.~LinkedList();
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	ListItem<T>* h = list.getHead();
	if(h != NULL)
	{
		return h->value;
	}
	
}

template <class T>
T Stack<T>::pop()
{
	ListItem<T>* h = list.getHead();
	if(h != NULL)
	{
		T val = h->value;
		list.deleteHead();
		return val;
	}
	
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	ListItem<T>* h = list.getHead();
	if(h == NULL)
		return true;

	return false;
}

#endif
