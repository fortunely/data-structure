/*
 * Sort.h
 *
 *  Created on: 2020��2��9��
 *      Author: Martin
 */

#ifndef SRC_SORT_H_
#define SRC_SORT_H_

void InsertSort(int a[], int n); // ֱ�Ӳ�������
void BInsertSort(int a[], int n); // ���ֲ�������
void ShellSort(int a[], int n); // ϣ������
int BubbleSort(int a[], int n); // ð������
int QuickSort(int a[], int low, int high); // ��������
void HeapSort(int a[], int n); // ������
void PrintArray(int a[], int n);

#endif /* SRC_SORT_H_ */
