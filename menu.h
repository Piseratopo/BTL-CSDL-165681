#ifndef MENU_H
#define MENU_H

#include "models.h"
#include "tree.h"

void displayMainMenu();
void handleMenuChoice(int choice, Sample** sampleList, TreeNode** root);
void addSampleMenu(Sample** sampleList);
void listSamplesMenu(Sample* sampleList);
void searchSamplesMenu(Sample* sampleList, TreeNode* root);
void sortSamplesMenu(Sample** sampleList);
void buildTreeMenu(Sample* sampleList, TreeNode** root);
void searchByTag(TreeNode* root);
void searchByTimestamp(Sample* sampleList);

#endif
