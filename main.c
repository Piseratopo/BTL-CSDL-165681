#include <stdio.h>
#include "models.h"

int main() {
   Alarm* alarmList = NULL;

   // Input 2 alarms
   inputAlarm(&alarmList);
   inputAlarm(&alarmList);

   // Print all alarms
   printf("\nAlarm list:\n");
   printAlarms(alarmList);

   return 0;
}