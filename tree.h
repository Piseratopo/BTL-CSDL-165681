#ifndef TREE_H
#define TREE_H

#include "models.h"

typedef struct TreeNode {
    Sample data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createTreeNode(Sample s);
TreeNode* insertBST(TreeNode *root, Sample s);
TreeNode* searchBST(TreeNode *root, const char *tag);
void inorderPrint(TreeNode *root);

#endif
