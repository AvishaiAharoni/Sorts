#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdio.h>
#include "sorts.h"

/******************************************************************************/

static void SwapInt(int *a, int *b)
{
	int temp = 0;
	
	assert(NULL != a);
	assert(NULL != b);
	
	temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************/

int Partition(int *base, size_t low, size_t high, int(*cmp)(int num1, int num2))
{
	size_t i = 0;
	size_t j = 0;
	int pivot = 0;
	
	assert(NULL != base);
	assert(NULL != cmp);
	assert(low < high);
	
	pivot = base[high - 1];
	i = low;
	
	for (j = low; j < high - 1; ++j)
	{
		if (0 > cmp(base[j], pivot))
		{
			SwapInt(&base[j], &base[i]);
			++i;
		}
	}
	
	SwapInt(&base[i], &base[high - 1]);
	
	return (i);
}

/******************************************************************************/

void QuickSortAux(int *base, size_t low, size_t high, int(*cmp)(int num1, int num2))
{
	int pivot = 0;
	
	assert(NULL != base);
	assert(NULL != cmp);
	
	if (low < high)
	{
		pivot = Partition(base, low, high, cmp);

		QuickSortAux(base, low, pivot, cmp);
		QuickSortAux(base, pivot + 1, high, cmp);
	}
}

/******************************************************************************/

int QuickSort(int *base, size_t len, int(*cmp)(int num1, int num2))
{
	assert(NULL != base);
	assert(0 < len);
	assert(NULL != cmp);
	
	QuickSortAux(base, 0, len, cmp);
	
	return (0);
}
