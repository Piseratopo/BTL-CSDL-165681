#include <stdio.h>
#include "models.h"

int main() {
   Sample* sampleList = NULL;

   // Input 2 samples
   inputSample(&sampleList);
   inputSample(&sampleList);

   // Print all samples
   printf("\nSample list:\n");
   printSamples(sampleList);

   return 0;
}