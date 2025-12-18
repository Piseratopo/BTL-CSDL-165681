#include <stdio.h>
#include <string.h>

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

int main(void) {
   Sample samples[] = {
      {"2025-12-12 10:30", "T1", 30.5, "C"},
      {"2025-12-12 10:35", "P1", 1.2, "bar"},
      {"2025-12-12 10:32", "T2", 28.1, "C"},
      {"2025-12-12 10:31", "T1", 31.0, "C"},
      {"2025-12-12 10:33", "I3", 15.0, "A"},
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

   return 0;
}
