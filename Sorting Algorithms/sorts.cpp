#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include <vector>
#include "list.cpp"
#include "list.h"
#include <cmath>
#include <stdlib.h>
//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	int capacity = nums.size();
	long arr[capacity];
	for(int i = 0; i < capacity; i++)
	{
		arr[i] = nums[i];
	}
	for(int i = 1; i< capacity; i++)
	{
		long temp = arr[i];
		long index = i-1;

		while(index>=0)
		{
			if(temp < arr[index])
			{
				arr[index + 1] = arr[index];
				index--;
			}
			else
				break;
		}
		arr[index + 1] = temp;
	}

	for(int i = 0; i<capacity; i++)
	{
		nums[i] = arr[i];
	}

	return nums;
}

//=====================================================================================
ListItem<long>* splitLL(ListItem<long>* a)
{
	ListItem<long>* temp = a;
	ListItem<long>* temp2 = temp;
	while(temp->next != NULL && temp->next->next != NULL)
	{
		temp = temp->next->next;
		temp2 = temp2->next;
	}

	ListItem<long>* last_LL = temp2->next;
	temp2->next = NULL;
	return last_LL;
}

ListItem<long>* mergeLL(ListItem<long>* head1, ListItem<long>* head2)
{
	if(head1 == NULL)
	{
		return head2;
	}

	if(head2 == NULL)
	{
		return head1;
	}

	ListItem<long>* temp1 = head1;
	ListItem<long>* temp2 = head2;
	if(temp1->value <= temp2->value)
	{
		temp1->next = mergeLL(temp1->next, temp2);
		temp1->next->prev = temp1;
		temp1->prev = NULL;
		return temp1;
	}
	else
	{
		temp2->next = mergeLL(temp1, temp2->next);
		temp2->next->prev = temp2;
		temp2->prev = NULL;
		return temp2;
	}
}

ListItem<long>* sortLL(ListItem<long>* original_head)
{
	if(original_head == NULL || original_head->next == NULL)
	{
		return original_head;
	}
	else
	{
		ListItem<long>* temp = splitLL(original_head);
		ListItem<long>* temp2 = sortLL(original_head);
		temp = sortLL(temp);
		return mergeLL(temp2,temp);
	}
}

vector<long> MergeSort(vector<long> nums)
{
	int capacity = nums.size();
	if(capacity <= 1)
		return nums;
	List<long> LL;

	for(int i = 0; i< capacity; i++)
	{
		LL.insertAtHead(nums[i]);
	}

	ListItem<long>* head = LL.getHead();
	head = sortLL(head);

	int count = 0;
	while(head != NULL)
	{
		nums[count] = head->value;
		head = head->next;
		count++;
	}

	return nums;
}


//=====================================================================================
void QuickSortArray2(long* arr, int left_bound, int right_bound)
{
	long pivot = arr[right_bound];
	int temp_left = left_bound;
	int temp_right = right_bound;

	while(temp_left <= temp_right)
	{
		while(arr[temp_left] < pivot)
		{
			temp_left++;
		}

		while(arr[temp_right] > pivot)
		{
			temp_right--;
		}

		
		if(temp_left <= temp_right)
		{
			long temp = arr[temp_left];
			arr[temp_left] = arr[temp_right];
			arr[temp_right] = temp;
			temp_left++;
			temp_right--;
		}
	}
	if(left_bound < temp_right)
	{
		QuickSortArray2(arr, left_bound, temp_right);
	}

	if(right_bound > temp_left)
	{
		QuickSortArray2(arr, temp_left, right_bound);
	}
}

vector<long> QuickSortArray(vector<long> nums)
{
	int capacity = nums.size();
	long arr[capacity];

	for(int i = 0; i<capacity; i++)
	{
		arr[i] = nums[i];
	}

	QuickSortArray2(arr,0,capacity-1);

	for(int i = 0; i<capacity; i++)
	{
		nums[i] = arr[i];
	}
	return nums;
}

//=====================================================================================
ListItem<long>* splitLL2(ListItem<long>* temp1, ListItem<long>* temp2)
{
	long pivot = temp2->value;
	ListItem<long>* x = temp1->prev;
	ListItem<long>* temp = temp1;
	while(temp != temp2)
	{
		if(temp->value <= pivot)
		{
			if(x == NULL)
			{
				x = temp1;
			}
			else
			{
				x = x->next;
			}

			long a = x->value;
			x->value = temp->value;
			temp->value = a;
		}

		temp = temp->next;
	}
	if(x == NULL)
	{
		x = temp1;
	}
	else
	{
		x = x->next;
	}
	
	long a = x->value;
	x->value = temp2->value;
	temp2->value = a;
	return x;
}

void QuickSortList2(ListItem<long>* temp1, ListItem<long>* temp2)
{
	if(temp2 != NULL && temp1 != temp2 && (temp1 != NULL && temp1->prev != temp2))
	{
		ListItem<long>* temp = splitLL2(temp1,temp2);
		QuickSortList2(temp1, temp->prev);
		QuickSortList2(temp->next, temp2);
	}
}

vector<long> QuickSortList(vector<long> nums)
{
	int capacity = nums.size();
	List<long> LL;
	for(int i = 0; i<capacity; i++)
	{
		LL.insertAtHead(nums[i]);
	}

	ListItem<long>* head = LL.getHead();
	ListItem<long>* tail = LL.getTail();

	QuickSortList2(head, tail);

	int count = 0;
	while(head != NULL)
	{
		nums[count] = head->value;
		count++;
		head = head->next;
	}

	return nums;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
	int capacity = nums.size();
	MinHeap Heap(capacity);

	for(int i = 0; i<capacity; i++)
	{
		Heap.insertKey(nums[i]);
	}

	for(int i = 0; i<capacity; i++)
	{
		nums[i] = Heap.extractMin();
	}
	return nums;
}

//=====================================================================================
vector<long> QueenOfAllSorts(vector<long> nums)
{
	int capacity = nums.size();
	long largest_element = nums[0];
	long smallest_element = nums[0];
	for(int i = 1; i<capacity; i++)
	{
		if(largest_element < nums[i])
		{
			largest_element = nums[i];
		}
		if(smallest_element > nums[i])
		{
			smallest_element = nums[i];
		}
	}

	int array_size = largest_element + abs(smallest_element) + 1;
	long arr[array_size];
	long frequency_table[array_size];

	for(int i = 0; i<array_size; i++)
	{
		arr[i] = -7387837873874787437;
		frequency_table[i] = 0;
	}
	for(int i = 0; i<capacity; i++)
	{
		long element = nums[i];
		if(element < 0)
		{
			int index = abs(smallest_element) - abs(element);
			if(arr[index] == -7387837873874787437)
			{
				arr[index] = element;
				frequency_table[index]++;
			}
			else
			{
				frequency_table[index]++;
			}
		}
		else
		{
			int index = abs(smallest_element) + element;
			if(arr[index] == -7387837873874787437)
			{
				arr[index] = element;
				frequency_table[index]++;
			}
			else
			{
				frequency_table[index]++;
			}
		}
	}
	

	int count = 0;
	for(int i = 0; i<nums.size(); i++)
	{
		int frequency = frequency_table[i];
		while(frequency != 0)
		{
			nums[count] = arr[i];
			count++;
			frequency--;
		}
	}
	
	return nums;
}
#endif