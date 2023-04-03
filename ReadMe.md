Daniel Grew (0978547)

Running Each Part of the Assignment

To compile the assignment enter the following commands in the terminal (or bash) while in the root of the assignment directory

    make all
    bin/assignment3

Next, the program should ask for a file input. You must enter the file name with the location relative to where you ran the program
E.g. if you ran the assignment from the root directory of the assignment (as you would have done above) and the text file was in the 
bin, you would type "bin/filename.txt" (where filename is the name of your file).

NOTE: also ensure that the data_A3_Q2.txt file is in the bin directory prior to running the program.

// Analysis and comparison of Question 2 Algorithms
// NOTE: this data was collected using the RunTests() and GetMetrics() functions in the main.c file

// RAW DATA
test_no, type, pattern, length, executiontime, matches, shifts
0, BRUTE_FORCE, that, 4, 9, 885, 3296599
0, HARSPOOL, that, 4, 9, 885, 893045
0, BOYER_MOORE, that, 4, 11, 885, 893045
1, BRUTE_FORCE, the, 3, 10, 28338, 3296600
1, HARSPOOL, the, 3, 11, 28338, 1142020
1, BOYER_MOORE, the, 3, 14, 28338, 1142020
2, BRUTE_FORCE, excluding, 9, 10, 4, 3296594
2, HARSPOOL, excluding, 9, 4, 4, 440873
2, BOYER_MOORE, excluding, 9, 5, 4, 440873
3, BRUTE_FORCE, Certain, 7, 8, 2, 3296596
3, HARSPOOL, Certain, 7, 5, 2, 578278
3, BOYER_MOORE, Certain, 7, 8, 2, 578278
4, BRUTE_FORCE, Possible, 8, 7, 0, 3296595
4, HARSPOOL, Possible, 8, 5, 0, 464110
4, BOYER_MOORE, Possible, 8, 6, 0, 464110
5, BRUTE_FORCE, Canada, 6, 7, 305, 3296597
5, HARSPOOL, Canada, 6, 6, 305, 609692
5, BOYER_MOORE, Canada, 6, 7, 305, 608845
6, BRUTE_FORCE, admission, 9, 9, 1363, 3296594
6, HARSPOOL, admission, 9, 5, 1363, 427338
6, BOYER_MOORE, admission, 9, 5, 1363, 427338
7, BRUTE_FORCE, uselessness, 11, 8, 1, 3296592
7, HARSPOOL, uselessness, 11, 4, 1, 361106
7, BOYER_MOORE, uselessness, 11, 4, 0, 355997
8, BRUTE_FORCE, behalf, 6, 8, 133, 3296597
8, HARSPOOL, behalf, 6, 5, 133, 622098
8, BOYER_MOORE, behalf, 6, 8, 133, 622098
9, BRUTE_FORCE, a, 1, 8, 212359, 3296602
9, HARSPOOL, a, 1, 28, 212359, 3296603
9, BOYER_MOORE, a, 1, 21, 212359, 3296603

// SUMMARY OF DATA
test_no, pattern, Brute Force vs Harspool (time), Brute Force vs Boyer-Moore (time), Harspool vs Boyer-Moore (time), Brute Force vs Harspool(shifts), Brute Force vs Boyer-Moore(shifts), Harspool vs Boyer-Moore(shifts) 
0, that, 1.00, 0.82, 0.82, 3.69, 3.69, 1.00 
1, the, 0.91, 0.71, 0.79, 2.89, 2.89, 1.00 
2, excluding, 2.50, 2.00, 0.80, 7.48, 7.48, 1.00 
3, Certain, 1.33, 1.14, 0.86, 5.70, 5.70, 1.00 
4, Possible, 1.40, 1.17, 0.83, 7.10, 7.10, 1.00 
5, Canada, 1.17, 1.00, 0.86, 5.41, 5.41, 1.00 
6, admission, 1.80, 1.80, 1.00, 7.71, 7.71, 1.00 
7, uselessness, 2.00, 2.00, 1.00, 9.13, 9.26, 1.01 
8, behalf, 1.60, 1.00, 0.62, 5.30, 5.30, 1.00 
9, a, 0.29, 0.38, 1.33, 1.00, 1.00, 1.00 

Averages for data
    TIME:
        Average Brute force : Harspool ratio = 1.4
        Average Brute force : Boyer-Moore ratio = 1.2
        Average Harspool : Boyer-Moore = 0.891
    
    SHIFTS
        Average Brute force : Harspool ratio = 5.541
        Average Brute force : Boyer-Moore ratio = 5.554
        Average Harspool : Boyer-Moore = 1.001

The data suggests that among the tests, the Harspool algorithm outperformed both the Brute Force algorithm and the Boyer-Moore algorithm.
I suspect that the harspool algorithm outperformed the Boyer-Moore algorithm because the words used in the tests did not contain repeated suffixes. This means that the good_suffix_table in the Boyer Moore algorithm made little to no use of the good_suffix table. This is why we also see that the ratio of shifts performed between the two algorithms is almost a 1:1 ratio.
