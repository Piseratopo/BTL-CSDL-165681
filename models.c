#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"

Sample* createSample(const char* timestamp, const char* tag, double value, const char* unit) {
   Sample* newSample = (Sample*)malloc(sizeof(Sample));
   if (!newSample) {
      printf("Memory allocation failed!\n");
      return NULL;
   }

   strncpy(newSample->timestamp, timestamp, sizeof(newSample->timestamp) - 1);
   newSample->timestamp[sizeof(newSample->timestamp) - 1] = '\0';

   strncpy(newSample->tag, tag, sizeof(newSample->tag) - 1);
   newSample->tag[sizeof(newSample->tag) - 1] = '\0';

   newSample->value = value;

   strncpy(newSample->unit, unit, sizeof(newSample->unit) - 1);
   newSample->unit[sizeof(newSample->unit) - 1] = '\0';

   newSample->next = NULL;
   return newSample;
}

/**
 * Input alarm from user and add to linked list.
 *
 * This function prompts the user to input details of an alarm and
 * adds the alarm to the linked list.
 *
 * @param head A pointer to the head of the linked list.
 */
void inputSample(Sample** head) {
   char timestamp[MAX_TIMESTAMP_LENGTH];
   char tag[MAX_TAG_LENGTH];
   char unit[MAX_UNIT_LENGTH];
   char buffer[256];
   double value = 0.0;

   printf("Timestamp (YYYY-MM-DD HH:MM): ");
   if (fgets(timestamp, sizeof(timestamp), stdin)) {
      timestamp[strcspn(timestamp, "\n")] = '\0';
   }

   printf("Tag (e.g., T1, P2): ");
   if (fgets(tag, sizeof(tag), stdin)) {
      tag[strcspn(tag, "\n")] = '\0';
   }

   printf("Value: ");
   if (fgets(buffer, sizeof(buffer), stdin)) {
      value = strtod(buffer, NULL);
   }

   printf("Unit (e.g., V, A, bar): ");
   if (fgets(unit, sizeof(unit), stdin)) {
      unit[strcspn(unit, "\n")] = '\0';
   }

   Sample* newSample = createSample(timestamp, tag, value, unit);

   if (*head == NULL) {
      *head = newSample;
   } else {
      Sample* temp = *head;
      while (temp->next != NULL) {
         temp = temp->next;
      }
      temp->next = newSample;
   }
}

/**
 * Prints out all alarms in the linked list.
 *
 * This function traverses the linked list of alarms and prints out
 * the details of each alarm.
 *
 * @param head A pointer to the head of the linked list.
 */
void printSamples(const Sample* head) {
   const Sample* temp = head;
   while (temp != NULL) {
      printf("Timestamp: %s\n", temp->timestamp);
      printf("Tag: %s\n", temp->tag);
      printf("Value: %.2f\n", temp->value);
      printf("Unit: %s\n", temp->unit);
      printf("---------------------------\n");
      temp = temp->next;
   }
}
