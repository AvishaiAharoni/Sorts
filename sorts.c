#include <assert.h> /* assert */
#include <string.h> /* memmove */
#include <stdlib.h> /* malloc, free */

#include "sorts.h"

/* help function to swap between 2 int numbers */
static void SwapInt(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************/

/* sort by loop over the array and compare every 2 elements.
   if the first is bigger than the second - the function does a swap.
   if in a whole run there wasn't a swap - means that the array is sorted */
int BubbleSort(int *base, size_t len, int(*cmp)(int num1, int num2))
{
	size_t j = 0;
	size_t i = 0;
	int had_changes = 1;
	
	assert(NULL != base); 
	assert(0 < len);
	assert(NULL != cmp);

	for (i = 0; ((i < len) && (1 == had_changes)); ++i)
	{
		had_changes = 0;
		for (j = 0; j < len - i - 1; ++j)
		{
			if (0 < cmp(base[j], base[j + 1]))
			{
				SwapInt(&base[j], &base[j + 1]);
				had_changes = 1;
			}
		}
	}
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

static int FindFirstNonBiggerPos(int *arr, size_t len, int val,
													int(*cmp)(int num1, int num2))
{
	int j = 0;
	
	for (j = 0; (j < len) && (0 < cmp(val, arr[j])); ++j)
		;
	
	return (j);
}

/******************************************************************************/

static void InsertAtPos(int *arr, size_t len_before_insertion, 
												int insertion_idx, int to_insert)
{
	memmove(&arr[insertion_idx + 1], &arr[insertion_idx], 
			(len_before_insertion - insertion_idx) * sizeof(int));
			
	arr[insertion_idx] = to_insert;
}

/******************************************************************************/

/* a sort by by the insertion algorithm */
int InsertionSort(int *base, size_t len, int(*cmp)(int num1, int num2))
{
	int to_insert = 0;
	size_t num_sorted = 1;
	size_t insertion_idx = 0;
	
	assert(NULL != base); 
	assert(0 < len);
	assert(NULL != cmp);

	for (num_sorted = 1; num_sorted < len; ++num_sorted)
	{
		to_insert = base[num_sorted];
		insertion_idx = FindFirstNonBiggerPos(base, len, to_insert, cmp);
		
		InsertAtPos(base, num_sorted, insertion_idx, to_insert);
	}
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

static size_t FindSmallest(int *arr, size_t len, int smallest_idx, 
													int(*cmp)(int num1, int num2))
{
	size_t i = 0;
	
	for (i = smallest_idx; i < len; ++i)
	{
		if (0 < cmp(arr[smallest_idx], arr[i]))
		{
			smallest_idx = i;
		}
	}
	
	return (smallest_idx);
}

/******************************************************************************/

/* a sort by finding the smallest element in the array,
   and putting it in the first place.
   then finding the new smallest, etc. */   
int SelectionSort(int *base, size_t len, int(*cmp)(int num1, int num2))
{

	int smallest_idx = 0;
	size_t i = 0;
		
	assert(NULL != base); 
	assert(0 < len);
	assert(NULL != cmp);

	for (i = 0; i < len - 1; ++i)
	{
		smallest_idx = i;
		
		smallest_idx = FindSmallest(base, len, smallest_idx, cmp);
		
		SwapInt(&base[i], &base[smallest_idx]);
	}
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

static void InitCountLUT(const int *src, int *arr_count, size_t len, int param, 
										size_t (*key_to_index)(int num, int param))
{
	size_t i = 0;
	size_t idx = 0;
	
	for (i = 0; i < len; ++i)
	{
		idx = (key_to_index(src[i], param));
		++arr_count[idx];
	}
}

/******************************************************************************/

static void SumCurrAndPrevInArray(int *arr_count, size_t range)
{
	size_t i = 1;
	
	for (i = 1; i < range; ++i)
	{
		arr_count[i] += arr_count[i - 1];
	}
}

/******************************************************************************/

static void InitDestArr(int *dest, const int *src, int *arr_count, size_t len, int param,
										size_t (*key_to_index)(int num, int param))
{
	size_t i = len;
	size_t idx_pos = 0;
	
	for ( ; i > 0; --i)
	{
		idx_pos = (key_to_index(src[i - 1], param));

		dest[arr_count[idx_pos] - 1] = src[i - 1];
		--arr_count[idx_pos];
	}
}

/******************************************************************************/

int CountingSort(int *dest, const int *src, size_t len, int r_min, int r_max, int param,
									size_t (*key_to_index)(int num, int param))
{
	int *arr_count_pos = NULL;
	int *arr_count = NULL;
	size_t range = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	assert(0 < len);
	assert(r_max >= r_min);
	assert(NULL != key_to_index);

	range = r_max - r_min + 1;
	arr_count_pos = (int *)calloc(range, sizeof(int));
	if (NULL == arr_count_pos)
	{
		return (1);
	}
	
	arr_count = arr_count_pos;
	
	InitCountLUT(src, arr_count, len, param, key_to_index);
		
	SumCurrAndPrevInArray(arr_count, range);
	
	InitDestArr(dest, src, arr_count, len, param, key_to_index);
	
	free(arr_count_pos);
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/

size_t KeyToIndexForRadix(int num, int param)
{
	return ((num / param) % 10);
}

/******************************************************************************/

size_t MaxNum(const int *src, size_t len)
{
	size_t i = 1;
	size_t max_num = src[0];
	
	for (i = 1; i < len; ++i)
	{
		if (max_num < src[i])
		{
			max_num = src[i];
		}
	}
	
	return (max_num);
}

/******************************************************************************/

void InitSrcByDest(int *src_for_sort, const int *src, size_t len)
{
	memcpy(src_for_sort, src, sizeof(int) * len);
}

/******************************************************************************/

int RadixSort(int *dest, const int *src, size_t len, int r_min, int r_max, int param, 
									size_t (*key_to_index)(int num, int param))
{
	int *src_for_sort = NULL;
	size_t max_num = 0;
	size_t param_to_func = 1;

	src_for_sort = (int *)calloc(len, sizeof(int));
	if (NULL == src_for_sort)
	{
		return (1);
	}

	assert(NULL != dest);
	assert(NULL != src);
	assert(0 < len);
	assert(r_max >= r_min);
	assert(NULL != key_to_index);

	max_num = MaxNum(src, len);

	InitSrcByDest(src_for_sort, src, len);
	
	while (0 < max_num)
	{
		CountingSort(dest, src_for_sort, len, 0, 9, param_to_func, &KeyToIndexForRadix);

		InitSrcByDest(src_for_sort, dest, len);
		
		param_to_func *= 10;
		max_num /= 10;
	}

	free(src_for_sort);

	return (0);
}
