#ifndef MODELS_H
#define MODELS_H

// Alarm struct definition
typedef struct Alarm {
    int  id;                  // mã alarm
    char tag[20];             // thiết bị hoặc kênh liên quan
    char time[20];            // thời điểm xảy ra (chuỗi đơn giản)
    int  priority;            // 1: cao, 2: trung bình, 3: thấp
    char description[100];    // mô tả chi tiết
    struct Alarm *next;       // con trỏ tới alarm tiếp theo (linked list)
} Alarm;

// Function prototypes
Alarm* createAlarm(int id, const char* tag, const char* time, int priority, const char* description);
void   inputAlarm(Alarm** head);
void   printAlarms(const Alarm* head);

#endif
