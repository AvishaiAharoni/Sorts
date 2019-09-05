#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdlib.h> /* malloc, free */

#include "sorts.h"
#include "binheap.h"
#include "dv.h"

int HeapSort(int *src, int *dest ,size_t len,
             int(*cmp)(const void *data1, const void *data2, void *param),
             void *param)
{
	bheap_t *bh = NULL;
	size_t i = 0;
	int res = 0;
	
	assert(NULL != src);
	assert(NULL != dest);
	assert(NULL != cmp);
	assert(0 < len);
	
	bh = BHeapCreate(cmp, param);
	if (NULL == bh)
	{
		return (ERROR_MEMORY);
	}
	
	for (i = 0; i < len; ++i)
	{
		res = BHeapInsert(bh, (void *)&src[i]);
		if (ERROR_MEMORY == res)
		{
			BHeapDestroy(bh); bh = NULL;
			
			return (ERROR_MEMORY);
		}
	}
	
	for (i = 0; i < len; ++i)
	{
		dest[i] = *(int *)BHeapDeleteMin(bh);
	}
	
	BHeapDestroy(bh); bh = NULL;
	
	return (SUCCESS);
}


