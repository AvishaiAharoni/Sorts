#include <stdlib.h> /* malloc, realoc, free */
#include <assert.h> /* assert */

#include "dv.h"
#include "binheap.h"

#define BH_INIT_NUM 7
#define ROOT_INDEX 0

/******************************************************************************/

struct binary_heap
{
    dv_t *d_vector;
	int(*cmp)(const void *data1, const void *data2, void *param);
	void *param;
};

/******************************************************************************/

/* help function to swap two pointers */
static void SwapData(void **a, void **b)
{
	void *temp = NULL;
	
	assert(NULL != *a);
	assert(NULL != *b);
	
	temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************/

/* help function */
static size_t GetMaxIdx(bheap_t *bh)
{
	assert(NULL != bh);
	
	return (BHeapSize(bh) - 1);
}

/******************************************************************************/

/* help function */
static size_t GetParentIdx(size_t idx)
{
	assert(0 <= idx);

	return ((idx - 1) / 2);
}

/******************************************************************************/

/* help function */
static size_t GetSonIdx(size_t idx, size_t side)
{
	assert(0 <= idx);

	return (idx * 2 + side);
}

/******************************************************************************/

/* help function */
static void *GetDataFromIdx(dv_t *dv, size_t idx)
{
	return (*(void **)DVGetItemAddress(dv, idx));
}

/******************************************************************************/

/* help function */
static int BHCompare(bheap_t *bh, size_t idx1, size_t idx2)
{
   return (bh->cmp(GetDataFromIdx(bh->d_vector, idx1),
   			GetDataFromIdx(bh->d_vector, idx2),
			bh->param));
}

/******************************************************************************/

/* help function to arrange the heap bottom up */
static void HeapifyUp(bheap_t *bh)
{
	size_t idx = 0;
	
	assert(NULL != bh);
	assert(NULL != bh->cmp);

	idx = GetMaxIdx(bh);
	
	while ((ROOT_INDEX != idx) && (0 > BHCompare(bh, idx, GetParentIdx(idx))))
	{
		SwapData(DVGetItemAddress(bh->d_vector, idx),
				(DVGetItemAddress(bh->d_vector, GetParentIdx(idx))));
				
		idx = GetParentIdx(idx);
	}
}

/******************************************************************************/

/* help function */
static size_t FindMinSon(bheap_t *bh, size_t data_index)
{
	size_t num_of_elements = 0;
	size_t left = 0;
	size_t right = 0;
	size_t min_val_idx = 0;	
	
	assert(NULL != bh);
	assert(NULL != bh->cmp);
	
	num_of_elements = DVSize(bh->d_vector);
	min_val_idx = data_index;
	
	left = GetSonIdx(data_index, 1);
	right = GetSonIdx(data_index, 2);
	
	if ((left < num_of_elements) && (0 < BHCompare(bh, min_val_idx, left)))
	{
		min_val_idx = left;
	}
	
	if ((right < num_of_elements) && (0 < BHCompare(bh, min_val_idx, right)))
	{
		min_val_idx = right;
	}
	
	return (min_val_idx);
}

/******************************************************************************/

/*help function to arrange the heap top down */
static void HeapifyDown(bheap_t *bh, size_t data_index)
{
	size_t min_val_idx = 0;	

	assert(NULL != bh);
	assert(NULL != bh->cmp);
	
	min_val_idx = FindMinSon(bh, data_index);
		
	if (min_val_idx != data_index)
	{
		SwapData(DVGetItemAddress(bh->d_vector, data_index),
				(DVGetItemAddress(bh->d_vector, min_val_idx)));
				
		HeapifyDown(bh, min_val_idx);
	}
}

/******************************************************************************/

/* help function to erase a value in a given address in the heap.
   after deleting - the function arranges the heap again */
static void BHErase(bheap_t *bh, size_t idx1, size_t idx2)
{
	assert(NULL != bh);
	assert(idx1 <= idx2);

	SwapData(DVGetItemAddress(bh->d_vector, idx1),
			(DVGetItemAddress(bh->d_vector, idx2)));

	DVPopBack(bh->d_vector);
	
	HeapifyDown(bh, idx1);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* to create a new binary heap, with a given cmp function */
bheap_t *BHeapCreate(int(*cmp)(const void *data1,const void *data2, void *param),
																	void *param)
{
	bheap_t *new_bheap = NULL;

	assert(NULL != cmp);

	new_bheap = (bheap_t *)malloc(sizeof(bheap_t));
	if (NULL == new_bheap)
	{
		return (MEMORY_ERROR);
	}

	new_bheap->d_vector = DVCreate(BH_INIT_NUM, sizeof(void *));
	if (NULL == new_bheap->d_vector)
	{
		free (new_bheap); new_bheap = NULL;
		
		return (MEMORY_ERROR);
	}
	
	new_bheap->cmp = cmp;
	new_bheap->param = param;
	
	return (new_bheap);
}

/******************************************************************************/

/* to destroy a binary heap */
void BHeapDestroy(bheap_t *bh)
{
	assert(NULL != bh);

	DVDestroy(bh->d_vector); bh->d_vector = NULL;
	free(bh); bh = NULL;
}

/******************************************************************************/

/* to insert to the heap a given data.
   for error in the inserting - returns ERROR_MEMORY.
   if success - returns SUCCESS.
   after the insert, there is a check to keep the rules of the heap */
int BHeapInsert(bheap_t *bh, void *data)
{
	assert(NULL != bh);
	assert(NULL != bh->cmp);
	assert(NULL != data);
	
	if (1 == DVPushBack(bh->d_vector, &data))
	{
		return (ERROR_MEMORY);
	}

	HeapifyUp(bh);

	return (SUCCESS);
}

/******************************************************************************/

/* to return the min number in the binary heap */
void *BHeapMin(const bheap_t *bh)
{
	assert(NULL != bh);

	return (GetDataFromIdx(bh->d_vector, ROOT_INDEX));
}

/******************************************************************************/

/* to return the number of the elements in the binary heap */
size_t BHeapSize(const bheap_t *bh)
{
	assert(NULL != bh);

	return (DVSize(bh->d_vector));
}

/******************************************************************************/

/* to check if a given binary heap is empty. yes - 1 */
int BHeapIsEmpty(const bheap_t *bh)
{
	assert(NULL != bh);

	return (0 == BHeapSize(bh));
}

/******************************************************************************/

/* to delete the min value in the heap.
   after deleting - the function arranges the heap again.
   returns the data of the deleted item, and if the heap is empty - returns NULL */
void *BHeapDeleteMin(bheap_t *bh)
{
	void *data = NULL;
	
	assert(NULL != bh);
	assert(NULL != bh->cmp);

	if (0 == BHeapSize(bh))
	{
		return (NULL);
	}
	
	data = GetDataFromIdx(bh->d_vector, ROOT_INDEX);

	BHErase(bh, ROOT_INDEX, GetMaxIdx(bh));

	return (data);
}

/******************************************************************************/

/* to prune items from the heap by a given is_match function */
int BHeapPrune(bheap_t *bh, int(*is_match)(void *data, void *param), void *param)
{
	size_t idx = 0;
	int flag = 0;
	
	assert(NULL != bh);
	assert(NULL != is_match);
	
	while (idx < BHeapSize(bh))
	{	
		if (1 == is_match(GetDataFromIdx(bh->d_vector, idx), param))
		{
			BHErase(bh, idx, GetMaxIdx(bh));
			
			flag = 1;
		}
		else
		{
			++idx;
		}
	}
	
	return ((1 == flag) ? SUCCESS : NOT_FOUND);
}

/******************************************************************************/
