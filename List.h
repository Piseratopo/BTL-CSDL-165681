#ifndef LIST_H
#define LIST_H

#include "models.h"

// Đinh nghĩa cấu trúc node
typedef struct SampleNode {
    Sample data;
    struct SampleNode* next;
} SampleNode;

// Khai báo hàm
SampleNode* createSampleNode(Sample sample);
void addSample(SampleNode** head, Sample sample);
void printSampleList(SampleNode* head);
void freeSampleList(SampleNode** head);

#endif