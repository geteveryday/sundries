#include <stdio.h>
#include <stdlib.h>

//设计进程结构体
struct PCB 
{
    char name[10];//以十个字符作为字符串储存进程名字
    int super;//用一个int类型储存优先级
    int needtime;//进程需要的时间
    int finish;//当进程完成时记录进程时间
    int entertime;//记录进入顺序
};

//设计进程初始化函数
void init(int num, struct PCB** jingcheng);
//设计输出函数
void outputjingcheng(struct PCB** p);
//设计进程运行函数、
void go(int num, struct PCB** jingcheng, int* time);


int main() 
{
    int num, time = 0;//num为进程数量,time记录进程时间
    printf("请输入进程数量：");
    scanf_s("%d", &num);
    struct PCB* jingcheng=NULL;
    init(num,&jingcheng);//初始化进程
    go(num, &jingcheng, &time);//运行函数
    
    return 0;
}


//设计进程初始化函数
void init(int num, struct PCB** jingcheng)
{
    *jingcheng = malloc(num * sizeof(struct PCB));
    if (*jingcheng == NULL)
    {
        printf("内存申请失败\n");
        exit(1);
    }
    for (int i = 0; i < num; i++)
    {
        printf("请输入进程名：\n");
        scanf_s("%s", (*jingcheng)[i].name, sizeof((*jingcheng)[i].name));
        printf("请输入进程优先级：\n");
        scanf_s("%d", &(*jingcheng)[i].super);
        printf("请输入进程需要的时间：\n");
        scanf_s("%d", &(*jingcheng)[i].needtime);
        (*jingcheng)[i].finish = 0;
        (*jingcheng)[i].entertime = i;
    }

}
//设计输出函数
void outputjingcheng(struct PCB** p)
{
    printf("当前执行的进程\t进程剩余的时间\n");
    printf("%-s           \t%-7d\n", (*p)->name, (*p)->needtime);
}
//设计进程运行函数
void go(int num, struct PCB** jingcheng, int* time)
{
    struct PCB* p = NULL;//创建一个函数内指针
    while (1)
    {
        int i;
        for (i = 0; i < num; i++)//循环找到一个还需要运行时间的结构体
        {
            if ((*jingcheng)[i].needtime != 0)
            {
                p = &(*jingcheng)[i];
                break;//如果有还没有完成的进程，就把其赋给p指针，然后退出循环
            }
        }
        if (p == NULL)
        {
            printf("进程已经完成！\n");//因为所有进程的needtime都为0，则p不会被赋值，则还为空
            printf("是否打印进程结束时间情况？（输入0不打印，非0打印）");
            int booler = 0;
            scanf_s("%d", &booler);
            if (booler)
            {
                system("cls||clear");//先清空屏幕（使用系统调用，cls||clear这个写法可以兼容windows，linux和MacOS）
                printf("进程名\t结束时间\n");
                for (int i = 0; i < num; i++)
                {
                    printf("%s    \t%d\n", (*jingcheng)[i].name, (*jingcheng)[i].finish);
                }
            }
            exit(1);//结束程序
        }

        for (; i < num; i++)
        {
            if ((*jingcheng)[i].needtime != 0 && (*jingcheng)[i].super < p->super)
            {//如果存在一个进程还没执行完并且优先级更高
                p = &(*jingcheng)[i];//就把指针指向他，现在，p执行的就是目前执行的进程一号位
            }
        }
        p->needtime -= 1;//时间片使进程时间减一
        (*time)++;
        if (p->needtime == 0)//进程结束
        {
            p->finish = *time;
            printf("进程%s已完成！\n", p->name);
        }
        outputjingcheng(&p);//输出进程的情况函数
        p = NULL;//指针使用完要归到空指针，防止野指针
    }

}