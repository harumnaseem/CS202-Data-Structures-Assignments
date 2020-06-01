#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	head = NULL;
    if (otherLinkedList.head != NULL)
    {
        ListItem<T> *temp= otherLinkedList.head;
        while (temp!=NULL)
        {
            insertAtTail(temp->value);
            temp=temp->next;
        }
    } 
}

template <class T>
LinkedList<T>::~LinkedList()
{
	while (head!=NULL)
    {
        ListItem<T> *temp = head;
        delete temp;
        head=head->next;
    }
    delete head;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T> *temp = new ListItem<T>(item);
	head = getHead();
	if(head == NULL)
	{
		head = temp;
		tail = temp;
	}

	else 
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{

	if(head == NULL)
	{
		insertAtHead(item);
	}
	else if(head -> next == NULL)
	{
		ListItem<T>* temp = new ListItem<T>(item);
		head->next = temp;
		temp->prev = head;
		temp->next = NULL;
		tail = temp;
	}
	else 
	{
		ListItem<T>* temp = getTail();
		ListItem<T>* temp2 = new ListItem<T>(item);
		temp2 -> prev = temp;
		temp -> next = temp2;
		temp2 ->next = NULL;
		tail = temp2;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T>* temp = searchFor(afterWhat);

	if(temp != NULL)
	{
		// nothing
	}
	if(temp -> next == NULL)
	{
		ListItem<T>* temp2 = new ListItem<T>(toInsert);
		temp-> next = temp2;
		temp2->prev = temp;
		head->next = temp2;
		tail = temp2;
	}
	else
	{
		ListItem<T>* temp2 = new ListItem<T>(toInsert);
		ListItem<T>* temp3 = temp->next;
		temp2-> next = temp3;
		temp2-> prev = temp;
		temp3-> prev = temp3;
		temp-> next = temp2;
	}
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{

	return tail;	
	
	 	
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    ListItem<T> *temp = getHead();

	if(temp != NULL)
	{
		while(temp -> next != NULL)
		{
			if(temp -> value == item)
			{
				return temp;
			}
			
			temp = temp -> next;
		}

		if(temp -> value == item)
		{
			return temp;
		}

	}

}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T>* temp = searchFor(item);

	if(temp == NULL)
	{
		// no such element
		return;
	}

	if(temp == tail)
	{
		deleteTail();
	}
	else if(temp==head)
	{
		deleteHead();
	}
	else
	{
		(temp->prev)->next = temp->next;
		(temp->next)->prev = temp->prev;
		delete temp;
	}
}

template <class T>
void LinkedList<T>::deleteHead()
{
	if(head == NULL)
 	{
		// cout<<"The list is already empty.";
	}
	else if(head->next == NULL)
	{
		ListItem<T>* temp = head;
	 	head = NULL;
	 	tail = NULL;
	 	delete temp;
	}
	else 
	{
	 	ListItem<T> *temp = head;
	 	head = head->next;
	 	head->prev = NULL;
	 	delete temp;
	}

}

template <class T>
void LinkedList<T>::deleteTail()
{
	if(head == NULL)
	{
		// cout<<"The list is already empty.";
	}
	else if(head -> next == NULL)
	{
		ListItem<T>* temp = tail;
	 	head = NULL;
	 	tail = NULL;
	 	delete temp;
	}	
	else
	{
		ListItem<T> *temp = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete temp;
	}
	
}

template <class T>
int LinkedList<T>::length()
{
	int c = 0;
	
	ListItem<T>* temp = head;

	while(temp !=NULL)
	{
		c++;
		temp = temp->next;
	}

	return c;
}

#endif