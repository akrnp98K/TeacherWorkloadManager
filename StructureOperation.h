//
// Created by 王诗涵 on 2023/1/30.
//

#ifndef CTEST_STRUCTUREOPERATION_H
#define CTEST_STRUCTUREOPERATION_H

#endif //CTEST_STRUCTUREOPERATION_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
    char no[12];
    char name[40];
    int term[2];
    float workload[2];
    float total;
    struct Node *Next;
};

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

//链表是否为空
int IsEmpty(List L){
    return L->Next == NULL;
}
//测试节点是否为尾节点
int IsLate(List L) {
    return L->Next == NULL;
}

int IdentificationNumberOrName(char *String) { //判断传入值为工号还是姓名 ｜ 用于查询
    if (String[0] > 'A' && String[0] < 'Z' || String[0] > 'a' && String[0] < 'z') {
        return 1;
    } else {
        return 0;
    }
}

void AddTeacherInformation(List L) {
    Position TemCell;
    TemCell = (List) malloc(sizeof(struct Node));
    if (TemCell == NULL) {
        printf("ERROR");
    } else {
        printf("工号\n");
        scanf("%s", TemCell->no);
        printf("姓名\n");
        scanf("%s", TemCell->name);
        TemCell->term[0] = 1;
        TemCell->term[1] = 2;
        printf("第一学期工作量：\n");
        scanf("%f", &TemCell->workload[0]);
        printf("第二学期工作量：\n");
        scanf("%f", &TemCell->workload[1]);
        TemCell->total = 0;

        TemCell->Next = L->Next;
        L->Next = TemCell;
    }
}

Position Lookup(List L, char *Indexes) {    //查找信息
    Position P = L->Next;
    if (IsEmpty(L)){
        return NULL;
    }
    char *container = malloc(sizeof(40));
    if (IdentificationNumberOrName(Indexes)) {
        strcpy(container, P->name);
    } else {
        strcpy(container, P->no);
    }
    while (P != NULL && strcmp(container, Indexes) != 0) {
        P = P->Next;
    }
    return P;
}

void SetWorkload(List L) { //设置修改教师某学期的工作量
    if (IsEmpty(L)){
        printf("你的表中没有任何数据，无法执行。\n");
        return;
    }
    char *Teacher = (char *) malloc(sizeof(40));
    puts("输入要修改工作量的教师的姓名或编号");
    scanf("%s", Teacher);
    int term = -1;
    Position P;
    P = Lookup(L, Teacher);
    printf("要修改哪一个学期？1 Or 2 Or 3(全部修改)\n"); //选择学期
    scanf("%d", &term);
    while (term > 3 || term < 1)    //判断数据合法性
    {
        printf("This option is not available. Please re-enter\n");
        scanf("%d", &term);
    }

    if (term == 3) {     //全部设置
        printf("第一学期：\n");
        scanf("%f", &P->workload[0]);
        printf("第二学期：\n");
        scanf("%f", &P->workload[1]);
    } else {
        scanf("%f", &P->workload[term - 1]);    //设置某学期的工作量
    }
}

//查找某个教师某个学期的工作量
Position FindWorkload(List L)
{
    if (IsEmpty(L)){
        printf("你的表中没有任何数据，无法执行。\n");
        return NULL;
    }
    char *Indexes = (char *) malloc(sizeof(40));
    if (Indexes == NULL){
        printf("内存分配出现错误\n");
        return NULL;
    }
    puts("输入要查找工作量的教师的姓名或编号");
    scanf("%s", Indexes);
    Position P = Lookup(L, Indexes);
    int term = -1;
    if (P != NULL) {
        printf("你想显示哪一个学期的？ \n(1 Or 2 Or 3(全部显示))\n");
        scanf("%d", &term);
        while (term < 1 || term > 3) {
            printf("Without this option, re-enter\n");
            scanf("%d", &term);
        }
        if (term == 3) {
            printf("Name：%s\n", P->name);
            printf("\t第一学期工作量：%f", P->workload[0]);
            printf("\n\t第二学期工作量：%f", P->workload[1]);
            printf("\n");
        } else {
            printf("姓名：%s", P->name);
            printf("\t工作量 %d：", term, P->workload[term - 1]);
        }
    } else {
        printf("An error occurred in the search. There may not be this person");
    }
}

//删除工作量
void DeleteWorkloadInformation(List L) {
    if (IsEmpty(L)){
        printf("你的表中没有任何数据，无法执行。\n");
        return;
    }
    char *Indexes = (char *) malloc(sizeof(40));
    if (Indexes == NULL){
        printf("内存分配出现错误\n");
        return;
    }
    printf("输入你要删除工作量的教师的姓名或编号：\n");
    scanf("%s", Indexes);
    Position P = Lookup(L, Indexes);
    if (P != NULL) {
        int term = -1;
        printf("你想删除哪一个学期的工作量信息？ 1 Or 2 Or 3(删除所有) \n");
        while (term < 1 || term > 3) {
            printf("This option is not available. Please re-enter.\n");
            scanf("%d", &term);
        }
        if (term == 3) {
            P->workload[0] = 0;
            P->workload[1] = 0;
        } else {
            P->workload[term - 1] = 0;
        }
    } else {
        printf("An error occurred in the search. There may not be this person.\n");
    }
}

//统计教师年度总工作量
void StatisticalWorkload(List L, char *Indexes) {
    if (IsEmpty(L)){
        printf("你的表中没有任何数据，无法执行。\n");
        return;
    }
//    char* Indexes = (char*)malloc(sizeof(40));
//    puts("输入你想要统计工作量信息的教师的姓名或者编号。 如要统计所以教师工作量信息，请输入 \"TotalAll\"");
//    scanf("%s",Indexes);
    if (strcmp(Indexes, "TotalAll") == 0 && L != NULL) {
        Position P = L;
        while (P != NULL) {
            P->total = P->workload[0] + P->workload[1];
            P = P->Next;
        }
    } else {
        Position P = Lookup(L, Indexes);
        if (P != NULL) {
            P->total = P->workload[0] + P->workload[1];
        }
    }
}

//查找目标参数的前一个节点
Position FindPrevious(List L, char *Indexes) {
    Position P;
    P = L;
    char *container = malloc(sizeof(40));
    if (container != NULL){
        if (IdentificationNumberOrName(Indexes)){
            while (P->Next != NULL && strcmp(P->Next->name, Indexes) != 0) {
                P = P->Next;
            }
        } else{
            while (P->Next != NULL && strcmp(P->Next->no, Indexes) != 0) {
                P = P->Next;
            }
        }
    }

    return P;
}

//删除节点
void DeleteNode(List L, char *Indexes) {
    if (IsEmpty(L)){
        printf("你的表中没有任何数据，无法执行。\n");
        return;
    }
    Position P, TemCell;
    P = FindPrevious(L, Indexes);
    if (!IsLate(P)) {
        TemCell = P->Next;
        P->Next = TemCell->Next;
    } else {
        P->Next = NULL;
    }
    if (Lookup(L,Indexes)==NULL){
        puts("删除成功....");
    } else{
        printf("删除失败.....");/**/
    }
}

//删除表
void DeleteList(List L){
    Position P,Tmp;
    P=L->Next;
    L->Next = NULL;
    while (P != NULL){
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}

/* 比较函数，用于比较链表中两个节点的total字段 */
int compare(struct Node *a, struct Node *b) {
    return a->total - b->total;
}

//排序部分
struct Node* merge(struct Node* head1, struct Node* head2) {
    struct Node* dummyHead = malloc(sizeof(struct Node));
    dummyHead->total = 0;
    struct Node *temp = dummyHead, *temp1 = head1, *temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->total <= temp2->total) {
            temp->Next = temp1;
            temp1 = temp1->Next;
        } else {
            temp->Next = temp2;
            temp2 = temp2->Next;
        }
        temp = temp->Next;
    }
    if (temp1 != NULL) {
        temp->Next = temp1;
    } else if (temp2 != NULL) {
        temp->Next = temp2;
    }
    return dummyHead->Next;
}

//排序函数
struct Node* sortList(struct Node* head) {
    if (head == NULL) {
        return head;
    }
    int length = 0;
    struct Node* node = head;
    while (node != NULL) {
        length++;
        node = node->Next;
    }
    struct Node* dummyHead = malloc(sizeof(struct Node));
    dummyHead->Next = head;
    for (int subLength = 1; subLength < length; subLength <<= 1) {
        struct Node *prev = dummyHead, *curr = dummyHead->Next;
        while (curr != NULL) {
            struct Node* head1 = curr;
            for (int i = 1; i < subLength && curr->Next != NULL; i++) {
                curr = curr->Next;
            }
            struct Node* head2 = curr->Next;
            curr->Next = NULL;
            curr = head2;
            for (int i = 1; i < subLength && curr != NULL && curr->Next != NULL;
                 i++) {
                curr = curr->Next;
            }
            struct Node* next = NULL;
            if (curr != NULL) {
                next = curr->Next;
                curr->Next = NULL;
            }
            struct Node* merged = merge(head1, head2);
            prev->Next = merged;
            while (prev->Next != NULL) {
                prev = prev->Next;
            }
            curr = next;
        }
    }
    return dummyHead->Next;
}


//总工作量排序
Position RankingTotalWorkload(List L){
    StatisticalWorkload(L,"TotalAll");
    sortList(L);
    return L;
}

//打印教师信息
void Print_(Position P){
    printf("\n\t\t姓名：%s"
           "\n\t\t工号：%s"
           "\n\t\t第%d学期工作量：%f"
           "\n\t\t第%d学期工作量：%f"
           "\n\t\t总工作量：%f",
           P->name,
           P->no,
           P->term[0],
           P->workload[P->term[0]-1],
           P->term[1],
           P->workload[P->term[1]-1],
           P->total);
}
void PrintInformation(List L,char * Indexes){
    Position P = L;
    if (strcmp(Indexes,"All")==0){
        P=P->Next;
        while (P != NULL){
            Print_(P);
            P=P->Next;
        }
    } else{
        Print_(P);
    }
}

//选项菜单函数
void MenuHelp(){
    printf("\n选择你要进行的操作：\n"
           "\t\t1.录入教师信息\n"
           "\t\t2.查找教师工作量信息\n"
           "\t\t3.修改教师工作量信息\n"
           "\t\t4.删除教师工作量信息\n"
           "\t\t5.统计年度总工作量\n"
           "\t\t6.显示工作量排名\n"
           "\t\t7.删除教师信息\n");
}
void menu(){
    printf("START......\n");
    List Head, ptr, new;
    ptr = (List) malloc(sizeof(struct Node));
    if (ptr == NULL){
        printf("内存分配未完成！⚠");
        exit(-1);
    }
    Head = ptr;
    ptr->Next = NULL;
    MenuHelp();
    int Operator = 0;
    scanf("%d",&Operator);
    char* Index = (char*)malloc(sizeof(40));
    while (Operator != -1) {
        switch (Operator) {
            case 1:
                AddTeacherInformation(Head);
                break;
            case 2:
                FindWorkload(Head);
                break;
            case 3:
                SetWorkload(Head);
                break;
            case 4:
                DeleteWorkloadInformation(Head);
                break;
            case 5:
                puts("输入你想要统计工作量信息的教师的姓名或者编号。 如要统计所以教师工作量信息，请输入 \"TotalAll\"");
                scanf("%s", Index);
                StatisticalWorkload(Head, Index);
                break;
            case 6:
                RankingTotalWorkload(Head);
                PrintInformation(Head, "All");
                break;
            case 7:
                puts("输入你想要删除的教师的姓名或者编号\n");
                scanf("%s", Index);
                DeleteNode(Head,Index);
                break;
            case -1:
                exit(0);
            default:
                printf("没有此选项\n");
        }
        MenuHelp();
        scanf("%d",&Operator);
    }
    system("cls");
    //system("clear");
}