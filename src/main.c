/**
 * @file main.c
 * @author Daniel Grew (0978547)
 * @brief This file contains the main function which runs the code for all of the questions in the assignment
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment3.h"

int main(int argc, char **argv)
{
    // get the user input
    printf("Please enter the name of the file containing the interval data \n");
    char *input = GetUserInput();
    if(input == NULL)
    {
        return ERROR;
    }

    int arr_len = 0;
    Interval *intervals = ReadQ1Data(input, &arr_len);

    if(intervals == NULL)
    {
        printf("error \n");
        return ERROR;
    }

    int common_point = 0;

    long int Q1P1T1_pre = CurTime();
    int num_intervals = CommonPointBruteForce(intervals, arr_len, &common_point);
    long int Q1P1T1_post = CurTime();

    printf("A Brute Force Program for finding the max number of intervals\n");
    printf("The maximum number of intervals: %d\n", num_intervals);
    printf("The intervals include the point: %d\n", common_point);
    printf("Time for finding the maximum number: %ld(ms)\n", (Q1P1T1_post - Q1P1T1_pre));

    long int Q1P2_pre = CurTime();
    int intervals_presort = CommonPointPreSort(intervals, arr_len, &common_point);
    long int Q1P2_post = CurTime();

    printf("A PreSort Program for finding the max number of intervals\n");
    printf("The maximum number of intervals: %d\n", intervals_presort);
    printf("The intervals include the point: %d\n", common_point);
    printf("Time for finding the maximum number: %ld(ms)\n", (Q1P2_post - Q1P2_pre));

    free(intervals);
    free(input);

    // ==============================
    // read file into text string

    char *text = ReadQ2Data(Q2_FILE_NAME);
    if(!text)
    {
        printf("Error reading file %s \n", Q2_FILE_NAME);
        return ERROR;
    }

    // get the user to input a pattern
    printf("A Brute force program for string search\n");
    printf("Enter a pattern: ");
    char *pattern = GetUserInput();

    int shifts = 0;
    long int Q2P1_pre = CurTime();
    int matches = StringSearchBruteForce(pattern, text, &shifts);
    long int Q2P1_post = CurTime();

    printf("Count: %d\n", matches);
    printf("Shifts: %d\n", shifts);
    printf("Execution Time: %ld(ms)\n", (Q2P1_post - Q2P1_pre));
    printf("\n");

    long int Q2P2_pre = CurTime();
    matches = StringSearchHarspoolAlgorithm(pattern, text, &shifts);
    long int Q2P2_post = CurTime();

    printf("Count: %d\n", matches);
    printf("Shifts: %d\n", shifts);
    printf("Execution Time: %ld(ms)\n", (Q2P2_post - Q2P2_pre));
    printf("\n");

    long int Q2P3_pre = CurTime();
    matches = StringSearchBoyerMooreAlgorithm(pattern, text, &shifts);
    long int Q2P3_post = CurTime();

    printf("Count: %d\n", matches);
    printf("Shifts: %d\n", shifts);
    printf("Execution Time: %ld(ms)\n", (Q2P3_post - Q2P3_pre));
    printf("\n");

    // RunTests(text);
    // GetMetrics(text);

    free(text);
    free(pattern);

    return 0;
}

/**
 * @brief Get the User Input 
 * 
 * @return char* 
 */
char *GetUserInput()
{
    char *input = malloc(sizeof(char) * MAX_INPUT_LEN);
    if(fgets(input, MAX_INPUT_LEN - 1, stdin) == NULL)
    {
        return NULL;
    }

    // remove trailing return if there is one
    int len = strlen(input);
    if(input[len-1] == RETURN_CHAR)
    {
        input[len-1] = NULL_TERM;
    }
    printf("\n");

    return input;
}

/**
 * @brief Retrieves the current time in milliseconds
 * 
 * NOTE: This is from the example given by Professor Fangju Wang from assignment 1
 * 
 * @return long int 
 */
long int CurTime()
{
    struct timespec ts;
    long int cur = 0;

    // get the current utc time
    timespec_get(&ts, TIME_UTC);
    cur = ((long int)ts.tv_sec) * 1000 + ((long int)ts.tv_nsec)/1000000;

    return cur;
}

/**
 * @brief Used to analyze the string search algorithms - writes the results in a csv
 * 
 * @param text 
 */
void RunTests(char *text)
{
    char * patterns[] = {"that", "the", "excluding", "Certain", "Possible", "Canada", "admission", "uselessness", "behalf", "a"};

    // open file for writing
    FILE *file = fopen("test.csv", "w");
    if(!file)
    {
        return;
    }

    fprintf(file, "test_no, type, pattern, length, executiontime, matches, shifts\n");

    // loop through the array of strings to perform the tests
    for(int i = 0; i < 10; i++)
    {
        int shifts = 0;
    long int Q2P1_pre = CurTime();
    int matches = StringSearchBruteForce(patterns[i], text, &shifts);
    long int Q2P1_post = CurTime();

    fprintf(file, "%d, BRUTE_FORCE, %s, %ld, %ld, %d, %d\n", i,patterns[i], strlen(patterns[i]), (Q2P1_post - Q2P1_pre), matches, shifts);

    long int Q2P2_pre = CurTime();
    matches = StringSearchHarspoolAlgorithm(patterns[i], text, &shifts);
    long int Q2P2_post = CurTime();

    fprintf(file, "%d, HARSPOOL, %s, %ld, %ld, %d, %d\n", i,patterns[i], strlen(patterns[i]), (Q2P2_post - Q2P2_pre), matches, shifts);

    long int Q2P3_pre = CurTime();
    matches = StringSearchBoyerMooreAlgorithm(patterns[i], text, &shifts);
    long int Q2P3_post = CurTime();

    fprintf(file, "%d, BOYER_MOORE, %s, %ld, %ld, %d, %d\n", i,patterns[i], strlen(patterns[i]), (Q2P3_post - Q2P3_pre), matches, shifts);
    
    }

    // close file
    fclose(file);
}

void GetMetrics(char *text)
{
    char * patterns[] = {"that", "the", "excluding", "Certain", "Possible", "Canada", "admission", "uselessness", "behalf", "a"};

    // open file for writing
    FILE *file = fopen("metrics.csv", "w");
    if(!file)
    {
        return;
    }

    fprintf(file, "test_no, pattern, matches, Brute Force vs Harspool (time), Brute Force vs Boyer-Moore (time), Harspool vs Boyer-Moore (time), Brute Force vs Harspool(shifts), Brute Force vs Boyer-Moore(shifts), Harspool vs Boyer-Moore(shifts) \n");

    // loop through the array of strings to perform the tests
    for(int i = 0; i < 10; i++)
    {
        int bf_shifts = 0;
        int h_shifts = 0;
        int bm_shifts = 0;

        long int Q2P1_pre = CurTime();
        int matches = StringSearchBruteForce(patterns[i], text, &bf_shifts);
        long int Q2P1_post = CurTime();

        int bf_time = Q2P1_post - Q2P1_pre;

        long int Q2P2_pre = CurTime();
        matches = StringSearchHarspoolAlgorithm(patterns[i], text, &h_shifts);
        long int Q2P2_post = CurTime();
        int h_time = Q2P2_post - Q2P2_pre;

        long int Q2P3_pre = CurTime();
        matches = StringSearchBoyerMooreAlgorithm(patterns[i], text, &bm_shifts);
        long int Q2P3_post = CurTime();
        int bm_time = Q2P3_post - Q2P3_pre;

        double bf_h_time = (double)bf_time/(double)h_time;
        double bf_bm_time = (double)bf_time/(double)bm_time;
        double h_bm_time = (double)h_time/(double)bm_time;

        double bf_h_shifts = (double)bf_shifts/(double)h_shifts;
        double bf_bm_shifts = (double)bf_shifts/(double)bm_shifts;
        double h_bm_shifts = (double)h_shifts/(double)bm_shifts;
        
        fprintf(file, "%d, %s, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f \n", i, patterns[i], matches, 
            bf_h_time, bf_bm_time, h_bm_time, bf_h_shifts, bf_bm_shifts, h_bm_shifts);
    }

    // close file
    fclose(file);
}
