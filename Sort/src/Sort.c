/*
 * Sort.c
 *
 *  Created on: 2020年2月9日
 *      Author: Martin
 */
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>

int Swap(int *s, int *t);
int Partition(int a[], int low, int high);

/**
 * void InsertSort(int a[], int n)
 * @brief 直接插入排序
 * @param a array to be sorted
 * @param n array's length
 * @return none
 * @note 无哨兵
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
		{// a[i-1]是有序表最后一个元素, 也是最大的元素. 逆序, 则需要往前寻找待插入位置, 并且有序表记录都要往后移动
			int temp = a[i];
			a[i] = a[i-1];

			int j = i - 2;
			while(j >= 0 && temp < a[j])
			{
				a[j+1] = a[j];
				j--;
			}

			if(j < 0)
			{// j < 0, 代表序列中间没有找到合适的位置, 应在序列首插入; 如果有哨兵, 这里j必等于0
				a[0] = temp;
			}
		}
	}

}

/**
 * 二分插入排序
 * @param a 待排序列
 * @param n 序列元素个数
 * @note  直接操作待排序列, 转换为升序序列
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
 * 一趟希尔排序
 * @note 序列根据具体增量值dk, 将序列分成多个分组, 对每个分组分别进行直接插入排序
 */
void ShellInsert(int a[], int n, int dk)
{
	for(int i = dk; i < n; i++)
	{// i从dk开始, 作为待插入元素, 因为前面只有1个元素, 没有必要和前面进行比较步骤
		if(a[i] < a[i-dk])
		{// 先判断是否有必要往前查找合适位置, 因为每个分组当前最后一个元素是最大值元素
			int temp = a[i]; // temp 缓存当前待插入元素a[i]

			int j;
			for(j = i-dk; j >= 0 && temp < a[j]; j -= dk)
			{// 待插入元素较小, 需要继续往前查找合适位置, 同时当前元素位置后移
				a[j+dk] = a[j];
			}

			a[j+dk] = temp; // j+dk是当前待插入元素最终位置
		}
	}
}

/**
 * 希尔排序
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
 * 堆排序一趟筛选, 调整a[s], 使a[s...n-1]成为大顶堆
 * @param a 顺序表, 存储堆(无序表)和有序表
 * @param n 顺序表元素个数
 * @param s 待调整位置
 * @note 已知a[s...n-1]除a[s]外, 均满足大顶堆定义, 也就是说需要调整a[s]的位置, 使a[s...n-1]完全符合大顶堆定义
 */
void HeapAdjust(int a[], int n, int s)
{
	int rc = a[s]; // 待调整位置值

	// 2*s+1是s的左孩子, 2*s+2是右孩子 (根节点位置0)
	for(int j = 2*s + 1; j <= n; j *=2)
	{// 沿着a[s]较大孩子结点, 向下遍历并筛选(因为要调整, 只可能是待调整结点a[s]和较大孩子结点交换位置)

		// 求较大孩子结点, 并保持j为较大孩子结点在顺序表中的位置
		if(j < n-1 && a[j] < a[j+1])
		{// 结点j的左孩子比右孩子小
			++ j; // j为较大值的孩子结点下标(即右孩子)
		}

		if(rc >= a[j]) // rc比最大孩子结点大, 即已符合大堆特性, 不需要继续进行调整
			break;

		// 否则, rc比最大孩子结点j小, 需要交换结点s(父节点)和j(最大子结点)
		a[s] = a[j];

		s = j; // 更新rc值应在位置, 此处只更新rc应在位置
	}

	a[s] = rc; // 将rc值更新到最终所在位置
}


/**
 * 堆排序
 * @param a 顺序表a[0...n-1], 用于存储堆和已排序序列的物理结构
 * @param n 顺序表a的元素个数
 * @note 非递减序列对应大顶堆, 末尾元素位置n-1, 对应父结点位置(n-1)/2, 也是最后一个非叶子结点
 */
void HeapSort(int a[], int n)
{
	// 建堆(大顶堆), 从最后一个非叶子结点开始往前调整
	for(int i = (n-1)/2; i >=0; --i)
	{
		HeapAdjust(a, n, i); // 从结点i开始往下调整
	}

	// 输出堆顶并调整
	for(int i = n-1; i >= 0; --i)
	{
		Swap(&a[0], &a[i]); // 输出堆顶元素到顺序表末尾

		HeapAdjust(a, n, 0); // 从堆顶开始自上而下调整
	}
}

/**
 * 交换2个值
 * @param s [out] 指向第一个值的指针
 * @param t [out] 指向第二个值的指针
 * @return 交换结果
 * - -1 空指针
 * - 0 交换成功
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
 * 打印数组
 * @param a 指向数组的指针
 * @param n 数组元素个数
 * @note 从a[0...n-1]串口答应数组a的元素值
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
