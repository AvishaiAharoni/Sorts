#ifndef SORT_H
#define SORT_H

int BubbleSort(int *base, size_t len, int(*cmp)(int num1, int num2));

int InsertionSort(int *base, size_t len, int(*cmp)(int num1, int num2));

int SelectionSort(int *base, size_t len, int(*cmp)(int num1, int num2));

int CountingSort(int *dest, const int *src, size_t len, int r_min, int r_max, int param,
									size_t (*key_to_index)(int num, int param));
							
int RadixSort(int *dest, const int *src, size_t len, int r_min, int r_max, int param, 
									size_t (*key_to_index)(int num, int param));

int MergeSort(int *base, size_t len, int(*cmp)(int num1, int num2));

int HeapSort(int *src, int *dest ,size_t len,
             int(*cmp)(const void *data1, const void *data2, void *param),
             void *param);

int QuickSort(int *base, size_t len, int(*cmp)(int num1, int num2));	
									
#endif /* SORT_H */
