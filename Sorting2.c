// right now there is a few errros
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TheSize 11
#define NUMBER_OF_THREADS 3

void *sorter(void *params);  // Thread functionfor sorting 
void *merger(void *params);  // Thread function for merging 
void quick_sort(int low, int high); // Quick Sort implementation 
int partition(int low, int high);   // Helper function for Quick Sort

int list[TheSize] = {7, 12, 19, 3, 18, 4, 2, -5, 6, 15, 8};
int result[TheSize];  // Array to hold sorted output

typedef struct {
    int StartIndex;
    int EndIndex;
} parameters;

int main(int argc, const char *argv[]) {
    int i;
    pthread_t workers[NUMBER_OF_THREADS];

    // Create first sorting thread
    parameters *data1 = (parameters *)malloc(sizeof(parameters));
    data1->StartIndex = 0;
    data1->EndIndex = (TheSize / 2) - 1;
    pthread_create(&workers[0], NULL, sorter, data1);

    // Create second sorting thread
    parameters *data2 = (parameters *)malloc(sizeof(parameters));
    data2->StartIndex = (TheSize / 2);
    data2->EndIndex = TheSize - 1;
    pthread_create(&workers[1], NULL, sorter, data2);

    // Wait for sorting threads to finish
    pthread_join(workers[0], NULL);
    pthread_join(workers[1], NULL);

    // Create merge thread
    parameters *theMerge = (parameters *)malloc(sizeof(parameters));
    theMerge->StartIndex = 0;
    theMerge->EndIndex = TheSize - 1;  /// error 
    pthread_create(&workers[2], NULL, merger, theMerge);

    // Wait for merging thread to finish
    pthread_join(workers[2], NULL);

    // Output the sorted array
    printf("\nFinal Sorted Array:\n");
    for (i = 0; i < TheSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free allocated memory
    free(data1);
    free(data2);
    free(theMerge);

    return 0;
}

// Sorting function using Quick Sort
void *sorter(void *params) {
    parameters *p = (parameters *)params;
    int begin = p->StartIndex;
    int end = p->EndIndex; /// error 

    quick_sort(begin, end);

    // Copy sorted values to result[]
    for (int i = begin; i <= end; i++) {
        result[i] = list[i];
    }

    pthread_exit(0);
}

// Quick Sort implementation
void quick_sort(int low, int high) {
    if (low < high) {
        int pivot_index = partition(low, high);
        quick_sort(low, pivot_index - 1);
        quick_sort(pivot_index + 1, high);
    }
}

// Partition function for Quick Sort
int partition(int low, int high) {
    int pivot = list[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (list[j] < pivot) {
            i++;
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    int temp = list[i + 1];
    list[i + 1] = list[high];
    list[high] = temp;
    return i + 1;
}

// Merging function
void *merger(void *params) {
    parameters *p = (parameters *)params;
    int mid = TheSize / 2;
    int i = 0, j = mid, k = 0;
    int temp[TheSize];

    // Merge two sorted halves
    while (i < mid && j < TheSize) {
        if (result[i] < result[j]) {
            temp[k++] = result[i++];
        } else {
            temp[k++] = result[j++];
        }
    }

    // Copy remaining elements from the first half
    while (i < mid) {
        temp[k++] = result[i++];
    }

    // Copy remaining elements from the second half
    while (j < TheSize) {
        temp[k++] = result[j++];
    }

    // Copy merged values back to result[]
    for (i = 0; i < TheSize; i++) {
        result[i] = temp[i];
    }

    pthread_exit(0);
}
