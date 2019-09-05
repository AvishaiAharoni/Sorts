#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */

#include "sorts.h"

/******************************************************************************/

static void ArrangeTheRestOfTheData(int *arr_merge, int *base, size_t merge_idx,
						size_t start_idx, size_t half, size_t end, size_t half_idx)
{
	/* if left from the start */
	memcpy((void *)(arr_merge + merge_idx), (void *)(base + start_idx),
											sizeof(int) * (half - start_idx + 1));
	
	
	/* if left from the end */	
	memcpy((void *)(arr_merge + merge_idx), (void *)(base + half_idx),
											sizeof(int) * (end - half_idx + 1));
}

/******************************************************************************/

/* copying to the base */
static void CopyBack(int *base, int *arr_merge, size_t start, size_t end)
{
	memcpy((void *)(base + start), (void *)arr_merge, sizeof(int) * (end - start + 1));
}


/******************************************************************************/

static void Merge(int *base, size_t start, size_t half, size_t end, int *arr_merge,
													int(*cmp)(int num1, int num2))
{
	size_t start_idx = start;
	size_t half_idx = half + 1;
	size_t merge_idx = 0;

	while ((start_idx <= half) && (half_idx <= end))
	{
		if (0 <= cmp(base[half_idx], base[start_idx]))
		{
			arr_merge[merge_idx] = base[start_idx];
			++start_idx;
		}
		else
		{
			arr_merge[merge_idx] = base[half_idx];
			++half_idx;
		}
		++merge_idx;
	}
	
	ArrangeTheRestOfTheData(arr_merge, base, merge_idx, start_idx, half, end, half_idx);
	
	/* copying to the base */
	CopyBack(base, arr_merge, start, end);
}

/******************************************************************************/

static void Div(int *base, size_t start, size_t end, int *arr_merge,
													int(*cmp)(int num1, int num2))
{
	size_t half = 0;
		
	assert(NULL != cmp);

	if (start < end)
	{	
		half = (end + start) / 2;
		Div(base, start, half, arr_merge, cmp);
		Div(base, half + 1, end, arr_merge, cmp);
		Merge(base, start, half, end, arr_merge, cmp);
	}
}

/******************************************************************************/

int MergeSort(int *base, size_t len, int(*cmp)(int num1, int num2))
{
	int *arr_merge = NULL;
	
	assert(NULL != base);
	assert(0 < len);
	assert(NULL != cmp);

	arr_merge = (int *)malloc(sizeof(int) * (len));
	if (NULL == arr_merge)
	{
		return (1);
	}

	Div(base, 0, len - 1, arr_merge, cmp);

	free(arr_merge);

	return (0);
}
