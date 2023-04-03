/**
 * @file P12.c
 * @author Daniel Grew (0978547)
 * @brief This file contains the code for question 1 part 2
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

/**
 * @brief Algorithm to find the most number which occurs most in all intervals and the number of intervals
 *      it occurs in. Uses presorting algorithm
 * 
 * @param intervals 
 * @param array_size 
 * @param common_point 
 * @return int 
 */
int CommonPointPreSort(Interval *intervals, int array_size, int *common_point)
{
    if(!intervals || array_size < 0)
    {
        return ERROR;
    }

    // split the array of intervals up into two arrays of ints
    // allocate space for the two arrays
    int *lefts = malloc(sizeof(int) * array_size);
    int *rights = malloc(sizeof(int) * array_size);

    IntervalsToInts(intervals, array_size, lefts, rights);

    // sort the arrays with mergesort algorithm 
    MergeSort(lefts, array_size);
    MergeSort(rights, array_size);

    // retrieve the leftmost and rightmost points
    int leftmost = lefts[0];
    int rightmost = rights[array_size - 1];


    // loop over the numbers between the leftmost and rightmost points
    int num = 0;
    int count = 0;

    for(int i = leftmost + 1; i < rightmost; i++)
    {
        int num_count = 0;
        for(int j = 0; j < array_size; j++)
        {
            if(i > lefts[j])
            {
                num_count++;
            }
            if(i >= rights[j])
            {
                num_count--;
            }
        }

        if(num_count > count)
        {
            count = num_count;
            num = i;
        }
    }

    free(lefts);
    free(rights);

    *common_point = num;
    return count;
}

void IntervalsToInts(Interval *intervals, int array_size, int *dest_1, int *dest_2)
{
    if(!intervals || !dest_1 || !dest_2)
    {
        return;
    }

    // loop over the intervals array and load the values of the leftmost point (x1) to dest_1
    //      and the rightmost points (x2) into dest_2
    for(int i = 0; i < array_size; i++)
    {
        dest_1[i] = intervals[i].x1;
        dest_2[i] = intervals[i].x2;
    }
}

/**
 * @brief Simple mergesort algorithm used to sort the array of integers
 * 
 * @param array 
 * @param arr_size 
 */
void MergeSort(int *array, int arr_size)
{
    // base case of array size n = 1
    if(arr_size <= 1)
    {
        return;
    }
    // check if array is null
    if(!array)
    {
        return;
    }

    // calculate the midpoint
    int mid = floor(arr_size/2);

    // allocate size for two arrays 
    int *lower = malloc(sizeof(int) * mid);
    int *upper = malloc(sizeof(int) * (arr_size - mid));

    // copy the contents of array into lower and upper
    CopyArray(lower, array, 0, mid);
    CopyArray(upper, array, mid, arr_size);

    MergeSort(lower, mid);
    MergeSort(upper, (arr_size - mid));

    Merge(lower, mid, upper, (arr_size - mid), array, arr_size);

    // free the arrays
    free(lower);
    free(upper);
}

/**
 * @brief Merges two sorted arrays
 * 
 * @param lower 
 * @param lower_len 
 * @param upper 
 * @param upper_len 
 * @param array 
 * @param array_len 
 */
void Merge(int *lower, int lower_len, int *upper, int upper_len, int *array, int array_len)
{
    if(!lower || !upper || !array)
    {
        return;
    }
    int i = 0;
    int j = 0;
    int k = 0;

    while(i < lower_len && j < upper_len)
    {
        // if the lower array element at index i is less than element in upper at index j
        if(lower[i] <= upper[j])
        {
            array[k] = lower[i];
            i++;
        }
        else
        {
            // if the lower index is of a greater value than the value in the upper array
            array[k] = upper[j];
            j++;
        }
        k++;
    }
    // if the end of the sorted lower array has been reached
    if(i == lower_len)
    {
        // add rest of sorted upper index to the end of the sorted array
        for(int index = j; index < upper_len; index++)
        {
            array[k] = upper[index];
            k++;
        }
    }
    else
    {
        array[k] = lower[i];
        i++;
        k++;
        for(int index = i; index < lower_len; index++)
        {
            array[k] = lower[index];
            k++;
        }
    }
}

/**
 * @brief Simple function for copying one array's contents to anothers
 * 
 * @param dest 
 * @param src 
 * @param start 
 * @param end 
 */
void CopyArray(int *dest, int *src, int start, int end)
{
    if(!dest || !src)
    {
        return;
    }

    int index = 0;
    for(int i = start; i < end; i++)
    {
        dest[index] = src[i];
        index++;
    }
}
