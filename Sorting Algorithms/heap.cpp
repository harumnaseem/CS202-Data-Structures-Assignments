#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"


MinHeap::MinHeap(int cap)
{
	capacity = cap;
	harr = new int[capacity];
	heap_size = 0;
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int small = i;
	if (r<heap_size && harr[r]<harr[small])
	{
		small = r;
	}
	if ( l<heap_size &&harr[l]<harr[small])
	{
		small =l;
	}
	if (small != i)
	{
		int a = harr[i];
		harr[i]=harr[small];
		harr[small]=a;
		MinHeapify(small);
	}

}
 
int MinHeap::parent(int i)
{
	return (i-1)/2;
}
 
int MinHeap::left(int i)
{
	return 2*i + 1;
}
 
int MinHeap::right(int i)
{
	return 2*i + 2;
}
 
int MinHeap::extractMin()
{
	if (heap_size<=0)
	{
		return -1;
	}
	else if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}
	else
	{

		int a = harr[0];
		harr[0]=harr[heap_size-1];
		heap_size--;
		MinHeapify(0);
		return a;
	}
}
 
void MinHeap::decreaseKey(int i, int new_val)
{
	int index = i;
	harr[i] = new_val;
	int index2 = parent(index);
	while(index != 0 && harr[index2] > harr[index])
	{
		int temp = harr[index];
		harr[index] = harr[index2];
		harr[index2] = temp;
		index = index2;
		index2 = parent(index);
	}
}
 
int MinHeap::getMin()
{
	if(heap_size == 0)
		return -1;

	return harr[0];
}
 
void MinHeap::deleteKey(int i)
{
	if(i < heap_size)
	{
		int min = getMin() - 1;
		decreaseKey(i, min);
		extractMin();
	}
}
 
void MinHeap::insertKey(int k)
{
	if(heap_size < capacity)
	{
		int index = heap_size;
		harr[index] = k;
		heap_size++;
		if(index == 0)
			return;
		int index2 = parent(index);
		while(harr[index2] > harr[index])
		{
			int temp = harr[index];
			harr[index] = harr[index2];
			harr[index2] = temp;
			index = index2;
			index2 = parent(index);
			if(index == 0)
				break;
		}
	}
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif