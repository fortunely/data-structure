/*
 * Sort.c
 *
 *  Created on: 2020��2��9��
 *      Author: Martin
 */
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>

int Swap(int *s, int *t);
int Partition(int a[], int low, int high);

/**
 * void InsertSort(int a[], int n)
 * @brief ֱ�Ӳ�������
 * @param a array to be sorted
 * @param n array's length
 * @return none
 * @note ���ڱ�
 */
void InsertSort(int a[], int n)
{
	if(n < 0)
	{
		printf("Invalid array's length\n");
		exit(-1);
	}

	for(int i = 1; i < n; i++)
	{
		if(a[i] < a[i-1])
		{// a[i-1]����������һ��Ԫ��, Ҳ������Ԫ��. ����, ����Ҫ��ǰѰ�Ҵ�����λ��, ����������¼��Ҫ�����ƶ�
			int temp = a[i];
			a[i] = a[i-1];

			int j = i - 2;
			while(j >= 0 && temp < a[j])
			{
				a[j+1] = a[j];
				j--;
			}

			if(j < 0)
			{// j < 0, ���������м�û���ҵ����ʵ�λ��, Ӧ�������ײ���; ������ڱ�, ����j�ص���0
				a[0] = temp;
			}
		}
	}

}

/**
 * ���ֲ�������
 * @param a ��������
 * @param n ����Ԫ�ظ���
 * @note  ֱ�Ӳ�����������, ת��Ϊ��������
 */
void BInsertSort(int a[], int n)
{
	if(n < 0)
	{
		printf("Invalid array's length\n");
		exit(-1);
	}

	for(int i = 1; i < n ; i ++)
	{
		int low = 0;
		int high = i - 1;
		int temp = a[i];

		while(low <= high)
		{
			int middle = (low + high) >> 1;
			if(temp < a[middle])
			{
				high = middle - 1;
			}
			else
			{
				low = middle + 1;
			}
		}

		for(int j = i-1; j >= low; j --)
		{
			a[j+1] = a[j];
		}

		a[low] = temp;
	}
}

/**
 * һ��ϣ������
 * @note ���и��ݾ�������ֵdk, �����зֳɶ������, ��ÿ������ֱ����ֱ�Ӳ�������
 */
void ShellInsert(int a[], int n, int dk)
{
	for(int i = dk; i < n; i++)
	{// i��dk��ʼ, ��Ϊ������Ԫ��, ��Ϊǰ��ֻ��1��Ԫ��, û�б�Ҫ��ǰ����бȽϲ���
		if(a[i] < a[i-dk])
		{// ���ж��Ƿ��б�Ҫ��ǰ���Һ���λ��, ��Ϊÿ�����鵱ǰ���һ��Ԫ�������ֵԪ��
			int temp = a[i]; // temp ���浱ǰ������Ԫ��a[i]

			int j;
			for(j = i-dk; j >= 0 && temp < a[j]; j -= dk)
			{// ������Ԫ�ؽ�С, ��Ҫ������ǰ���Һ���λ��, ͬʱ��ǰԪ��λ�ú���
				a[j+dk] = a[j];
			}

			a[j+dk] = temp; // j+dk�ǵ�ǰ������Ԫ������λ��
		}
	}
}

/**
 * ϣ������
 */
void ShellSort(int a[], int n)
{
	for(int dlta = n/2; dlta > 0; dlta = dlta/2)
	{
		ShellInsert(a, n, dlta);
	}
}

int BubbleSort(int a[], int n)
{
	if(n < 0)
	{// error array's length
		return -1;
	}

	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 1; j < n - 1 - i; j ++)
		{
			if(a[j-1] > a[j])
			{// swap a[j-1] and a[j]
				int temp = a[j-1];
				a[j-1] = a[j];
				a[j] = temp;
			}
		}
	}

	return 0;
}

int QuickSort(int a[], int low, int high)
{
	if(low >= high)
	{
		return -1;
	}

	int pivotLoc = Partition(a, low, high);

	if(pivotLoc > low)
	{
		QuickSort(a, low, pivotLoc - 1);
	}

	if(pivotLoc < high)
	{
		QuickSort(a, pivotLoc + 1, high);
	}

	return 0;
}

int Partition(int a[], int low, int high)
{
	int pivotKey = a[low];
	while(low < high)
	{
		while(low < high && a[high] >= pivotKey) high --;
		a[low] = a[high];
		while(low < high && a[low] <= pivotKey) low ++;
		a[high] = a[low];
	}

	a[low] = pivotKey;

	return low;
}


/**
 * ������һ��ɸѡ, ����a[s], ʹa[s...n-1]��Ϊ�󶥶�
 * @param a ˳���, �洢��(�����)�������
 * @param n ˳���Ԫ�ظ���
 * @param s ������λ��
 * @note ��֪a[s...n-1]��a[s]��, ������󶥶Ѷ���, Ҳ����˵��Ҫ����a[s]��λ��, ʹa[s...n-1]��ȫ���ϴ󶥶Ѷ���
 */
void HeapAdjust(int a[], int n, int s)
{
	int rc = a[s]; // ������λ��ֵ

	// 2*s+1��s������, 2*s+2���Һ��� (���ڵ�λ��0)
	for(int j = 2*s + 1; j <= n; j *=2)
	{// ����a[s]�ϴ��ӽ��, ���±�����ɸѡ(��ΪҪ����, ֻ�����Ǵ��������a[s]�ͽϴ��ӽ�㽻��λ��)

		// ��ϴ��ӽ��, ������jΪ�ϴ��ӽ����˳����е�λ��
		if(j < n-1 && a[j] < a[j+1])
		{// ���j�����ӱ��Һ���С
			++ j; // jΪ�ϴ�ֵ�ĺ��ӽ���±�(���Һ���)
		}

		if(rc >= a[j]) // rc������ӽ���, ���ѷ��ϴ������, ����Ҫ�������е���
			break;

		// ����, rc������ӽ��jС, ��Ҫ�������s(���ڵ�)��j(����ӽ��)
		a[s] = a[j];

		s = j; // ����rcֵӦ��λ��, �˴�ֻ����rcӦ��λ��
	}

	a[s] = rc; // ��rcֵ���µ���������λ��
}


/**
 * ������
 * @param a ˳���a[0...n-1], ���ڴ洢�Ѻ����������е�����ṹ
 * @param n ˳���a��Ԫ�ظ���
 * @note �ǵݼ����ж�Ӧ�󶥶�, ĩβԪ��λ��n-1, ��Ӧ�����λ��(n-1)/2, Ҳ�����һ����Ҷ�ӽ��
 */
void HeapSort(int a[], int n)
{
	// ����(�󶥶�), �����һ����Ҷ�ӽ�㿪ʼ��ǰ����
	for(int i = (n-1)/2; i >=0; --i)
	{
		HeapAdjust(a, n, i); // �ӽ��i��ʼ���µ���
	}

	// ����Ѷ�������
	for(int i = n-1; i >= 0; --i)
	{
		Swap(&a[0], &a[i]); // ����Ѷ�Ԫ�ص�˳���ĩβ

		HeapAdjust(a, n, 0); // �ӶѶ���ʼ���϶��µ���
	}
}

/**
 * ����2��ֵ
 * @param s [out] ָ���һ��ֵ��ָ��
 * @param t [out] ָ��ڶ���ֵ��ָ��
 * @return �������
 * - -1 ��ָ��
 * - 0 �����ɹ�
 */
int Swap(int *s, int *t)
{
	if(s != NULL && t != NULL)
	{
		int temp = *s;
		*s = *t;
		*t = temp;
	}
	else
	{
		return -1;
	}

	return 0;
}

/**
 * ��ӡ����
 * @param a ָ�������ָ��
 * @param n ����Ԫ�ظ���
 * @note ��a[0...n-1]���ڴ�Ӧ����a��Ԫ��ֵ
 */
void PrintArray(int a[], int n)
{
	if(n < 0)
	{// error array's length
		printf("error array's length");
		return;
	}

	printf("array=[");
	for(int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("]\n");
}
