#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
	list.~LinkedList();
	ListItem<T>* h = (otherQueue.list).getHead();
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
Queue<T>::~Queue()
{
	list.~LinkedList();
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	ListItem<T>* h = list.getHead();
	if(h != NULL)
	{
		return h->value;
	}
	
}

template <class T>
T Queue<T>::dequeue()
{
	ListItem<T>* h = list.getHead();
	if(h != NULL)
	{
		int val = h->value;
		list.deleteHead();
		return val;
	}
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	ListItem<T>* h = list.getHead();
	if(h == NULL)
		return true;

	return false;
}


#endif