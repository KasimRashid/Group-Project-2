// Names: Navid Nikoo, Kasim Rashid, and Anthony Te
// This program will take a list of intergers and divide them into two(almost) equally sized list
// and two worker threads which will be sorting the list then merged with a merging thread

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

// the list that will be sorted
#define SIZE 11
int list[SIZE] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[SIZE];

// not sure where to put these
typedef struct 
{
    int start;
    int end;
} ThreadParameters;

void *sort(void *ThreadParameters);
void *merge(void *ThreadParameters);
void quick_sort(int lhs, int rhs);
int partition(int lhs, int rhs);



int main(int argc, const char *argv[]) {
    int i;
    pthread_t workers[3];
    
    // first sorting thread
    ThreadParameters *thread_1 =(ThreadParameters *)malloc(sizeof(ThreadParameters));
    thread_1->start = 0;
    thread_1->end = (SIZE % 2 == 0) ? ((SIZE / 2) - 1) : ((SIZE + 1) / 2);

    // Second thread
    ThreadParameters *thread_2 =(ThreadParameters *)malloc(sizeof(ThreadParameters));
    thread_2->start = (SIZE % 2 == 0) ? (SIZE / 2) : (((SIZE + 1) / 2) + 1);
    thread_2->end = SIZE -1;
}