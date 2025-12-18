#include <string.h>
#include "sort.h"
void sortByValue(Sample arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].value < arr[minIdx].value)
                minIdx = j;
        }
        if (minIdx != i) {
            Sample tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}
