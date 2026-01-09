#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "models.h"
#include "sort.h"
#include "tree.h"

// --- UTILITIES ---
void printHeader(const char* title) {
    printf("\n==========================================================\n");
    printf("   %s\n", title);
    printf("==========================================================\n");
}

void printSubHeader(const char* title) {
    printf("\n--- %s ---\n", title);
}

// --- DATA GENERATION ---
// Tạo bộ dữ liệu giả lập phong phú hơn (15 mẫu)
void generateMockData(Sample** head) {
    Sample dataset[] = {
        // Cảm biến Nhiệt độ (TEMP_01) - 5 mẫu
        {"2025-12-12 08:00", "TEMP_01", 25.5, "C", NULL},
        {"2025-12-12 09:00", "TEMP_01", 26.0, "C", NULL},
        {"2025-12-12 10:00", "TEMP_01", 28.5, "C", NULL}, // Đỉnh nhiệt
        {"2025-12-12 11:00", "TEMP_01", 27.2, "C", NULL},
        {"2025-12-12 12:00", "TEMP_01", 26.8, "C", NULL},

        // Cảm biến Áp suất (PRES_01) - 4 mẫu
        {"2025-12-12 08:05", "PRES_01",  1.2, "bar", NULL},
        {"2025-12-12 09:05", "PRES_01",  2.5, "bar", NULL}, // Đỉnh áp
        {"2025-12-12 10:05", "PRES_01",  1.8, "bar", NULL},
        {"2025-12-12 11:05", "PRES_01",  1.1, "bar", NULL},

        // Cảm biến Điện áp (VOLT_01) - 4 mẫu - Có sự cố sụt áp
        {"2025-12-12 08:30", "VOLT_01", 220.0, "V", NULL},
        {"2025-12-12 09:30", "VOLT_01", 219.5, "V", NULL},
        {"2025-12-12 10:30", "VOLT_01", 180.0, "V", NULL}, // Sụt áp
        {"2025-12-12 11:30", "VOLT_01", 221.0, "V", NULL},
        
        // Dữ liệu nhiễu/Lẻ tẻ
        {"2025-12-12 10:15", "HUMID_02", 60.5, "%", NULL},
        {"2025-12-13 01:00", "TEMP_01", 20.0, "C", NULL}  // Ngày hôm sau
    };

    size_t count = sizeof(dataset) / sizeof(dataset[0]);
    for (size_t i = 0; i < count; ++i) {
        addSample(head, dataset[i]);
    }
   printf("[INFO] Generated %d mock samples.\n", (int)count);
}

// --- TEST SCENARIO 1: DATA MANAGEMENT ---
void test_CoreFeatures(Sample* head) {
    printHeader("TEST SCENARIO 1: CORE FUNCTIONS & STATS (SV2)");

    // 1. In danh sách gốc
    printSubHeader("1. Full Data List (Linked List Traversal)");
    printSampleList(head);

    // 2. Test Tìm kiếm tuyến tính (Lịch sử đo)
    printSubHeader("2. Linear Search by Tag (History)");
    printf("[TEST] Searching for tag 'TEMP_01' (Expected: 6 records)...\n");
    searchLinearByTag(head, "TEMP_01");

    printf("\n[TEST] Searching for tag 'UNKNOWN' (Expected: Not found)...\n");
    searchLinearByTag(head, "UNKNOWN");

    // 3. Test Tìm kiếm theo khoảng thời gian
    printSubHeader("3. Search by Time Range");
    char* start = "2025-12-12 09:00";
    char* end   = "2025-12-12 11:00";
    printf("[TEST] Range: %s to %s\n", start, end);
    searchByTimeRange(head, start, end);

    // 4. Test Thống kê (Nâng cao)
    printSubHeader("4. Statistics (Min/Max/Avg)");
    printf("[TEST] Calculate stats for 'TEMP_01'...\n");
    calculateStatsByTag(head, "TEMP_01");

    printf("\n[TEST] Calculate stats for 'VOLT_01'...\n");
    calculateStatsByTag(head, "VOLT_01");
}

// --- TEST SCENARIO 2: ALGORITHMS (SV3 Focus) ---
void test_Algorithms(Sample* head) {
    printHeader("TEST SCENARIO 2: ALGORITHMS & BST (SV3)");

    // Chuẩn bị dữ liệu mảng để sort
    int count = 0;
    Sample* arr = listToArray(head, &count);
    
    // 1. Test Sorting
    printSubHeader("1. Sorting Algorithms");
    
    // Clone mảng để test sort value
    Sample* arrVal = (Sample*)malloc(count * sizeof(Sample));
    memcpy(arrVal, arr, count * sizeof(Sample));

    printf("[TEST] Sorting by Timestamp (Ascending)...\n");
    sortByTimestamp(arr, count);
    printf("Top 3 samples after sort:\n");
    for(int i=0; i<3 && i<count; i++) printf("  %s - %s\n", arr[i].timestamp, arr[i].tag);

    printf("\n[TEST] Sorting by Value (Ascending)...\n");
    sortByValue(arrVal, count);
    printf("Top 3 samples after sort (Min values):\n");
    for(int i=0; i<3 && i<count; i++) printf("  %.2f - %s (%s)\n", arrVal[i].value, arrVal[i].tag, arrVal[i].timestamp);

    // 2. Test BST
    printSubHeader("2. Binary Search Tree (BST)");
    TreeNode* root = buildBSTFromList(head);
    printf("[TEST] BST Built. Performing In-order Traversal (Sorted by Tag)...\n");
    inorderPrint(root);

    // 3. Test BST Search
    printSubHeader("3. BST Lookup (Quick Existence Check)");
    char* targets[] = {"PRES_01", "HUMID_02", "GHOST_TAG"};
    for (int i = 0; i < 3; i++) {
        printf("Looking up '%s'... ", targets[i]);
        TreeNode* res = searchBST(root, targets[i]);
        if (res) printf("[FOUND] Val: %.2f\n", res->data.value);
        else printf("[NOT FOUND]\n");
    }

    // Cleanup
    free(arr);
    free(arrVal);
    // Lưu ý: Không free root ở đây để đơn giản hóa demo, OS sẽ dọn dẹp
}

// --- MAIN DRIVER ---
int main(int argc, char* argv[]) {
    Sample* loggerHead = NULL;
    
    // 1. Setup Data
    generateMockData(&loggerHead);

    int runPart1 = 1;
    int runPart2 = 1;

    // Xử lý tham số dòng lệnh
    if (argc > 1) {
        if (strcmp(argv[1], "core") == 0) { runPart2 = 0; }
        else if (strcmp(argv[1], "algo") == 0) { runPart1 = 0; }
    }

    // 2. Run Tests
    if (runPart1) test_CoreFeatures(loggerHead);
    if (runPart2) test_Algorithms(loggerHead);

    // 3. Cleanup List
    freeSampleList(&loggerHead);

    // Giữ màn hình để xem kết quả
    printf("\n==========================================================\n");
    printf("Tests Completed. Press Enter to exit...");
    getchar();

    return 0;
}