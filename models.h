#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNIT_LENGTH 10
#define MAX_TAG_LENGTH 30
#define MAX_TIMESTAMP_LENGTH 50
#define MAX_UNIT_LENGTH 10
#define MAX_DESCRIPTION_LENGTH 200

typedef struct Sample {
   char timestamp[MAX_TIMESTAMP_LENGTH]; // measurement time (e.g., "2025-12-12 10:30")
   char tag[MAX_TAG_LENGTH];             // channel name: T1, P2, I3...
   double value;                         // measured value
   char unit[MAX_UNIT_LENGTH];           // unit: °C, bar, A, V...
   struct Sample* next;                  // pointer to the next Sample
} Sample;

// Create a new sample with the given data
Sample* createSample(const char* timestamp, const char* tag, double value, const char* unit);

// Input a new sample from user
void inputSample(Sample** head);

// Print all samples in the list
void printSamples(const Sample* head);

// Week 1 functions
void addSample(Sample** head, Sample sample);
void printSampleList(const Sample* head);
void freeSampleList(Sample** head);

// Week 2 functions
void searchLinearByTag(const Sample* head, const char* tag);
void searchByTimeRange(Sample* head, char* startTime, char* endTime);
void deleteByTimestamp(Sample** head, char* targetTime);
Sample* listToArray(Sample* head, int* count);

// Week 3 functions
void calculateStatsByTag(const Sample* head, const char* tag);
void saveToCSV(const Sample* head, const char* filename, const char* filterTag);

#endif
