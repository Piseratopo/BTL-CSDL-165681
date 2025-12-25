#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

TreeNode* createTreeNode(Sample s) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = s;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insertBST(TreeNode *root, Sample s) {
    if (root == NULL)
        return createTreeNode(s);

    if (strcmp(s.tag, root->data.tag) < 0)
        root->left = insertBST(root->left, s);
    else
        root->right = insertBST(root->right, s);

    return root;
}

TreeNode* searchBST(TreeNode *root, const char *tag) {
    if (root == NULL) return NULL;

    int cmp = strcmp(tag, root->data.tag);
    if (cmp == 0) return root;
    if (cmp < 0) return searchBST(root->left, tag);
    return searchBST(root->right, tag);
}

void inorderPrint(TreeNode *root) {
    if (root == NULL) return;

    inorderPrint(root->left);
    printf("%s | %s | %.2f %s\n",
           root->data.timestamp,
           root->data.tag,
           root->data.value,
           root->data.unit);
    inorderPrint(root->right);
}
TreeNode* buildBSTFromList(Node *head) {
    TreeNode *root = NULL;
    Node *cur = head;

    while (cur != NULL) {
        root = insertBST(root, cur->data);
        cur = cur->next;
    }

    return root;
}
