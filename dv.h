#ifndef DV_H_

#define DV_H

typedef struct dynamic_vector dv_t;

#define SUC 0
#define FAIL 1

/* the function creates a new DV, by given size of element and the number
	of the elements */
dv_t *DVCreate(size_t num_of_items, size_t size_of_item);

/* to remove a DV */
void DVDestroy(dv_t *vector);

/* to return the size of the elements in the array */
size_t DVSize (const dv_t *vector);

/* to return the size of the array's capacity */
size_t DVCapacity(const dv_t *vector);

/* to return the item in given index from the DV */
void *DVGetItemAddress(const dv_t *vector, size_t item_index);

/* to increase the array by a given number.
	returns 0 for success and 1 for failiture */
int DVReserve(dv_t *vector, size_t new_capacity);

/* to insert a new item to the array.
	if there isn't place, calls a function to increase the size of the array
	for success returns 0, failiture - 1 */
int DVPushBack(dv_t *vector, const void *item_to_add);

/* to pop the last item from the array.
	if the array is NULL - doing nothing.
	if after the poping the size is half of the capacity, and if we cut 
	a quarter from the cpacity, it will be above the capacity that set - doing it.
	for success returns 0, failiture - 1 */
int DVPopBack(dv_t *vector);


#endif /* DV_H */
