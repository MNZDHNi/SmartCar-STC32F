#include "List.h"

void List_5_Init(List_5* list) {
    int i;
    for (i = 0; i < 5; i++) {
        list->arr[i] = 0;
    }
    list->p = 0;
}

void List_5_Append(List_5* list, unsigned int value) {
    if (list->p == 5) {
        list->p = 0;
    }
    if (list->p < 5) {
        list->arr[list->p] = value;
        list->p++;
    }
}

unsigned int List_5_Read(List_5* list) {
    int i = list->p + 1;
    if (i == 5) {
        i = 0;
    }
    return list->arr[i];
}