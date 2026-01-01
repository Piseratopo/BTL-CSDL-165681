#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"

static Sample* duplicateSampleNode(const Sample* sample) {
   Sample* newNode = (Sample*)malloc(sizeof(Sample));
   if (!newNode) {
      printf("Memory allocation failed!\n");
      exit(EXIT_FAILURE);
   }
   *newNode = *sample;
   newNode->next = NULL;
   return newNode;
}

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

void addSample(Sample** head, Sample sample) {
   Sample* newNode = duplicateSampleNode(&sample);
   if (*head == NULL) {
      *head = newNode;
      return;
   }

   Sample* current = *head;
   while (current->next != NULL) {
      current = current->next;
   }
   current->next = newNode;
}


void freeSampleList(Sample** head) {
   if (!head || !*head) {
      return;
   }

   Sample* current = *head;
   while (current != NULL) {
      Sample* nextNode = current->next;
      free(current);
      current = nextNode;
   }
   *head = NULL;
}

// Search by Tag
void searchLinearByTag(const Sample* head, const char* tag) {
   printf("\n--- TIM KIEM LICH SU DO CHO TAG: %s ---\n", tag);
   printf("%-20s %-10s %-10s %-10s\n", "Timestamp", "Tag", "Value", "Unit");
   int found = 0;
   const Sample* current = head;
   while (current != NULL) {
      // So sánh chuỗi tag
      if (strcmp(current->tag, tag) == 0) {
         printf("%-20s %-10s %-10.2f %-10s\n",
                  current->timestamp, 
                  current->tag, 
                  current->value, 
                  current->unit);
         found++;
      }
      current = current->next;
   }
   if (found == 0) printf("(Khong tim thay du lieu cho tag %s)\n", tag);
}
// Search by time range
void searchByTimeRange(Sample* head, char* startTime, char* endTime) {
   printf("\n--- SEARCH FROM %s TO %s ---\n", startTime, endTime);
   printf("%-20s %-10s %-10s %-10s\n", "Timestamp", "Tag", "Value", "Unit");

   int found = 0;
   Sample* current = head;

   while (current != NULL) {
      // Compare timestamp strings
      if (strcmp(current->timestamp, startTime) >= 0 &&
         strcmp(current->timestamp, endTime) <= 0) {
         
         printf("%-20s %-10s %-10.2f %-10s\n", 
                  current->timestamp, 
                  current->tag, 
                  current->value, 
                  current->unit);
         found++;
      }
      current = current->next;
   }
   
   if (found == 0) printf("(No data available)\n");
}

// Delete by Timestamp
void deleteByTimestamp(Sample** head, char* targetTime) {
   Sample* current = *head;
   Sample* prev = NULL;

   // Empty list
   if (current == NULL) return;

   // Case: Delete head node
   if (strcmp(current->timestamp, targetTime) == 0) {
      *head = current->next; // Update head
      free(current);         // Free memory
      printf("Deleted sample at timestamp: %s\n", targetTime);
      return;
   }

   // Case: Delete middle or end node
   while (current != NULL && strcmp(current->timestamp, targetTime) != 0) {
      prev = current;
      current = current->next;
   }

   // Not found
   if (current == NULL) {
      printf("Sample not found for deletion!\n");
      return;
   }

   // Perform deletion
   prev->next = current->next;
   free(current);
   printf("Deleted sample at timestamp: %s\n", targetTime);
}

// Convert Linked List to Array (for sorting support)
Sample* listToArray(Sample* head, int* count) {
   // Step 1: Count the number of nodes
   int n = 0;
   Sample* current = head;
   while (current != NULL) {
      n++;
      current = current->next;
   }
   *count = n;

   if (n == 0) return NULL;

   // Step 2: Allocate dynamic array
   Sample* arr = (Sample*)malloc(n * sizeof(Sample));
   if (arr == NULL) return NULL;

   // Step 3: Copy data
   current = head;
   for (int i = 0; i < n; i++) {
      // Copy entire struct content
      arr[i] = *current; 
      
      // Set next to NULL to avoid unwanted links
      arr[i].next = NULL; 
      
      current = current->next;
   }

   return arr;
}
// Calculate statistics by Tag
void calculateStatsByTag(const Sample* head, const char* tag) {
   double minVal = 1e9, maxVal = -1e9, sum = 0;
   int count = 0;
   const Sample* current = head;

   while (current != NULL) {
      if (strcmp(current->tag, tag) == 0) {
         if (current->value < minVal) minVal = current->value;
         if (current->value > maxVal) maxVal = current->value;
         sum += current->value;
         count++;
      }
      current = current->next;
   }

   if (count > 0) {
      printf("\n--- THONG KE DU LIEU CHO TAG: %s ---\n", tag);
      printf("So luong mau: %d\n", count);
      printf("Gia tri Min : %.2f\n", minVal);
      printf("Gia tri Max : %.2f\n", maxVal);
      printf("Trung binh  : %.2f\n", sum / count);
   } else {
      printf("Khong tim thay tag '%s' de thong ke.\n", tag);
   }
}
// Save to CSV
void saveToCSV(const Sample* head, const char* filename, const char* filterTag) {
   FILE *f = fopen(filename, "w");
   if (f == NULL) {
      printf("Loi: Khong the tao hoac mo file '%s' de ghi!\n", filename);
      return;
   }
   fprintf(f, "Timestamp,Tag,Value,Unit\n");

   int count = 0;
   const Sample* current = head;
   while (current != NULL) {
      if (filterTag == NULL || strlen(filterTag) == 0 || strcmp(current->tag, filterTag) == 0) {
         fprintf(f, "%s,%s,%.2f,%s\n", 
                 current->timestamp, 
                 current->tag, 
                 current->value, 
                 current->unit);
         count++;
      }
      current = current->next;
   }

   fclose(f);
   printf("Da xuat %d dong du lieu ra file '%s' thanh cong.\n", count, filename);
}