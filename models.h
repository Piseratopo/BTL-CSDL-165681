#ifndef MODELS_H
#define MODELS_H

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

#endif
