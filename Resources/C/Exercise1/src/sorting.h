

#ifndef LABORATORIO_ALGORITMI_2021_2022_SORTING_H
#define LABORATORIO_ALGORITMI_2021_2022_SORTING_H

//An array of any number of elements of any kind, ordered in non-descending order
//according to a specific precedence relation.
typedef struct _OrderedArray OrderedArray;

//It sorts an array using the insertion sort algorithm calling
// the binarySearch to optimize the sorting.
//It accepts as input a pointer to an array and the range
// to be sorted.
//The input parameters cannot be NULL or out of bounds of the
//  array.
void insertionSort(OrderedArray *ordered_array);

void quickSort(OrderedArray *orderedArray);


#endif //LABORATORIO_ALGORITMI_2021_2022_SORTING_H
