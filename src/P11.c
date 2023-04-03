/**
 * @file P11.c
 * @author Daniel Grew (0978547)
 * @brief This contains the code for question 1 part 1
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

/**
 * @brief Implementation of a brute force algorithm which finds the largest number of intervals which share a 
 *      common point
 * 
 * @param intervals 
 * @param common_point 
 * @return int 
 */
int CommonPointBruteForce(Interval *intervals, int array_size, int *common_point)
{
    // make sure intervals array is not null
    if(!intervals)
    {
        return ERROR;
    }

    // find max and min points
    int min = intervals[0].x1;
    int max = intervals[0].x2;
    for(int i = 0; i < array_size; i++)
    {
        if(intervals[i].x1 < min)
        {
            min = intervals[i].x1;
        }
        else if(intervals[i].x2 > max)
        {
            max = intervals[i].x2;
        }
    }


    // loop from min to max, checking every interval to see if the number is in the interval
    int num = 0;
    int count = 0;

    for(int j = min + 1; j < max; j++)
    {
        int num_count = 0;
        // loop over array of intervals
        for(int k = 0; k < array_size; k++)
        {
            if(intervals[k].x1 < j && j < intervals[k].x2)
            {
                num_count++;
            }
        }

        // check if the number of occurances within the intervals is greater than the 
        //      currently recorded greatest number of occurances
        if(num_count > count)
        {
            count = num_count;
            num = j;
        }
    }

    *common_point = num;

    return count;
}
