// Names: Navid Nikoo, Kasim Rashid, and Anthony Te
// This program will take a list of intergers and divide them into two(almost) equally sized list
// and two worker threads which will be sorting the list then merged with a merging thread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// not sure where to put these
typedef struct 
{
    int * subArray;
    size_t size;
} SortingThreadParameters;

// the list that will be sorted

#define SIZE(sizeof(list)/sizeof(*list))
int list[11] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE];

int main() {
    
    int list[11] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
    int result[SIZE];

}