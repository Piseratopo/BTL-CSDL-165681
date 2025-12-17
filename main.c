#include <stdio.h>
#include "models.h"

int main() {
   Alarm* alarmList = NULL;

   // Input 2 alarms
   inputAlarm(&alarmList);
   inputAlarm(&alarmList);

   // Print all alarms
   printf("\nDanh sách Alarm:\n");
   printAlarms(alarmList);

   return 0;
}