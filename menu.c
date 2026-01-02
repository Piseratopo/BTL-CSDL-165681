#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "sort.h"

void displayMainMenu() {
    printf("\n=== SENSOR DATA MANAGEMENT SYSTEM ===\n");
    printf("1. Add new sample\n");
    printf("2. List all samples\n");
    printf("3. Search samples\n");
    printf("4. Sort samples\n");
    printf("5. Build and display BST\n");
    printf("6. Statistics (Min/Max/Avg)\n");
    printf("7. File Operations (Import/Export CSV)\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void handleMenuChoice(int choice, Sample** sampleList, TreeNode** root) {
    switch (choice) {
        case 1:
            addSampleMenu(sampleList);
            break;
        case 2:
            listSamplesMenu(*sampleList);
            break;
        case 3:
            searchSamplesMenu(*sampleList, *root);
            break;
        case 4:
            sortSamplesMenu(sampleList);
            break;
        case 5:
            buildTreeMenu(*sampleList, root);
            break;
        case 6:
            {
            char tag[MAX_TAG_LENGTH];
            printf("Enter Tag to calculate stats: ");
            fgets(tag, sizeof(tag), stdin);
            tag[strcspn(tag, "\n")] = '\0';
            calculateStatsByTag(*sampleList, tag);
            }
            break;
        case 7:
            fileMenu(sampleList);
            break;
        case 0:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void addSampleMenu(Sample** sampleList) {
    printf("\n=== ADD NEW SAMPLE ===\n");
    inputSample(sampleList);
    printf("Sample added successfully!\n");
}

void listSamplesMenu(Sample* sampleList) {
    printf("\n=== ALL SAMPLES ===\n");
    if (sampleList == NULL) {
        printf("No samples found.\n");
        return;
    }
    printSampleList(sampleList);
}

void searchSamplesMenu(Sample* sampleList, TreeNode* root) {
    if (sampleList == NULL) {
        printf("No samples available to search.\n");
        return;
    }

    int choice;
    printf("\n=== SEARCH SAMPLES ===\n");
    printf("1. Search by Tag (History - Linear Search) \n"); // Cách 1: Tìm hết lịch sử
    printf("2. Search by Time Range (Linear Search)    \n"); // Cách 2: Tìm theo giờ
    printf("3. Quick Lookup by Tag (BST Search)        \n"); // Cách 3: Tìm nhanh (BST)
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    char buffer[100]; 

    switch (choice) {
        case 1: 
            printf("Enter Tag to view history: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            searchLinearByTag(sampleList, buffer); 
            break;

        case 2:
            {
                char start[MAX_TIMESTAMP_LENGTH], end[MAX_TIMESTAMP_LENGTH];
                printf("Enter START time (YYYY-MM-DD HH:MM): ");
                fgets(start, sizeof(start), stdin);
                start[strcspn(start, "\n")] = '\0';
                
                printf("Enter END time   (YYYY-MM-DD HH:MM): ");
                fgets(end, sizeof(end), stdin);
                end[strcspn(end, "\n")] = '\0';
                
                searchByTimeRange(sampleList, start, end);
            }
            break;

        case 3: 
            if (root == NULL) {
                printf("Error: BST not built yet. Please choose option 5 in Main Menu first.\n");
            } else {
                printf("Enter Tag to lookup (BST): ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                
              
                TreeNode* result = searchBST(root, buffer);
                
                if (result != NULL) {
                    printf("\n[BST Found] Device exists in system:\n");
                    printf("Timestamp: %s | Tag: %s | Value: %.2f %s\n", 
                           result->data.timestamp, result->data.tag, 
                           result->data.value, result->data.unit);
                } else {
                    printf("\n[BST Result] Tag '%s' not found in tree.\n", buffer);
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
    }
}
void sortSamplesMenu(Sample** sampleList) {
    if (*sampleList == NULL) {
        printf("No samples available to sort.\n");
        return;
    }

    int choice;
    printf("\n=== SORT SAMPLES ===\n");
    printf("1. Sort by timestamp\n");
    printf("2. Sort by value\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline

    // Convert linked list to array for sorting
    int count = 0;
    Sample* samples = listToArray(*sampleList, &count);
    
    if (samples == NULL || count == 0) {
        printf("No samples to sort.\n");
        if (samples) free(samples);
        return;
    }

    switch (choice) {
        case 1:
            sortByTimestamp(samples, count);
            printf("Samples sorted by timestamp.\n");
            break;
        case 2:
            sortByValue(samples, count);
            printf("Samples sorted by value.\n");
            break;
        default:
            printf("Invalid choice.\n");
            free(samples);
            return;
    }

    // Rebuild the linked list
    Sample* newList = NULL;
    Sample* tail = NULL;
    
    for (int i = 0; i < count; i++) {
        Sample* newNode = (Sample*)malloc(sizeof(Sample));
        *newNode = samples[i];
        newNode->next = NULL;
        
        if (newList == NULL) {
            newList = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    // Free old list and update
    freeSampleList(sampleList);
    *sampleList = newList;
    
    // Free the temporary array
    free(samples);
}

void buildTreeMenu(Sample* sampleList, TreeNode** root) {
    if (sampleList == NULL) {
        printf("No samples available to build tree.\n");
        return;
    }

    *root = NULL;
    Sample* current = sampleList;
    int count = 0;
    
    while (current != NULL) {
        *root = insertBST(*root, *current);
        current = current->next;
        count++;
    }
    
    printf("BST built with %d samples.\n", count);
    printf("In-order traversal of BST (sorted by tag):\n");
    printf("%-20s %-10s %-10s %-10s\n", "Timestamp", "Tag", "Value", "Unit");
    printf("----------------------------------------------------------\n");
    inorderPrint(*root);
}

void searchByTag(TreeNode* root) {
    if (root == NULL) {
        printf("BST is not built yet. Please build the tree first.\n");
        return;
    }

    char tag[MAX_TAG_LENGTH];
    printf("Enter tag to search: ");
    fgets(tag, sizeof(tag), stdin);
    tag[strcspn(tag, "\n")] = '\0';

    TreeNode* result = searchBST(root, tag);
    if (result != NULL) {
        printf("\nFound sample:\n");
        printf("Timestamp: %s\n", result->data.timestamp);
        printf("Tag: %s\n", result->data.tag);
        printf("Value: %.2f\n", result->data.value);
        printf("Unit: %s\n", result->data.unit);
    } else {
        printf("No sample found with tag '%s'\n", tag);
    }
}

void searchByTimestamp(Sample* sampleList) {
    if (sampleList == NULL) {
        printf("No samples available.\n");
        return;
    }

    char timestamp[MAX_TIMESTAMP_LENGTH];
    printf("Enter timestamp to search (YYYY-MM-DD HH:MM): ");
    fgets(timestamp, sizeof(timestamp), stdin);
    timestamp[strcspn(timestamp, "\n")] = '\0';

    printf("\nSearch results for timestamp '%s':\n", timestamp);
    printf("%-20s %-10s %-10s %-10s\n", "Timestamp", "Tag", "Value", "Unit");
    printf("----------------------------------------------------------\n");

    int found = 0;
    Sample* current = sampleList;
    while (current != NULL) {
        if (strcmp(current->timestamp, timestamp) == 0) {
            printf("%-20s %-10s %-10.2f %-10s\n",
                  current->timestamp,
                  current->tag,
                  current->value,
                  current->unit);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No samples found with the specified timestamp.\n");
    }
}

void printSampleList(const Sample* head) {
    printf("\n%-20s %-10s %-10s %-10s\n", "Timestamp", "Tag", "Value", "Unit");
    printf("----------------------------------------------------------\n");
    const Sample* current = head;
    while (current != NULL) {
        printf("%-20s %-10s %-10.2f %-10s\n",
              current->timestamp,
              current->tag,
              current->value,
              current->unit);
        current = current->next;
    }
    printf("----------------------------------------------------------\n");
}
void fileMenu(Sample** sampleList) {
    int choice;
    char filename[100];
    char tag[MAX_TAG_LENGTH];

    printf("\n=== FILE OPERATIONS (CSV) ===\n");
    printf("1. Export ALL data to CSV (Xuat tat ca)\n");
    printf("2. Export by TAG to CSV (Bao cao rieng tung kenh) [NANG CAO]\n"); // <--- Thêm dòng này
    printf("3. Import from CSV (Doc tu file)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // Xóa bộ nhớ đệm

    // Nhập tên file cho các chức năng Export/Import
    printf("Nhap ten file (vd: data.csv): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    switch (choice) {
        case 1: // Export All
            if (*sampleList == NULL) {
                printf("Danh sach rong, khong co gi de xuat.\n");
            } else {
                saveToCSV(*sampleList, filename, NULL); // NULL = In hết
            }
            break;
            
        case 2: // Export by Tag (Tính năng bạn đang hỏi)
            if (*sampleList == NULL) {
                printf("Danh sach rong.\n");
            } else {
                printf("Nhap Tag muon in bao cao (vd: T1): ");
                fgets(tag, sizeof(tag), stdin);
                tag[strcspn(tag, "\n")] = '\0';
                
                // Gọi hàm saveToCSV với tham số tag để lọc
                saveToCSV(*sampleList, filename, tag); 
            }
            break;

        case 3: // Import
            importFromCSV(sampleList, filename);
            break;
            
        default:
            printf("Lua chon khong hop le.\n");
    }
}