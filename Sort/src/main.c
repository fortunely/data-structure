/*
 * main.c
 *
 *  Created on: 2020Äê2ÔÂ9ÈÕ
 *      Author: Martin
 */
#include "Sort.h"

int array[] = {5,1,2,6,3,4,2,15,11};

int main(void)
{

	int array_length = sizeof(array)/sizeof(array[0]);

	PrintArray(array, array_length);
//	InsertSort(array, array_length);
//	BInsertSort(array, array_length);
//	ShellSort(array, array_length);
	HeapSort(array, array_length);

//	BubbleSort(array, array_length);
//	QuickSort(array, 0, array_length - 1);
	PrintArray(array, array_length);

	return 0;
}
