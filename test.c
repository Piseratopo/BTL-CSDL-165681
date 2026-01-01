#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "models.h"
#include "sort.h"
#include "tree.h"

static void printSampleArray(const char* title, const Sample* arr, int n) {
   printf("%s\n", title);
   for (int i = 0; i < n; ++i) {
      printf("%-16s %-3s %6.2f %-6s\n",
             arr[i].timestamp,
             arr[i].tag,
             arr[i].value,
             arr[i].unit);
   }
   printf("---------------------------\n");
}

static void runSortingAndTreeDemo(void) {
   Sample samples[] = {
      {"2025-12-12 10:30", "T1", 30.5, "C", NULL},
      {"2025-12-12 10:35", "P1",  1.2, "bar", NULL},
      {"2025-12-12 10:32", "T2", 28.1, "C", NULL},
      {"2025-12-12 10:31", "T1", 31.0, "C", NULL},
      {"2025-12-12 10:33", "I3", 15.0, "A", NULL},
   };
   const int count = (int)(sizeof(samples) / sizeof(samples[0]));

   printSampleArray("=== ORIGINAL ORDER ===", samples, count);

   Sample byTimestamp[count];
   Sample byValue[count];
   memcpy(byTimestamp, samples, sizeof(samples));
   memcpy(byValue, samples, sizeof(samples));

   sortByTimestamp(byTimestamp, count);
   printSampleArray("=== SORTED BY TIMESTAMP ===", byTimestamp, count);

   sortByValue(byValue, count);
   printSampleArray("=== SORTED BY VALUE ===", byValue, count);

   TreeNode* root = NULL;
   for (int i = 0; i < count; ++i) {
      root = insertBST(root, samples[i]);
   }

   printf("=== INORDER BST (TAG ASC) ===\n");
   inorderPrint(root);
   printf("---------------------------\n");

   const char* probeTag = "T1";
   TreeNode* found = searchBST(root, probeTag);
   if (found) {
      printf("Found tag %s -> %s %.2f %s\n",
             probeTag,
             found->data.timestamp,
             found->data.value,
             found->data.unit);
   } else {
      printf("Tag %s not found in BST.\n", probeTag);
   }
}

static void runLoggerDemo(void) {
   Sample* logger = NULL;
   Sample dataset[] = {
      {"2024-12-18 08:00", "TEMP_01", 30.5, "C", NULL},
      {"2024-12-18 08:05", "PRES_01",  2.1, "bar", NULL},
      {"2024-12-18 08:10", "VOLT_M", 220.0, "V", NULL},
      {"2024-12-18 08:15", "TEMP_01", 31.2, "C", NULL},
      {"2024-12-18 08:20", "PRES_01",  2.3, "bar", NULL},
      {"2024-12-18 08:25", "VOLT_M", 219.5, "V", NULL},
      {"2024-12-18 08:30", "TEMP_01", 32.0, "C", NULL},
      {"2024-12-18 08:35", "PRES_01",  2.4, "bar", NULL},
      {"2024-12-18 08:40", "VOLT_M", 221.0, "V", NULL},
   };
   const size_t count = sizeof(dataset) / sizeof(dataset[0]);

   for (size_t i = 0; i < count; ++i) {
      addSample(&logger, dataset[i]);
   }

   printSampleList(logger);
   freeSampleList(&logger);
}

static void usage(const char* prog) {
   printf("Usage: %s [all|logger|algo]\n", prog);
   printf("   all    - run every demo (default)\n");
   printf("   logger - run the linked-list logger demo only\n");
   printf("   algo   - run sorting + tree demos only\n");
}

int main(int argc, char* argv[]) {
   int runLogger = 1;
   int runAlgorithms = 1;

   if (argc > 1) {
      runLogger = 0;
      runAlgorithms = 0;

      for (int i = 1; i < argc; ++i) {
         if (strcmp(argv[i], "logger") == 0) {
            runLogger = 1;
         } else if (strcmp(argv[i], "algo") == 0 || strcmp(argv[i], "algorithms") == 0) {
            runAlgorithms = 1;
         } else if (strcmp(argv[i], "all") == 0) {
            runLogger = 1;
            runAlgorithms = 1;
            break;
         } else {
            usage(argv[0]);
            return 1;
         }
      }

      if (!runLogger && !runAlgorithms) {
         usage(argv[0]);
         return 1;
      }
   }

   if (runLogger) {
      printf("=== DATA LOGGER LINKED LIST DEMO ===\n");
      runLoggerDemo();
   }

   if (runAlgorithms) {
      if (runLogger) {
         putchar('\n');
      }
      printf("=== SORT & TREE DEMO ===\n");
      runSortingAndTreeDemo();
   }

   return 0;
}
