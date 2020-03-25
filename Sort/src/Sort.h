/*
 * Sort.h
 *
 *  Created on: 2020年2月9日
 *      Author: Martin
 */

#ifndef SRC_SORT_H_
#define SRC_SORT_H_

void InsertSort(int a[], int n); // 直接插入排序
void BInsertSort(int a[], int n); // 二分插入排序
void ShellSort(int a[], int n); // 希尔排序
int BubbleSort(int a[], int n); // 冒泡排序
int QuickSort(int a[], int low, int high); // 快速排序
void HeapSort(int a[], int n); // 堆排序
void PrintArray(int a[], int n);

#endif /* SRC_SORT_H_ */
