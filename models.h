#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAG_LENGTH 30
#define MAX_TIME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200

// Alarm struct definition
typedef struct Alarm {
    int  id;                  // mã alarm
    char tag[MAX_TAG_LENGTH];             // thiết bị hoặc kênh liên quan
    char time[MAX_TIME_LENGTH];            // thời điểm xảy ra (chuỗi đơn giản)
    int  priority;            // 1: cao, 2: trung bình, 3: thấp
    char description[MAX_DESCRIPTION_LENGTH];    // mô tả chi tiết
    struct Alarm *next;       // con trỏ tới alarm tiếp theo (linked list)
} Alarm;

// Function prototypes
Alarm* createAlarm(int id, const char* tag, const char* time, int priority, const char* description);
void   inputAlarm(Alarm** head);
void   printAlarms(const Alarm* head);

//Định nghĩa cấu trúc mẫu dữ liệu (THANH TUNG 20232601)

typedef struct {
    char timestamp[20];
    char tag[10];
    double value;
    char unit[10];
} Sample;

#endif
