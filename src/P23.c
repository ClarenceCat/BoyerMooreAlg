/**
 * @file P23.c
 * @author Daniel Grew (0978547)
 * @brief This file contains the code for question 2 part 3
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

int StringSearchBoyerMooreAlgorithm(char *pattern, char *text, int *shifts)
{
    // check if pattern or text are null
    if(!pattern || !text)
    {
        return ERROR;
    }

    // get the lengths of the pattern and text
    int pattern_len = strlen(pattern);
    int text_len = strlen(text);

    // construct the bad symbol shift
    char *bad_symbol_shift_table = malloc(sizeof(char) * SHIFT_TABLE_LEN);

    // set up the bad symbol shift table in the same way we did for the Harspool algorithm function
    for(int i = 0; i < SHIFT_TABLE_LEN; i++)
    {
        bad_symbol_shift_table[i] = pattern_len;
    }

    // set all relevant values in shift table
    for(int j = 0; j < pattern_len - 1; j++)
    {
        int index = CharToIndex(pattern[j]);
        bad_symbol_shift_table[index] = pattern_len - 1 - j;
    }

    // set up good suffix table
    int *good_suffix_shift_table = ConstructGoodSuffixTable(pattern, pattern_len);

    if(!good_suffix_shift_table)
    {
        free(bad_symbol_shift_table);
        return ERROR;
    }

    // loop through the text to find all occurances of the pattern 
    int num_matches = 0;
    int num_shifts = 0;

    int idx = pattern_len - 1;
    while(idx < text_len)
    {
        int matches = 0;
        // while matching
        while(matches < pattern_len && pattern[pattern_len - 1 - matches] == text[idx - matches])
        {
            matches += 1;
        }

        if(matches == pattern_len)
        {
            num_matches++;
            idx += pattern_len;
            num_shifts++;
            continue;
        }

        if(matches == 0)
        {
            idx += max(bad_symbol_shift_table[CharToIndex(text[idx])], 1);
        }
        else 
        {
            // get d_1
            int d_1 = max(bad_symbol_shift_table[CharToIndex(text[idx])], 1);

            int d_2 = good_suffix_shift_table[matches];

            // find out which shift to use
            int d = max(d_1, d_2);

            // increment the idx by the value in the harspool shift table
            idx += d;
        }

        num_shifts++;
    }

    free(bad_symbol_shift_table);
    free(good_suffix_shift_table);

    *shifts = num_shifts;
    return num_matches;
}

/**
 * @brief Constructs the good suffix table used in the Boyer-Moore Algorithm
 * 
 * @param pattern 
 * @param pattern_len 
 * @return int* 
 */
int *ConstructGoodSuffixTable(char *pattern, int pattern_len)
{
   // first case - check for another occurance of suffix in pattern
    int *suf_tbl = malloc(sizeof(int) * pattern_len);

    // initialize the list
    for(int initialize_idx = 0; initialize_idx < pattern_len; initialize_idx++)
    {
        suf_tbl[initialize_idx] = pattern_len;
    }

    // loop from right to left (note suffix_len = pattern_len - idx)
    for(int idx = pattern_len - 1; idx >= 0; idx--)
    {
        int k_val = pattern_len - idx;
        for(int cur = 0; cur < pattern_len && (cur + k_val < pattern_len - k_val); cur++)
        {
            if(strncmp(&pattern[idx], &pattern[cur], k_val) == 0)
            {
                // set suf_tbl[k] to the shift amount
                suf_tbl[pattern_len - idx] = pattern_len - (cur + k_val);
            }
        }
    }

    // the second case : the longest matching prefix
    for(int l_val = 1; l_val < pattern_len; l_val++)
    {
        // loop through pattern from 0 -> l_val
        for(int m = 0; m < l_val; m++)
        {
            // compare last m + 1 characters to the first m + 1 characters
            if(strncmp(&pattern[0], &pattern[pattern_len - m - 1], m + 1) == 0)
            {
                if(suf_tbl[l_val] > pattern_len - (m + 1))
                {
                    suf_tbl[l_val] = pattern_len - (m + 1);
                    break;
                }
            }
        }
    }

    return suf_tbl;
}

/**
 * @brief finds the maximum between two integers
 * 
 * @param n1 
 * @param n2 
 * @return int 
 */
int max(int n1, int n2)
{
    if(n1 > n2)
    {
        return n1;
    }
    else 
    {
        return n2;
    }
}



