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

void printSampleList(const Sample* head) {
   printf("\n%-20s %-10s %-10s %-10s\n", "Thoi gian", "Tag", "Gia tri", "Don vi");
   printf("----------------------------------------------------------\n");
   const Sample* current = head;
   while (current != NULL) {
      printf("%-20s %-10s %-10.2f %-10s\n",
            current->timestamp,
            current->tag,
            current->value,
            current->unit);
      current = current->next;
   }
   printf("----------------------------------------------------------\n");
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


// Tuan 2_ Tung

//Tìm kiếm theo Tag
void searchByTag(Sample* head, char* searchTag) {
    printf("\n--- KET QUA TIM KIEM TAG: %s ---\n", searchTag);
    printf("%-20s %-10s %-10s %-10s\n", "Thoi gian", "Tag", "Gia tri", "Don vi");
    
    int found = 0;
    Sample* current = head;
    
    while (current != NULL) {
        // So sánh trực tiếp tag
        if (strcmp(current->tag, searchTag) == 0) {
            printf("%-20s %-10s %-10.2f %-10s\n", 
                   current->timestamp, 
                   current->tag, 
                   current->value, 
                   current->unit);
            found++;
        }
        current = current->next;
    }
    
    if (found == 0) printf("(Khong tim thay ket qua nao)\n");
}

// Tìm kiếm theo khoảng thời gian
void searchByTimeRange(Sample* head, char* startTime, char* endTime) {
    printf("\n--- TIM KIEM TU %s DEN %s ---\n", startTime, endTime);
    printf("%-20s %-10s %-10s %-10s\n", "Thoi gian", "Tag", "Gia tri", "Don vi");

    int found = 0;
    Sample* current = head;

    while (current != NULL) {
        // So sánh chuỗi thời gian
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
    
    if (found == 0) printf("(Khong co du lieu)\n");
}

// Xóa theo Timestamp
void deleteByTimestamp(Sample** head, char* targetTime) {
    Sample* current = *head;
    Sample* prev = NULL;

    // Danh sách rỗng
    if (current == NULL) return;

    // Trường hợp xóa đầu danh sách (Head)
    if (strcmp(current->timestamp, targetTime) == 0) {
        *head = current->next; // Cập nhật head mới
        free(current);         // Giải phóng bộ nhớ
        printf("Da xoa mau tai thoi diem: %s\n", targetTime);
        return;
    }

    // Trường hợp xóa ở giữa hoặc cuối
    while (current != NULL && strcmp(current->timestamp, targetTime) != 0) {
        prev = current;
        current = current->next;
    }

    // Không tìm thấy
    if (current == NULL) {
        printf("Khong tim thay mau can xoa!\n");
        return;
    }

    // Thực hiện xóa
    prev->next = current->next;
    free(current);
    printf("Da xoa mau tai thoi diem: %s\n", targetTime);
}

// Chuyển Linked List sang Mảng (Để hỗ trợ Sort)
Sample* listToArray(Sample* head, int* count) {
    // Bước 1: Đếm số lượng
    int n = 0;
    Sample* current = head;
    while (current != NULL) {
        n++;
        current = current->next;
    }
    *count = n;

    if (n == 0) return NULL;

    // Bước 2: Cấp phát mảng động
    Sample* arr = (Sample*)malloc(n * sizeof(Sample));
    if (arr == NULL) return NULL;

    // Bước 3: Copy dữ liệu
    current = head;
    for (int i = 0; i < n; i++) {
        // Copy toàn bộ nội dung struct
        arr[i] = *current; 
        
        // Gán next trong mảng bằng NULL để tránh liên kết không mong muốn
        arr[i].next = NULL; 
        
        current = current->next;
    }

    return arr;
}
