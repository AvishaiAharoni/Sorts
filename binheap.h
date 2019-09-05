#ifndef BINHEAP_H_
#define BINHEAP_H_

#include <stddef.h> /* size_t */

#define SUCCESS 0
#define BT_FAIL 1
#define ERROR_MEMORY 1
#define MEMORY_ERROR NULL
#define NOT_FOUND 1

typedef struct binary_heap bheap_t;

/* to create a new binary heap, with a given cmp function */
bheap_t *BHeapCreate(int(*cmp)(const void *data1,const void *data2, void *param),
																	void *param);

/* to destroy a binary heap */
void BHeapDestroy(bheap_t *bh);

/* to insert to the heap a given data.
   for error in the inserting - returns ERROR_MEMORY.
   if success - returns SUCCESS.
   after the insert, there is a check to keep the rules of the heap */
int BHeapInsert(bheap_t *bh, void *data);

void *BHeapDeleteMin(bheap_t *bh);

/* to return the min number in the binary heap */
void *BHeapMin(const bheap_t *bh);

/* to return the number of the elements in the binary heap */
size_t BHeapSize(const bheap_t *bh);

/* to check if a given binary heap is empty. yes - 1 */
int BHeapIsEmpty(const bheap_t *bh);

/* to prune items from the heap by a given is_match function */
int BHeapPrune(bheap_t *bh, int(*is_match)(void *data, void *param), void *param);

#endif /* BINHEAP_H_ */
