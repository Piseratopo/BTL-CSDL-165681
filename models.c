#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"

// Create a new alarm node
Alarm* createAlarm(int id, const char* tag, const char* time, int priority, const char* description) {
   Alarm* newAlarm = (Alarm*)malloc(sizeof(Alarm));
   if (!newAlarm) {
      printf("Memory allocation failed!\n");
      return NULL;
   }
   newAlarm->id = id;
   strncpy(newAlarm->tag, tag, sizeof(newAlarm->tag) - 1);
   newAlarm->tag[sizeof(newAlarm->tag) - 1] = '\0';
   strncpy(newAlarm->time, time, sizeof(newAlarm->time) - 1);
   newAlarm->time[sizeof(newAlarm->time) - 1] = '\0';
   newAlarm->priority = priority;
   strncpy(newAlarm->description, description, sizeof(newAlarm->description) - 1);
   newAlarm->description[sizeof(newAlarm->description) - 1] = '\0';
   newAlarm->next = NULL;
   return newAlarm;
}

/**
 * Input alarm from user and add to linked list.
 *
 * This function prompts the user to input details of an alarm and
 * adds the alarm to the linked list.
 *
 * @param head A pointer to the head of the linked list.
 */
void inputAlarm(Alarm** head) {
   int id, priority;
   char buffer[128];          // general input buffer
   char tag[20], time[20], description[100];

   printf("Alarm's ID: ");
   if (fgets(buffer, sizeof(buffer), stdin)) {
      id = (int)strtol(buffer, NULL, 10);
   }

   printf("Tag (device name or channel): ");
   if (fgets(tag, sizeof(tag), stdin)) {
      // remove newline character from end of string
      tag[strcspn(tag, "\n")] = '\0';
   }

   printf("Time of occurrence: ");
   if (fgets(time, sizeof(time), stdin)) {
      time[strcspn(time, "\n")] = '\0';
   }

   printf("Priority (1: high, 2: medium, 3: low): ");
   if (fgets(buffer, sizeof(buffer), stdin)) {
      priority = (int)strtol(buffer, NULL, 10);
   }

   printf("Short description: ");
   if (fgets(description, sizeof(description), stdin)) {
      description[strcspn(description, "\n")] = '\0';
   }

   // create a new alarm node and add to linked list
   Alarm* newAlarm = createAlarm(id, tag, time, priority, description);

   if (*head == NULL) {
      // if list is empty, set new alarm as head
      *head = newAlarm;
   } else {
      Alarm* temp = *head;
      // traverse list to find last node and append new node
      while (temp->next != NULL) {
         temp = temp->next;
      }
      temp->next = newAlarm;
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
void printAlarms(const Alarm* head) {
   const Alarm* temp = head;
   while (temp != NULL) {
      // print alarm details
      printf("ID: %d\n", temp->id);
      printf("Tag: %s\n", temp->tag);
      printf("Time: %s\n", temp->time);
      printf("Priority: %d\n", temp->priority);
      printf("Description: %s\n", temp->description);
      printf("---------------------------\n");
      // move to next alarm in list
      temp = temp->next;
   }
}
