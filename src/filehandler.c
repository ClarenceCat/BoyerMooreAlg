/**
 * @file filehandler.c
 * @author Daniel Grew (0978547)
 * @brief This file contains all of the code used for file handling in the assignment
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

/**
 * @brief Extracts intervals from file
 * 
 * @param filename 
 * @return Interval* 
 */
Interval *ReadQ1Data(char *filename, int *array_size)
{
    // make sure filename is not null
    if(!filename || strcmp(filename, EMPTY_STR) == 0)
    {
        return NULL;
    }

    // get the number of lines in the file
    int num_lines = FileLen(filename);
    
    // make sure there was no error
    if(num_lines == ERROR)
    {
        return NULL;
    }

    *array_size = num_lines;

    // extract information from the file
    return Q1ExtractData(filename, num_lines);
}

/**
 * @brief gets the length of a file (how many lines in the file are there?)
 * 
 * @param filename 
 * @return int 
 */
int FileLen(char *filename)
{
    // make sure the filename is not null
    if(!filename)
    {
        return ERROR;
    }

    int len = 0;
    // this will store the line that has been read from the file
    char line_tmp[Q1_MAX_LINE_LEN];

    // open file
    FILE *file = fopen(filename, READ);

    // if file is null return error
    if(!file)
    {
        return ERROR;
    }

    while(fgets(line_tmp, Q1_MAX_LINE_LEN, file))
    {
        if(strcmp(line_tmp, EMPTY_STR) != 0)
        {
            len++;
        }
    }


    // close file
    if (fclose(file) != 0)
    {
        return ERROR;
    }

    return len;
}

/**
 * @brief Extracts interval data from file
 * 
 * @param filename 
 * @param file_len 
 * @return Interval* 
 */
Interval *Q1ExtractData(char *filename, int file_len)
{
    // check if filename is null or file_len is invalid (<0)
    if(!filename || file_len < 0)
    {
        return NULL;
    }

    // allocate space for the set of intervals
    Interval *intervals = malloc(sizeof(Interval) * file_len );

    // open the file
    FILE *file = fopen(filename, READ);

    if(!file)
    {
        free(intervals);
        return NULL;
    }

    // set up temp string to hold values
    char tmp[Q1_MAX_LINE_LEN];

    int index = 0;

    // loop through file
    while(fgets(tmp, Q1_MAX_LINE_LEN, file))
    {
        int x1 = 0;
        int x2 = 0;

        int scanned = sscanf(tmp, "%d   %d", &x1, &x2);

        if(scanned == INT_PER_INTERVAL)
        {
            intervals[index].x1 = x1;
            intervals[index].x2 = x2;
            index++;
        }
    }

    //  close file
    if(fclose(file) != 0)
    {
        free(intervals);
        return NULL;
    }

    return intervals;
}

char *ReadQ2Data(char *filename)
{
    // make sure filename is not null
    if(!filename)
    {
        return NULL;
    }

    // find the number of characters total
    int len = Q2GetNumChars(filename);

    // check if error has occurred
    if(len == ERROR)
    {
        return NULL;
    }

    // allocate space for the text
    char *text = malloc(sizeof(char) * len);
    strcpy(text, EMPTY_STR);

    // loop through the file and append the content to the end of the string
    FILE *file = fopen(filename, READ);

    if(!file)
    {
        free(text);
        return NULL;
    }
    
    char tmp[Q2_MAX_LINE_LEN];
    while(fgets(tmp, Q2_MAX_LINE_LEN, file))
    {
        strcat(text, tmp);
    }

    fclose(file);
    return text;
}

int Q2GetNumChars(char *filename)
{
    // make sure filename is not null
    if (!filename)
    {
        return ERROR;   
    }
    
    // open the file
    FILE *file = fopen(filename, READ);

    // make sure file exists
    if(!file)
    {
        return ERROR;
    }

    // temp variable 
    char tmp[Q2_MAX_LINE_LEN];

    // read file counting the number of characters
    int num_chars = 0;

    while(fgets(tmp, Q2_MAX_LINE_LEN, file))
    {
        num_chars += strlen(tmp);
    }

    fclose(file);
    return num_chars;
}
