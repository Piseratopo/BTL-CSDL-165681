#include <stdio.h>
#include "list.h"

int main() {
    SampleNode* myLogger = NULL;

    // 1. Tạo dữ liệu giả lập
    Sample s1 = {"2024-12-18 08:00", "TEMP_01", 30.5, "C"};
    Sample s2 = {"2024-12-18 08:05", "PRES_01", 2.1, "bar"};
    Sample s3 = {"2024-12-18 08:10", "VOLT_M",  220.0, "V"};
    Sample s4 = {"2024-12-18 08:15", "TEMP_01", 31.2, "C"};
    Sample s5 = {"2024-12-18 08:20", "PRES_01", 2.3, "bar"};
    Sample s6 = {"2024-12-18 08:25", "VOLT_M",  219.5, "V"};
    Sample s7 = {"2024-12-18 08:30", "TEMP_01", 32.0, "C"};
    Sample s8 = {"2024-12-18 08:35", "PRES_01", 2.4, "bar"};
    Sample s9 = {"2024-12-18 08:40", "VOLT_M",  221.0, "V"};
    
    // 2. Thêm vào danh sách liên kết
    addSample(&myLogger, s1);
    addSample(&myLogger, s2);
    addSample(&myLogger, s3);
    addSample(&myLogger, s4);
    addSample(&myLogger, s5);
    addSample(&myLogger, s6);
    addSample(&myLogger, s7);
    addSample(&myLogger, s8);
    addSample(&myLogger, s9);

    // 3. In ra để xem kết quả
    printSampleList(myLogger);

    // 4. Dọn dẹp bộ nhớ
    freeSampleList(&myLogger);
    return 0;
}