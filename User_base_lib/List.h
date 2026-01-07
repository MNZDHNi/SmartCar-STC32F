#ifndef __USER_BASE_LIB_LIST_H__
#define __USER_BASE_LIB_LIST_H__

typedef struct {
    unsigned int arr[5];
    char p;
} List_5;

void List_5_Init(List_5* list);
void List_5_Append(List_5* list, unsigned int value);
unsigned int List_5_Read(List_5* list);
unsigned int List_5_Average(List_5* list);

#endif