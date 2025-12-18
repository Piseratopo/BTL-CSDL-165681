#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Tạo node mới (Cấp phát động)
SampleNode* createSampleNode(Sample sample) {
    SampleNode* newNode = (SampleNode*)malloc(sizeof(SampleNode));
    if (newNode == NULL) {
        printf("Loi them note!\n");
        exit(1);
    }
    newNode->data = sample;
    newNode->next = NULL;
    return newNode;
}

// Thêm node vào cuối danh sách
void addSample(SampleNode** head, Sample sample) {
    SampleNode* newNode = createSampleNode(sample);
    if (*head == NULL) {
        *head = newNode;
    } else {
        SampleNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// In danh sách mẫu dữ liệu
void printSampleList(SampleNode* head) {
    printf("\n%-20s %-10s %-10s %-10s\n", "Thoi gian", "Tag", "Gia tri", "Don vi");
    printf("----------------------------------------------------------\n");
    SampleNode* current = head;
    while (current != NULL) {
        printf("%-20s %-10s %-10.2f %-10s\n", 
               current->data.timestamp, current->data.tag, 
               current->data.value, current->data.unit);
        current = current->next;
    }
    printf("----------------------------------------------------------\n");
}

// Giải phóng bộ nhớ danh sách
void freeSampleList(SampleNode** head) {
    SampleNode* current = *head;
    SampleNode* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}