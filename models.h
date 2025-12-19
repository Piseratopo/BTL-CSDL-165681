#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAG_LENGTH 30
#define MAX_TIME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200

typedef struct Sample {
    char timestamp[MAX_TIMESTAMP_LENGTH]; // thời gian đo (vd: "2025-12-12 10:30")
    char tag[MAX_TAG_LENGTH];             // tên kênh đo: T1, P2, I3...
    double value;                         // giá trị đo
    char unit[MAX_UNIT_LENGTH];           // đơn vị: °C, bar, A, V...
    struct Sample* next;                  // con trỏ tới Sample tiếp theo
} Sample;

Sample* createSample(const char* timestamp, const char* tag, double value, const char* unit);
void    inputSample(Sample** head);
void    printSamples(const Sample* head);

#endif
