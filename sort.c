#include <string.h>
#include "sort.h"

static void swapSamples(Sample* a, Sample* b) {
   Sample tmp = *a;
   *a = *b;
   *b = tmp;
}

void sortByTimestamp(Sample arr[], int n) {
   for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (strcmp(arr[j].timestamp, arr[j + 1].timestamp) > 0) {
            swapSamples(&arr[j], &arr[j + 1]);
         }
      }
   }
}

void sortByValue(Sample arr[], int n) {
   for (int i = 0; i < n - 1; i++) {
      int minIdx = i;
      for (int j = i + 1; j < n; j++) {
         if (arr[j].value < arr[minIdx].value) {
            minIdx = j;
         }
      }
      if (minIdx != i) {
         swapSamples(&arr[i], &arr[minIdx]);
      }
   }
}
// listToArray is now implemented in models.c
// This function is kept for backward compatibility
int listToArrayWrapper(Sample *head, Sample arr[], int max) {
    int count = 0;
    Sample* result = listToArray(head, &count);
    if (result == NULL) return 0;
    
    int elementsToCopy = (count < max) ? count : max;
    for (int i = 0; i < elementsToCopy; i++) {
        arr[i] = result[i];
    }
    
    free(result);
    return elementsToCopy;
}
void sortSamplesByTag(Sample arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i].tag, arr[j].tag) > 0) {
                Sample tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

