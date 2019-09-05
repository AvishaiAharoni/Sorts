#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

#include "dv.h"

#define MULTI 2
#define DEVIDE 0.75

static size_t g_capacity = 0;

struct dynamic_vector
{
    size_t item_size;
    size_t capacity;
    size_t size;
    void *array;
};

/* the function creates a new DV, by given size of element and the number
	of the elements */
dv_t *DVCreate(size_t num_of_items, size_t size_of_item)
{
	/* to create the dv */
    dv_t *new_dv = (dv_t *)malloc(sizeof(dv_t));
    if (NULL == new_dv)
    {
        return (NULL);
    }
    
    /* checking if either num_of_items or size_of_item bigger than 0 */
	assert((num_of_items > 0) && (size_of_item > 0));

    /* to create the array */    
    new_dv->array = malloc(num_of_items * size_of_item);
    if (NULL == new_dv->array)
    {
    	free(new_dv); new_dv = NULL;
    	
        return (NULL); 
    }
	
	/* initializing the values to the fields */
    new_dv->item_size = size_of_item;
    new_dv->capacity = num_of_items;
    new_dv->size = 0 ;
    
    /* store the num_of_items value in the global variable */
	g_capacity = num_of_items;
    
    return (new_dv);
}

/* the function realoc the array, by given size to increase (or dicrease).
	returns 1 for success, and 0 for failiture */
static int DVAddToArray(size_t new_capacity, dv_t *my_dv)
{
    /* to create the new array */    
    void *new_array = realloc(my_dv->array, my_dv->item_size * new_capacity);
    if (NULL == new_array)
    {
        return (0);
    }
    
	/* initializing the update values to the fields */
    my_dv->array = new_array;
    my_dv->capacity = new_capacity;
    if (new_capacity < my_dv->size)
    {
    	my_dv->size = new_capacity;
    }
    
    return (1);
}

/* to increase the array by a given number.
	returns 0 for success and 1 for failiture */
int DVReserve(dv_t *vector, size_t new_capacity)
{
	int success = 0;
	
	/* checking that vector isn't NULL and the new_capacity is bigger than 0 */
	assert((vector != NULL) && (new_capacity > 0));
	
	success = DVAddToArray(new_capacity, vector);
	
	/* updates the value to the global varables */
	if (1 == success)
	{
		g_capacity = vector->capacity * success;
	}
	
	return (!(success));
}

/* to insert a new item to the array.
	if there isn't place, calls a function to increase the size of the array
	for success returns 0, failiture - 1 */
int DVPushBack(dv_t *vector, const void *item_to_add)
{
	int succ_add = 0;
	
	assert((vector != NULL) && (item_to_add != NULL));
	
	/* if there isn't place to insert a new item */
	if (vector->size == vector->capacity)
	{
		/* to add new cells to the array */
		succ_add = DVAddToArray(vector->size * MULTI, vector);
		if (0 == succ_add)
		{
			return (FAIL);
		}
	}
	
	/* to enter the new item to the array */
	memcpy(((char*)vector->array + vector->size * vector->item_size ), 
			item_to_add, vector->item_size);
	++vector->size;
			
	return (SUC);
}

/* to pop the last item from the array.
	if the array is NULL - doing nothing.
	if after the poping the size is half of the capacity, and if we cut 
	a quarter from the cpacity, it will be above the capacity that set - doing it.
	for success returns 0, failiture - 1 */
int DVPopBack(dv_t *vector)
{
	assert(vector != NULL);
	
	if (0 == vector->size)
	{
		return (SUC);
	}
	
	/* decreases the array */
	--vector->size;
	
	/* to check whether after the poping the size is half of the capacity,
		and if we cut a quarter from the cpacity,
		it will be above the capacity that set - doing it. */
	if ((vector->size < (vector->capacity / MULTI)) && 
		((vector->capacity * DEVIDE) > g_capacity))
	{
		DVAddToArray(vector->capacity * DEVIDE, vector);
	}
	
	return (SUC);
}

/* to remove a DV */
void DVDestroy(dv_t *vector)
{
	assert(vector != NULL);
	
    free(vector->array); vector->array = NULL;
    free(vector); vector = NULL;
}

/* to return the size of the elements in the array */
size_t DVSize(const dv_t *vector)
{
    return (vector->size);
}

/* to return the size of the array's capacity */
size_t DVCapacity(const dv_t *vector)
{
    return (vector->capacity);
}

/* to return the item in given index from the DV */
void *DVGetItemAddress(const dv_t *vector, size_t item_index)
{
	/* to check if the DV is not NULL */
    assert(vector != NULL);
    
    if (item_index > vector->size)
    {
    	return (NULL);
    }
    
    return ((char *) vector->array + (vector->item_size * item_index));
}
