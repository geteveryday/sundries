#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
// ��Դ�ṹ��
struct ziyuan {
    int size;
    int* num;
};
// ���̽ṹ��
struct jincheng {
    char name[20];      // ��������
    int* max;           // ������̶�Ӧ��Դ�����������
    int* allocated;     // �����ѷ������Դ��
    bool finished;      // ��ǽ����Ƿ����
};
// ��ʼ����Դ�����ĺ���
void initZiyuan(struct ziyuan* ziYuan) {
    printf("��������Դ������");
    int size;
    scanf("%d", &size);
    ziYuan->num = (int*)malloc(size * sizeof(int));
    if (ziYuan->num == NULL) {
        printf("�ڴ����ʧ�ܣ�");
        exit(1);
    }
    ziYuan->size = size;
    for (int i = 0; i < size; i++) {
        printf("��������Դ%d�Ĵ�С��", i);
        scanf("%d", &(ziYuan->num[i]));
    }
}

// ��ʼ�����̵ĺ���
int initjincheng(struct jincheng** JINCHENG, int num) {
    printf("��������̵ĸ�����\n");
    int size = 0;
    scanf("%d", &size);
    *JINCHENG = (struct jincheng*)malloc(size * sizeof(struct jincheng));
    if (*JINCHENG == NULL) {
        printf("�ڴ����ʧ�ܣ�");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        (*JINCHENG)[i].max = (int*)malloc(sizeof(int) * num);
        (*JINCHENG)[i].allocated = (int*)malloc(sizeof(int) * num);
        if ((*JINCHENG)[i].max == NULL || (*JINCHENG)[i].allocated == NULL) {
            printf("�ڴ����ʧ�ܣ�");
            exit(1);
        }
    }
    for (int i = 0; i < size; i++) {
        printf("���������%d�����֣�", i);
        scanf("%19s", (*JINCHENG)[i].name);
        for (int j = 0; j < num; j++) {
            printf("���������%s��%d��Դ�������������", (*JINCHENG)[i].name, j);
            scanf("%d", &(*JINCHENG)[i].max[j]);
        }
        // �ֶ�����ռ�õ���Դ��
        printf("���������%s��ǰ�Ѿ�ռ�õ���Դ����", (*JINCHENG)[i].name);
        for (int j = 0; j < num; j++) {
            printf("��Դ%d��ռ������", j);
            scanf("%d", &(*JINCHENG)[i].allocated[j]);
        }
        (*JINCHENG)[i].finished = false;
    }
    return size;
}
//���ĺ��������м��㷨ʵ��

   // ���ĺ��������м��㷨ʵ��
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

    int* execution_order = (int*)malloc(num_processes * sizeof(int)); // ��̬���� execution_order ����

    printf("������Ҫִ�еĽ���˳��0 �� %d����ÿ������֮���ÿո�ָ���\n", num_processes - 1);
    for (int i = 0; i < num_processes; ++i) {
        scanf_s("%d", &execution_order[i]);
        if (execution_order[i] < 0 || execution_order[i] >= num_processes) {
            printf("��Ч�Ľ������������������롣\n");
            i--;
        }
    }

    bool deadlock_detected = false;
    int deadlock_count = 0;
    int max_deadlock_attempts = 5; // ���ó��Խ��������������

    while (deadlock_count < max_deadlock_attempts) {
        for (int i = 0; i < num_processes; ++i) {
            int process_index = execution_order[i];
            printf("���н���%s...\n", JINCHENG[process_index].name);

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
                printf("���̷������Դ��\n");
                for (int i = 0; i < num_processes; ++i)
                {
                    printf("����%s��", JINCHENG[i].name);
                    for (int j = 0; j < num_resources; ++j) {
                        printf("%d ", allocation[i][j]);
                    }
                    printf("\n");
                }

                printf("����%s���䲢�ͷ���Դ��\n", JINCHENG[process_index].name);
                printf("\n");

                for (int j = 0; j < num_resources; ++j) {
                    available[j] += JINCHENG[process_index].allocated[j] + JINCHENG[process_index].max[j];
                    allocation[process_index][j] = 0;
                }
                printf("�ͷź����Դ��\n");
                for (int i = 0; i < num_processes; i++)
                {
                    printf("%d ", available[i]);
                }
                finished[process_index] = true;
            }
            else {
                printf("�޷�Ϊ����%s������Դ������%s���ڵȴ�״̬������������\n", JINCHENG[process_index].name, JINCHENG[process_index].name);
                printf("��ǰϵͳ״̬��\n");
                printf("������Դ��");
                for (int j = 0; j < num_resources; ++j) {
                    printf("%d ", available[j]);
                }
                printf("\n");

                printf("���̷������Դ��\n");
                for (int i = 0; i < num_processes; ++i) {
                    printf("����%s��", JINCHENG[i].name);
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
            printf("δ����������\n");
            break;
        }
        else {
            printf("������������������ѡ�����˳��...\n");
            // ����ѡ�����˳��
            for (int i = 0; i < num_processes; ++i) {
                execution_order[i] = (execution_order[i] + 1) % num_processes;
            }
            deadlock_count++;
            deadlock_detected = false;
        }
    }

    if (deadlock_count == max_deadlock_attempts) {
        printf("�ﵽ�������������Դ����������޷����������\n");
    }

    // �ͷŶ�̬����������ڴ�
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
