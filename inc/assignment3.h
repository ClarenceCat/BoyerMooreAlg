/**
 * @file assignment3.h
 * @author Daniel Grew (0978547)
 * @brief This file contais the function prototypes for all functions in the assignment and struct definition for an interval
 * @version 0.1
 * @date 2022-03-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

// Constants
#define MAX_INPUT_LEN 100
#define RETURN_CHAR '\n'
#define NULL_TERM '\0'

#define ERROR -1
#define INT_PER_INTERVAL 2
#define Q1_MAX_LINE_LEN 50
#define READ "r"
#define EMPTY_STR ""

#define Q2_MAX_LINE_LEN 100
#define Q2_FILE_NAME "./bin/data_A3_Q2.txt"

#define SHIFT_TABLE_LEN 52
#define UPPER_A 'A'
#define UPPER_Z 'Z'
#define LOWER_A 'a'
#define LOWER_Z 'z'
#define NOT_FOUND 6

// struct definitions
typedef struct interval {
    int x1;
    int x2;
} Interval;

// function prototypes
// getting user input
char *GetUserInput();
long int CurTime();
void RunTests(char *text);
void GetMetrics(char *text);

// file reading
Interval *ReadQ1Data(char *filename, int *array_size);
int FileLen(char *filename);
Interval *Q1ExtractData(char *filename, int file_len);

// question 1
// pt1
int CommonPointBruteForce(Interval *intervals, int array_size, int *common_point);

// pt2
int CommonPointPreSort(Interval *intervals, int array_size, int *common_point);
void IntervalsToInts(Interval *intervals, int array_size, int *dest_1, int *dest_2);
void MergeSort(int *array, int arr_size);
void Merge(int *lower, int lower_len, int *upper, int upper_len, int *array, int array_len);
void CopyArray(int *dest, int *src, int start, int end);

// question 2
// pt1
int StringSearchBruteForce(char *pattern, char *text, int *shifts);
char *ReadQ2Data(char *filename);
int Q2GetNumChars(char *filename);

// pt2
int StringSearchHarspoolAlgorithm(char *pattern, char *text, int *shifts);
int CharToIndex(char c);

// pt3
int StringSearchBoyerMooreAlgorithm(char *pattern, char *text, int *shifts);
int *ConstructGoodSuffixTable(char *pattern, int pattern_len);
int max(int n1, int n2);

