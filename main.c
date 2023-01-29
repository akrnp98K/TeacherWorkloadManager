//教师工作量管理系统
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
//定义一个教师结构体
typedef struct teacher//定义储存教师工作量信息的结构体
{
    char no[12];/*教师工号*/
    char name[40];/*姓名*/
    int term[2];/*学期*/
    char workload[60];/*工作量*/
    float total;/*年度工作量总结*/
    struct teacher*link;/*指向下一结点的指针*/
}STU;//后面可以用STU定义变量或是数组存放教师工作量信息


//函数声明
void Llstlnit(STU* L,char*);//创建表头，初始化链表
STU* ListCreate(STU*L,int n);//创建链表，将新生成的节点插入到链表的表头
void Listlnsert(STU*L);//插入教师的相关信息的函数
void ListDelete(STU*L, char n[40]);//删除某个教师的信息的函数
void LlstSearch(STU* L, char n[]);//查找教师的相关信息的函数
void input(STU* p, int i);//录入某个教师的信息的函数
void output(STU*L);//输出教师信息的函数
void menu();//菜单函数
//创建表头，初始化链表
STU* LIstlnit(STU*L)
{
    STU* head = NULL;
    head=(STU*)malloc(sizeof(STU));
    head->link=NULL;
    L= head;
    return L;
}
//创建链表，将新生成的节点插入到链表的表头
STU* ListCreate(STU* L, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        STU*p;
//将新生成的节点插入到链表中
        p= NULL;
        p= (STU*)malloc(sizeof(STU));
        input(p, i);
        p->link=L->link;
        L->link=p;


    }
    return L;
}

//对链表的进行节点的删除操作
void ListDelete(STU*L,char n[])//删除某个学生的信息的函数
{
    STU* p=L->link,*pre =L;//定义p指针指向头结点的指向，定义pre指向头结点，pre始终指向p的前驱节点
    if (p== NULL)
//定义p指针指向头节点的指向，定义pre指向头节
        printf("数据为空，无法删除!");
    else
    {
        while (strcmp(p->name, n)!= 0)
        {
            pre= p;
            p=pre->link;
            if (p== NULL)
            {

                printf("没有找到相关信息，无法删除\n");//判断文件是否存在，是否除成功
                return;
            }
        }
        pre->link= p->link;
        free(p);
        printf("删除成功");
    }
}
void Llstlnit(STU*L, char n[])//查找某个学生的信息的函数
{
    STU* p= L->link;
    if (p==NULL)
        printf("数据为空，无法查找！");
    else
    {
        while (strcmp(p->name, n)!= 0)
        {
            p=p->link;
            if (p==NULL)
            {
                printf("没有找到相关信息\n");//判断文件是否存在，是否查找成功
                return;
            }
        }
        printf("该教师的工作量信息为:\n");
        printf("\t%s\n", p->workload);
    }
    return p;
}
void ListModify(STU* L, char na[])//修改某个教师工作量的信息的函数
{
    char wk[60];
    STU* p=L->link;
    while (p != NULL)
    {
        if(strcmp(p->name,na)==0);
        {
            printf("请选择您修改后的学生籍贯:\n");
            scanf("%s",&wk);
            strcpy(p->workload,wk);
            break;
        }
        p=p->link;
    }
}
void input(STU*p,int i)//录入教师工作量的函数
{
    printf("请输入第%d名教师的工号:",i+ 1);
    scanf("%s", &p->no);
    printf("请输入第%d名教师的姓名:",i+ 1);
    scanf("%s", &p->name);
    printf("请输入第%d教师的工作量:",i+ 1);
    scanf("%s",&p->workload);
    printf("请输入第%d教师的总工作量",i+ 1);
    scanf("%s", &p->total);
    printf("请输入第%d教师的学期:",i+ 1);
    scanf("%s", &p->term);

}
void output(STU*L)//输出函数
{
    STU*p= L->link;
    while (p!= NULL)
    {
        printf("%s\t", p->no);
        printf("%s\t",p->name);
        printf("\t%s", p->workload);
        printf("\t\t%s", p->total);
        printf("\t%s", p->term);
        printf("\n");
        p=p->link;
    }
}
void PrintFile(STU*L)//保存学生信息的函数
{
    STU*p=L->link;
    FILE* fp;
    fp = fopen("student.txt","w");
    fprintf(fp,"学号\t\t姓名\t\t电话号码ItIt身份证号码\t\t籍贯\t\t通讯地址\n");
    while (p!= NULL)
    {
        printf("%s\t",p->no);
        printf("%s\t",p->name);
        printf("\t%s",p->workload);
        printf("\t\t%s",p->total);
        printf("\t%s", p->term);
        printf("\n");
        p= p->link;
    }
    printf("保存成功，请到当前目录下的student.txt文件中查看");
    fclose(fp);
}
void menu()//菜单函数
{
    printf("\n\n");
    printf("\t\t\t******************学生籍贯管理系统************************\n");
    printf("\tltlt*作者:魏永雷，班级:数据科学221学号:3220706134 *\n");
    printf("\t\t\t*                                                        *\n");
    printf("\t\t\t*      <1>.录入教师工作量信息           *\n");
    printf("\t\t\t*      <2>.查找教师工作量信息           *\n");
    printf("\t\t\t*      <3>.修改教师工作量信息           *\n");
    printf("\t\t\t*      <4>.删除教师工作量信息           *\n");
    printf("\t\t\t*      <5>.保存教师工作量信息           *\n");
    printf("\t\t\t*      <6>.对教师工作量进行排序           *\n");
    printf("\t\t\t*      <7>.统计教师总工作量信息           *\n");
    printf("\t\t\t*      <0>.退出管理系统          *\n");
    printf("\t\t\t*                                         欢迎使用本系统！ *\n");
    printf("\t\t\t********************************************************\n");
    printf("\t\t\t输入选项，按回车进入选项：                               \n");
}
int main()
{
    int item,n;
    char nam[30];
    STU*L=NULL;
    L= Llstlnit(L);
    do
    {
        menu();
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        switch (item)//switch语句编写菜单选项
        {
            case 1:
                printf("请输入您要录入的学生人数·");
                scanf("%d", &n);
                L= ListCreate(L, n);
                break;
            case 2:
                printf("全部学生信息如下:\n");
                printf("学号\tIt姓名\t\t电话号码\tIt身份证号码\t\t籍贯\tIt通讯地址\n");
                output(L);
                break;
            case 3:
                printf("请输入您要查找的教师名字:");
                scanf("%s", nam);
            case 4:
                printf("请输入您要修改的教师工作量:");
                scanf("%s",nam);
                ListModify(L, nam);
                break;
            case 5:
                printf("请输入您要删除的教师工作:");
                scanf("%s", nam);
                ListDelete(L, nam);
                break;
            case 6:
                PrintFile(L);
                break;
            case 0:
                printf("即将退出教师工作量管理系统……");
                exit(0);
            default:
                break;
        }
        printf("\n\n\n\n");
    } while (item);
    return 0;
}