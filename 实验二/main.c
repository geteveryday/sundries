#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
// 资源结构体
struct ziyuan {
    int size;
    int* num;
};
// 进程结构体
struct jincheng {
    char name[20];      // 进程名字
    int* max;           // 储存进程对应资源的最大需求量
    int* allocated;     // 储存已分配的资源量
    bool finished;      // 标记进程是否完成
};
// 初始化资源个数的函数
void initZiyuan(struct ziyuan* ziYuan) {
    printf("请输入资源个数：");
    int size;
    scanf("%d", &size);
    ziYuan->num = (int*)malloc(size * sizeof(int));
    if (ziYuan->num == NULL) {
        printf("内存分配失败！");
        exit(1);
    }
    ziYuan->size = size;
    for (int i = 0; i < size; i++) {
        printf("请输入资源%d的大小：", i);
        scanf("%d", &(ziYuan->num[i]));
    }
}

// 初始化进程的函数
int initjincheng(struct jincheng** JINCHENG, int num) {
    printf("请输入进程的个数：\n");
    int size = 0;
    scanf("%d", &size);
    *JINCHENG = (struct jincheng*)malloc(size * sizeof(struct jincheng));
    if (*JINCHENG == NULL) {
        printf("内存分配失败！");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        (*JINCHENG)[i].max = (int*)malloc(sizeof(int) * num);
        (*JINCHENG)[i].allocated = (int*)malloc(sizeof(int) * num);
        if ((*JINCHENG)[i].max == NULL || (*JINCHENG)[i].allocated == NULL) {
            printf("内存分配失败！");
            exit(1);
        }
    }
    for (int i = 0; i < size; i++) {
        printf("请输入进程%d的名字：", i);
        scanf("%19s", (*JINCHENG)[i].name);
        for (int j = 0; j < num; j++) {
            printf("请输入进程%s的%d资源的最大需求量：", (*JINCHENG)[i].name, j);
            scanf("%d", &(*JINCHENG)[i].max[j]);
        }
        // 手动输入占用的资源量
        printf("请输入进程%s当前已经占用的资源量：", (*JINCHENG)[i].name);
        for (int j = 0; j < num; j++) {
            printf("资源%d的占用量：", j);
            scanf("%d", &(*JINCHENG)[i].allocated[j]);
        }
        (*JINCHENG)[i].finished = false;
    }
    return size;
}
//核心函数，银行家算法实现

   // 核心函数，银行家算法实现
void go(struct ziyuan* ziYuan, struct jincheng* JINCHENG, int num_processes, int num_resources) {
    int* available = ziYuan->num;
    int** need = (int**)malloc(num_processes * sizeof(int*));
    int** allocation = (int**)malloc(num_processes * sizeof(int*));
    bool* finished = (bool*)malloc(num_processes * sizeof(bool));

    for (int i = 0; i < num_processes; ++i) {
        need[i] = (int*)malloc(num_resources * sizeof(int));
        allocation[i] = (int*)malloc(num_resources * sizeof(int));
        finished[i] = false;
        for (int j = 0; j < num_resources; ++j) {
            need[i][j] = JINCHENG[i].max[j] - JINCHENG[i].allocated[j];
            allocation[i][j] = JINCHENG[i].allocated[j];
        }
    }

    int* execution_order = (int*)malloc(num_processes * sizeof(int)); // 动态分配 execution_order 数组

    printf("请输入要执行的进程顺序（0 到 %d），每个进程之间用空格分隔：\n", num_processes - 1);
    for (int i = 0; i < num_processes; ++i) {
        scanf_s("%d", &execution_order[i]);
        if (execution_order[i] < 0 || execution_order[i] >= num_processes) {
            printf("无效的进程索引，请重新输入。\n");
            i--;
        }
    }

    bool deadlock_detected = false;
    int deadlock_count = 0;
    int max_deadlock_attempts = 5; // 设置尝试解除死锁的最大次数

    while (deadlock_count < max_deadlock_attempts) {
        for (int i = 0; i < num_processes; ++i) {
            int process_index = execution_order[i];
            printf("运行进程%s...\n", JINCHENG[process_index].name);

            bool can_allocate = true;
            for (int j = 0; j < num_resources; ++j) {
                if (need[process_index][j] > available[j]) {
                    can_allocate = false;
                    break;
                }
            }
            if (can_allocate) {
                for (int j = 0; j < num_resources; ++j) {
                    available[j] -= need[process_index][j];
                    allocation[process_index][j] += need[process_index][j];
                }
                printf("进程分配的资源：\n");
                for (int i = 0; i < num_processes; ++i)
                {
                    printf("进程%s：", JINCHENG[i].name);
                    for (int j = 0; j < num_resources; ++j) {
                        printf("%d ", allocation[i][j]);
                    }
                    printf("\n");
                }

                printf("进程%s分配并释放资源：\n", JINCHENG[process_index].name);
                printf("\n");

                for (int j = 0; j < num_resources; ++j) {
                    available[j] += JINCHENG[process_index].allocated[j] + JINCHENG[process_index].max[j];
                    allocation[process_index][j] = 0;
                }
                printf("释放后的资源：\n");
                for (int i = 0; i < num_processes; i++)
                {
                    printf("%d ", available[i]);
                }
                finished[process_index] = true;
            }
            else {
                printf("无法为进程%s分配资源，进程%s处于等待状态，发生死锁！\n", JINCHENG[process_index].name, JINCHENG[process_index].name);
                printf("当前系统状态：\n");
                printf("可用资源：");
                for (int j = 0; j < num_resources; ++j) {
                    printf("%d ", available[j]);
                }
                printf("\n");

                printf("进程分配的资源：\n");
                for (int i = 0; i < num_processes; ++i) {
                    printf("进程%s：", JINCHENG[i].name);
                    for (int j = 0; j < num_resources; ++j) {
                        printf("%d ", allocation[i][j]);
                    }
                    printf("\n");
                }

                deadlock_detected = true;
                break;
            }
        }

        if (!deadlock_detected) {
            printf("未发生死锁。\n");
            break;
        }
        else {
            printf("发生死锁，尝试重新选择进程顺序...\n");
            // 重新选择进程顺序
            for (int i = 0; i < num_processes; ++i) {
                execution_order[i] = (execution_order[i] + 1) % num_processes;
            }
            deadlock_count++;
            deadlock_detected = false;
        }
    }

    if (deadlock_count == max_deadlock_attempts) {
        printf("达到最大死锁解除尝试次数，可能无法解除死锁。\n");
    }

    // 释放动态分配的数组内存
    free(execution_order);
    for (int i = 0; i < num_processes; ++i) {
        free(need[i]);
        free(allocation[i]);
    }
    free(need);
    free(allocation);
    free(finished);
}


int main() {
    struct ziyuan ziYuan;
    initZiyuan(&ziYuan);
    struct jincheng* JINCHENG;
    int size = initjincheng(&JINCHENG, ziYuan.size);
    go(&ziYuan, JINCHENG, size, ziYuan.size);
    return 0;
}
