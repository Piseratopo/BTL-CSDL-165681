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
