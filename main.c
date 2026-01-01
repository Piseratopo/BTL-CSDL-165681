#include <stdio.h>
#include <stdlib.h>
#include "models.h"
#include "menu.h"
#include "tree.h"

int main() {
   Sample* sampleList = NULL;
   TreeNode* root = NULL;
   int choice;

   do {
      displayMainMenu();
      if (scanf("%d", &choice) != 1) {
         // Clear input buffer on invalid input
         while (getchar() != '\n');
         choice = -1; // Force invalid choice
      } else {
         getchar(); // Consume newline
      }
      
      handleMenuChoice(choice, &sampleList, &root);
   } while (choice != 0);

   // Cleanup
   freeSampleList(&sampleList);
   
   return 0;
}