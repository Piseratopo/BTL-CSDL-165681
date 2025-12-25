#include <stdio.h>
#include <stdlib.h> 
#include "models.h"

int main() {
    Sample* myList = NULL;

    printf("=== DANG KHOI TAO DU LIEU MAU ===\n");

    // 1. Tạo dữ liệu giả
    Sample s1 = {"2025-12-25 10:00", "T1", 25.5, "C"};
    Sample s2 = {"2025-12-25 10:05", "P1", 1.02, "bar"};
    Sample s3 = {"2025-12-25 10:10", "T1", 26.0, "C"};
    Sample s4 = {"2025-12-26 08:00", "V1", 220.0, "V"};
    Sample s5 = {"2025-12-26 09:00", "T2", 24.8, "C"};
    Sample s6 = {"2025-12-26 10:00", "P2", 1.05, "bar"};
    Sample s7 = {"2025-12-26 11:00", "T2", 25.0, "C"};
    Sample s8 = {"2025-12-26 12:00", "V1", 221.0, "V"};
    Sample s9 = {"2025-12-27 10:00", "T1", 27.5, "C"};

    // Hàm này đã có trong models.c bạn gửi -> OK
    addSample(&myList, s1);
    addSample(&myList, s2);
    addSample(&myList, s3);
    addSample(&myList, s4);
    addSample(&myList, s5);
    addSample(&myList, s6);
    addSample(&myList, s7);
    addSample(&myList, s8);
    addSample(&myList, s9);

    printf("\n=== DANH SACH BAN DAU ===\n");
    // Hàm này đã có trong models.c bạn gửi -> OK
    printSampleList(myList);

    // 2. Test Tìm kiếm theo Tag
    searchByTag(myList, "T1");

    // 3. Test Tìm kiếm theo khoảng thời gian
    searchByTimeRange(myList, "2025-12-25 10:00", "2025-12-25 10:05");

    // 4. Test Xóa
    printf("\n>>> Xoa mau tai 2025-12-25 10:05...\n");
    deleteByTimestamp(&myList, "2025-12-25 10:05");
    
    printf("\n=== DANH SACH SAU KHI XOA ===\n");
    printSampleList(myList); 

    // 5. Test chuyển sang Mảng (Để SV3 dùng sau này)
    int n = 0;
    Sample* arr = listToArray(myList, &n);
    printf("\n>>> Da chuyen sang mang voi %d phan tu.\n", n);
    
    // In thử phần tử đầu tiên của mảng để chắc chắn
    if (n > 0) {
        printf("Phan tu dau tien trong mang: %s - %s\n", arr[0].timestamp, arr[0].tag);
    }
    
    // Dọn dẹp
    if (arr != NULL) free(arr);
    freeSampleList(&myList);

    printf("\nChuong trinh chay thanh cong! Bam Enter de thoat.");
    getchar();

    return 0;
}