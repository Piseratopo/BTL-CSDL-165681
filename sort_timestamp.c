#include <string.h>
#include "sort.h"

void sortByTimestamp(Sample arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].timestamp, arr[j + 1].timestamp) > 0) {
                Sample tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
// void sortByValue(Sample arr[], int n) {
    //for (int i = 0; i < n - 1; i++) {
      //  int minIdx = i;
        //for (int j = i + 1; j < n; j++) {
          //  if (arr[j].value < arr[minIdx].value)
            //    minIdx = j;
        //}
        //if (minIdx != i) {
          //  Sample tmp = arr[i];
            //arr[i] = arr[minIdx];
            //arr[minIdx] = tmp;
        //}
    //}
//}
