#include <stdio.h>
#include "tree.h"
#include "sort.h"

int main() {
    Sample samples[4] = {
        {"2025-12-12 10:30", "T1", 30.5, "C"},
        {"2025-12-12 10:35", "P1", 1.2, "bar"},
        {"2025-12-12 10:32", "T2", 28.1, "C"},
        {"2025-12-12 10:31", "T1", 31.0, "C"}
    };

    // TEST SORT
    sortByTimestamp(samples, 4);
    printf("=== SORT BY TIME ===\n");
    for (int i = 0; i < 4; i++)
        printf("%s %s %.2f\n", samples[i].timestamp, samples[i].tag, samples[i].value);

    // TEST TREE
    TreeNode *root = NULL;
    for (int i = 0; i < 4; i++)
        root = insertBST(root, samples[i]);

    printf("\n=== INORDER BST ===\n");
    inorderPrint(root);

    return 0;
}
