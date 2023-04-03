/**
 * @file P21.c
 * @author Daniel Grew (0978547)
 * @brief this file contains the code for question 2 part 1
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

int StringSearchBruteForce(char *pattern, char *text, int *shifts)
{
    // make sure pattern is not null
    if(!pattern)
    {
        return ERROR;
    }

    // get the length of the pattern and text
    int pattern_len = strlen(pattern);
    int text_len = strlen(text);

    // starting from index 0 compare pattern against the text
    int shift_count = 0;
    int num_matches = 0;

    for(int i = 0; i < text_len - pattern_len; i++)
    {
        int j = 0;
        for(j = 0; j < pattern_len; j++)
        {
            // check if the character in the pattern matches the character in the text
            if(pattern[j] != text[i + j])
            {
                break;
            }
        }
        if(j == pattern_len)
        {
            num_matches++;
        }

        shift_count++;
    }

    *shifts = shift_count;
    return num_matches;
}
