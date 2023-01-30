//
// Created by 王诗涵 on 2023/1/29.
//

#ifndef CTEST_DATAOPERATION_H
#define CTEST_DATAOPERATION_H

#endif //CTEST_DATAOPERATION_H
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char no[12];
    char name[40];
    int term[2];
    float workload[2];
    float total;
    struct Node *Next;
};

/* 比较函数，用于比较链表中两个节点的total字段 */
int compare(struct Node *a, struct Node *b) {
    return a->total - b->total;
}

/* 交换两个节点 */
void swap(struct Node *a, struct Node *b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

/* 冒泡排序 */
void bubbleSort(struct Node *head, int (*compare)(struct Node*, struct Node*)) {
    struct Node *current, *next;
    int swapped;
    if (head == NULL) {
        return;
    }
    do {
        swapped = 0;
        current = head;
        while (current->Next != NULL) {
            next = current->Next;
            if (compare(current, next) > 0) {
                swap(current, next);
                swapped = 1;
            }
            current = current->Next;
        }
    } while (swapped);
}

int main() {
    /* 假设已经有一个链表，并且已经赋值 */
    struct Node *head = ...;

    /* 排序 */
    bubbleSort(head, compare);

    /* 遍历排序后的链表 */
    struct Node *current = head;
    while (current != NULL) {
        printf("%s %s %d %d %f\n", current->no, current->name, current->term[0], current->term[1], current->total);
        current = current->Next;
    }
    return 0;
}
