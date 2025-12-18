#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Định nghĩa cấu trúc mẫu dữ liệu (THANH TUNG 20232601)

typedef struct {
    char timestamp[20];
    char tag[10];
    double value;
    char unit[10];
} Sample;

#endif
