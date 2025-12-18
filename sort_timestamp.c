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
