/**
 * @file P22.c
 * @author Daniel Grew (0978547)
 * @brief This file contains code for question 2 part 2
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

int StringSearchHarspoolAlgorithm(char *pattern, char *text, int *shifts)
{
    // check if pattern or text is null
    if(!pattern || !text)
    {
        return ERROR;
    }

    int pattern_len = strlen(pattern);
    int text_len = strlen(text);
    int num_shifts = 0;
    int num_matches = 0;

    // create skip table
    char *shift_table = malloc(sizeof(int) * SHIFT_TABLE_LEN);
    // pre set all values in table to the length of the pattern
    for(int i = 0; i < SHIFT_TABLE_LEN; i++)
    {
        shift_table[i] = pattern_len;
    }

    // set all relevant values in shift table
    for(int j = 0; j < pattern_len - 1; j++)
    {
        int index = CharToIndex(pattern[j]);
        shift_table[index] = pattern_len - 1 - j;
    }

    // loop through the text to find the pattern
    int idx = pattern_len - 1;
    while(idx < text_len)
    {
        int matches = 0;
        // while matching
        while(matches < pattern_len && pattern[pattern_len - 1 - matches] == text[idx - matches])
        {
            matches += 1;
        }

        // check if num matches == pattern length
        if(matches == pattern_len)
        {
            num_matches++;
            idx += pattern_len;
        }
        // if not
        else{
            // increment the idx by the value in the harspool shift table
            idx += shift_table[CharToIndex(text[idx])];
        }

        num_shifts++;
    }

    free(shift_table);

    *shifts = num_shifts;
    return num_matches;
}

int CharToIndex(char c)
{
    if(c >= LOWER_A && c <= LOWER_Z)
    {
        return c - LOWER_A;
    }
    else if(c >= UPPER_A && c <= UPPER_Z)
    {
        return 26 + (c - UPPER_A);
    }
    else 
    {
        return NOT_FOUND;
    }
}
