#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <time.h> /* time */
#include <stdlib.h> /* rand, srand, qsort */

#include "sorts.h"

#define ARR_SIZE 5000LU
#define SIZE_ELEMENT sizeof(int)

int BubbleSortTest();
int InsertionSortTest();
int SelectionSortTest();
int CountingSortTest();
int RadixSortTest();
int MergeSortTest();
int QuickSortTest();

int main()
{
	int res = 0;
	
	res = BubbleSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}
	
	res = InsertionSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}

	res = SelectionSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}

	res = CountingSortTest();;
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}
	
	res = RadixSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}
	
	res = MergeSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}	
	
	res = QuickSortTest();
	if (0 != res)
	{
		printf("line: %d\n", res);
		
		return (1);
	}	
	
	return (0);
}

/******************************************************************************/

/* the compare function for qsort*/
int CmpQsort(const void *a, const void *b)
{
	if (*(int *)a > *(int *)b)
	{
		return (1);
	}
	
	if (*(int *)b > *(int *)a)
	{
		return (-1);
	}
	
	return (0);
}

/* the compare function for int */
int Cmp(int a, int b)
{
	return (CmpQsort((void *)&a, (void *)&b));
}

/******************************************************************************/

/* to init an arr for the sorts */
static void InitArr(int *arr, int *check, size_t size, size_t mod, int negative)
{
    size_t i = 0;
    time_t time_val = 0;
    
    srand((unsigned int)time(&time_val));
    
    for(i = 0 ; i < size ; ++i)
    {
        arr[i] = rand() % mod;
        if (0 == i % 7)
        {
        	arr[i] *= negative;
        }
        check[i] = arr[i];
/*        printf("base: %d	check: %d\n", arr[i], check[i]);*/
	}
}

/******************************************************************************/

/* to test the sorts aginst qsort of the system */
static int TestArr(int *arr, int *check, size_t size)
{
    size_t i = 0;
    
	qsort((void *)check, size, SIZE_ELEMENT, &CmpQsort);

    for (i = 0; i < size; ++i)
    {
        if (arr[i] != check[i])
        {
			printf("base: %d	check: %d\n", arr[i], check[i]);
			printf ("i = %lu\n", i);
			
/*        	return (1);*/
        }
/*		printf("base: %d	check: %d\n", arr[i], check[i]);*/
	
	}

	return (0);
}

/******************************************************************************/

/* to swap between 2 int numbers */
static void SwapInt(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/******************************************************************************/

/* to reverse an array */
static void Reverse(int *arr, size_t size)
{
	int *low = arr;
	int *high = arr + size -1;
	
	while (low < high)
	{
		SwapInt(low, high);
		++low;
		--high;
	}
}

/******************************************************************************/

/* the key_to_index function */
size_t KeyToIndex(int num, int param)
{
	return (num - param);
}

/******************************************************************************/

/* to find a nim / max in an array */
static void MinMaxInArr(int *arr, size_t len, int *min, int *max)
{
	size_t i = 1;
	
	*min = arr[0];
	*max = arr[0];
	
	for (i = 1; i < len; ++i)
	{
		if (arr[i] > *max)
		{
			*max = arr[i];
		}
		else if (arr[i] < *min)
		{
			*min = arr[i];
		}
	}
}

/******************************************************************************/

/* to return a sort array */
static void SortArr(int *arr, int *check, size_t len, int negative)
{
	size_t i = 0;
	int j = len / 2 * negative;
		
	for ( ; i < len ; ++i, ++j)
	{
		arr[i] = j;
		check[i] = j;
	}
}

/******************************************************************************/

/* to return a sort array */
static void OneValArr(int *arr, int *check, size_t len, int num)
{
	size_t i = 0;
		
	for ( ; i < len ; ++i)
	{
		arr[i] = num;
		check[i] = num;
	}
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* to test a given array with a function */
double TestArrWithFunc(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
					 			 int *base, size_t len,int (*cmp)(int num1, int num2))
{
	clock_t start = 0;
	clock_t end = 0;

	start = clock();
	
	name(base, len, cmp);
	
	end = clock();
	
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

/******************************************************************************/

/* to test a sort by regular array */
static int RegularCheck(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
		char *typefunc, int *arr, int *check, size_t len, int (*cmp)(int num1, int num2))
{
    printf("time of %s sort is: %f\n", typefunc,
    							TestArrWithFunc(name, arr, ARR_SIZE, Cmp));
   
	if (0 != TestArr(arr, check, ARR_SIZE))
	{
		printf("problem in regular %s sort\n", typefunc);
		
		return (1);
	}
	
	return (0);
}

/******************************************************************************/

/* to test a sort by reverse array */
static int ReverseCheck(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
		char *typefunc, int *arr, int *check, size_t len, int (*cmp)(int num1, int num2))
{
	Reverse(check, ARR_SIZE);
	Reverse(arr, ARR_SIZE);

    printf("time of reverse %s sort is: %f\n", typefunc,
    							TestArrWithFunc(&BubbleSort, arr, ARR_SIZE, &Cmp));
   
	if (0 != TestArr(arr, check, ARR_SIZE))
	{
		printf("problem in reverse %s sort\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test a sort by reverse array */
static int SortArrCheck(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
		char *typefunc, int *arr, int *check, size_t len, int (*cmp)(int num1, int num2))
{
	SortArr(arr, check, ARR_SIZE, -1);

    printf("time of sort %s sort is: %f\n", typefunc,
    							TestArrWithFunc(&BubbleSort, arr, ARR_SIZE, &Cmp));
   
	if (0 != TestArr(arr, check, ARR_SIZE))
	{
		printf("problem in sort %s sort\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test a sort by one val array */
static int OneValCheck(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
		char *typefunc, int *arr, int *check, size_t len, int (*cmp)(int num1, int num2))
{
	OneValArr(arr, check, ARR_SIZE, 15);
	
    printf("time of %s sort with one val is: %f\n", typefunc,
    							TestArrWithFunc(&BubbleSort, arr, ARR_SIZE, &Cmp));
   
	if (0 != TestArr(arr, check, ARR_SIZE))
	{
		printf("problem in %s sortwith one val\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test a sort by one cell array */
static int OneCellCheck(int (*name)(int *base, size_t len, int (*cmp)(int num1, int num2)),
										char *typefunc, int (*cmp)(int num1, int num2))
{
	int arr[1] = {5};
	int check[1] = {5};
	
    printf("time of %s sort with one cell is: %f\n", typefunc,
    							TestArrWithFunc(&BubbleSort, arr, 1LU, &Cmp));
    
	if (0 != TestArr(arr, check, 1))
	{
		printf("problem in %s sort with one cell\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* to test the bubble sort */
int BubbleSortTest()
{
    int arr[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "bubble";
    int res = 0;
    
    InitArr(arr, check, ARR_SIZE, 1000LU, -1);
        
    /* regular */
	res = RegularCheck(&BubbleSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* reverse */
	res = ReverseCheck(&BubbleSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* sort */
	res = SortArrCheck(&BubbleSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one val */
	res = OneValCheck(&BubbleSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one cell */
	res = OneCellCheck(&BubbleSort, typefunc, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	puts("");
	
	return (0);
}

/******************************************************************************/

/* to test the insertion sort */
int InsertionSortTest()
{
    int arr[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "insertion";
    int res = 0;
    
    InitArr(arr, check, ARR_SIZE, 1000LU, -1);
        
    /* regular */
	res = RegularCheck(&InsertionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* reverse */
	res = ReverseCheck(&InsertionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* sort */
	res = SortArrCheck(&InsertionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}

	/* one val */
	res = OneValCheck(&InsertionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one cell */
	res = OneCellCheck(&InsertionSort, typefunc, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}

	puts("");
	
	return (0);
}

/******************************************************************************/

/* to test the selection sort */
int SelectionSortTest()
{
    int arr[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "selection";
    int res = 0;
    
    InitArr(arr, check, ARR_SIZE, 1000LU, -1);
        
    /* regular */
	res = RegularCheck(&SelectionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* reverse */
	res = ReverseCheck(&SelectionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* sort */
	res = SortArrCheck(&SelectionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}

	/* one val */
	res = OneValCheck(&SelectionSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one cell */
	res = OneCellCheck(&SelectionSort, typefunc, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}

	puts("");
	
	return (0);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/* to test a given count array with a function */
double TestCountArrWithFunc(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
				int *dest, int *src, size_t len, int r_min, int r_max, int param, 
										size_t (*key_to_index)(int num, int param))
{
	clock_t start = 0;
	clock_t end = 0;

	start = clock();
	
	countfunc(dest, src, len, r_min, r_max, param, key_to_index);
	
	end = clock();
	
	return ((double)(end - start) / CLOCKS_PER_SEC);
}

/******************************************************************************/

/* to test regular count */
int RegularCount(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
			int *check, int *dest, int *src, size_t len, int r_min, int r_max, int param, 
							size_t (*key_to_index)(int num, int param), char *typefunc)
{
    printf("time of %s sort is: %f\n", typefunc,
    		TestCountArrWithFunc(countfunc, dest, src, len, r_min, r_max, param,
																key_to_index));

	if (0 != TestArr(dest, check, len))
	{
		printf("problem in regular %s sort\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test reverse count */
int ReverseCount(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
			int *check, int *dest, int *src, size_t len, int r_min, int r_max, int param, 
							size_t (*key_to_index)(int num, int param), char *typefunc)
{
    Reverse(src, len);
    Reverse(check, len);

    printf("time of reverse %s sort is: %f\n", typefunc,
    		TestCountArrWithFunc(countfunc, dest, src, len, r_min, r_max, param,
																key_to_index));

	if (0 != TestArr(dest, check, len))
	{
		printf("problem in reverse %s sort\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test sort count */
int SortCount(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
			int *check, int *dest, int *src, size_t len, int r_min, int r_max, int param, 
							size_t (*key_to_index)(int num, int param), char *typefunc)
{
    printf("time of %s sort with sort array is: %f\n", typefunc,
    		TestCountArrWithFunc(countfunc, dest, src, len, r_min, r_max, param,
																key_to_index));

	if (0 != TestArr(dest, check, len))
	{
		printf("problem in %s sort with sort array\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test count with one val */
int OneValCount(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
			int *check, int *dest, int *src, size_t len, int r_min, int r_max, int param, 
							size_t (*key_to_index)(int num, int param), char *typefunc)
{
	OneValArr(src, check, len, 18);
	
    printf("time of %s sort with one val is: %f\n", typefunc,
    		TestCountArrWithFunc(countfunc, dest, src, len, r_min, r_max, param,
																key_to_index));

	if (0 != TestArr(dest, check, len))
	{
		printf("problem in %s sort with one val\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test count with one cell */
int OneCellCount(int (*countfunc)(int *dest, const int *src, size_t len, 
			int r_min, int r_max, int param, size_t (*key_to_index)(int num, int param)),
							size_t (*key_to_index)(int num, int param), char *typefunc)
{
	int src1[2] = {5, 5};
	int dest1[2] = {5, 5};
	int check1[2] = {5, 5};
	
    printf("time of %s sort with two cells is: %f\n", typefunc,
    		TestCountArrWithFunc(countfunc, dest1, src1, 2LU, 5, 5, 5,
																key_to_index));

	if (0 != TestArr(dest1, check1, 2))
	{
		printf("problem in %s sort with two cells\n", typefunc);
		
		return (1);
	}

	return (0);
}

/******************************************************************************/

/* to test the count sort */
int CountingSortTest()
{
    int arr[ARR_SIZE] = {0};
    int dest[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "count";
    int res = 0;
    int min = 0;
    int max = 0;
    
    InitArr(arr, check, ARR_SIZE, 5000LU, -1);
	
   	MinMaxInArr(arr, ARR_SIZE, &min, &max);
   	
   	/* regular count */
	res = RegularCount(&CountingSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}
	
   	/* reverse count */
	res = ReverseCount(&CountingSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}
	
   	/* sort count */
	res = SortCount(&CountingSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

   	/* one val count */
	res = OneValCount(&CountingSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

   	/* one val count */
	res = OneCellCount(&CountingSort, &KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

	puts("");
	
	return (0);	
}


/******************************************************************************/

/* to test the radix sort */
int RadixSortTest()
{
    int arr[ARR_SIZE] = {0};
    int dest[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "radix";
    int res = 0;
    int min = 0;
    int max = 0;
    
    InitArr(arr, check, ARR_SIZE, 500LU, 1);
	
   	MinMaxInArr(arr, ARR_SIZE, &min, &max);
   	
   	/* regular radix */
	res = RegularCount(&RadixSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}
	
   	/* reverse radix */
	res = ReverseCount(&RadixSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}
	
   	/* sort radix */
	res = SortCount(&RadixSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

   	/* one val radix */
	res = OneValCount(&RadixSort, check, dest, arr, ARR_SIZE, min, max, min,
																&KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

   	/* one cell radix */
	res = OneCellCount(&RadixSort, &KeyToIndex, typefunc);
	if (0 != res)
	{
		return (__LINE__);
	}

	puts("");
	
	return (0);	
}

/******************************************************************************/

/* to test the merge sort */
int MergeSortTest()
{
    int arr[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "merge";
    int res = 0;
    
    InitArr(arr, check, ARR_SIZE, 1000LU, -1);
        
    /* regular */
	res = RegularCheck(&MergeSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* reverse */
	res = ReverseCheck(&MergeSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* sort */
	res = SortArrCheck(&MergeSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one val */
	res = OneValCheck(&MergeSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one cell */
	res = OneCellCheck(&MergeSort, typefunc, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	puts("");
	
	return (0);
}

/******************************************************************************/


/* to test the quick sort */
int QuickSortTest()
{
    int arr[ARR_SIZE] = {0};
    int check[ARR_SIZE] = {0};
    char *typefunc = "quick";
    int res = 0;
    
    InitArr(arr, check, ARR_SIZE, 1000LU, -1);
        
    /* regular */
	res = RegularCheck(&QuickSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* reverse */
	res = ReverseCheck(&QuickSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* sort */
	res = SortArrCheck(&QuickSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one val */
	res = OneValCheck(&QuickSort, typefunc, arr, check, ARR_SIZE, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	/* one cell */
	res = OneCellCheck(&QuickSort, typefunc, &Cmp);
	if (0 != res)
	{
		return (__LINE__);
	}
	
	puts("");
	
	return (0);
}

/******************************************************************************/
