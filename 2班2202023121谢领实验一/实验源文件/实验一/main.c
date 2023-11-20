#include <stdio.h>
#include <stdlib.h>

//��ƽ��̽ṹ��
struct PCB 
{
    char name[10];//��ʮ���ַ���Ϊ�ַ��������������
    int super;//��һ��int���ʹ������ȼ�
    int needtime;//������Ҫ��ʱ��
    int finish;//���������ʱ��¼����ʱ��
    int entertime;//��¼����˳��
};

//��ƽ��̳�ʼ������
void init(int num, struct PCB** jingcheng);
//����������
void outputjingcheng(struct PCB** p);
//��ƽ������к�����
void go(int num, struct PCB** jingcheng, int* time);


int main() 
{
    int num, time = 0;//numΪ��������,time��¼����ʱ��
    printf("���������������");
    scanf_s("%d", &num);
    struct PCB* jingcheng=NULL;
    init(num,&jingcheng);//��ʼ������
    go(num, &jingcheng, &time);//���к���
    
    return 0;
}


//��ƽ��̳�ʼ������
void init(int num, struct PCB** jingcheng)
{
    *jingcheng = malloc(num * sizeof(struct PCB));
    if (*jingcheng == NULL)
    {
        printf("�ڴ�����ʧ��\n");
        exit(1);
    }
    for (int i = 0; i < num; i++)
    {
        printf("�������������\n");
        scanf_s("%s", (*jingcheng)[i].name, sizeof((*jingcheng)[i].name));
        printf("������������ȼ���\n");
        scanf_s("%d", &(*jingcheng)[i].super);
        printf("�����������Ҫ��ʱ�䣺\n");
        scanf_s("%d", &(*jingcheng)[i].needtime);
        (*jingcheng)[i].finish = 0;
        (*jingcheng)[i].entertime = i;
    }

}
//����������
void outputjingcheng(struct PCB** p)
{
    printf("��ǰִ�еĽ���\t����ʣ���ʱ��\n");
    printf("%-s           \t%-7d\n", (*p)->name, (*p)->needtime);
}
//��ƽ������к���
void go(int num, struct PCB** jingcheng, int* time)
{
    struct PCB* p = NULL;//����һ��������ָ��
    while (1)
    {
        int i;
        for (i = 0; i < num; i++)//ѭ���ҵ�һ������Ҫ����ʱ��Ľṹ��
        {
            if ((*jingcheng)[i].needtime != 0)
            {
                p = &(*jingcheng)[i];
                break;//����л�û����ɵĽ��̣��Ͱ��丳��pָ�룬Ȼ���˳�ѭ��
            }
        }
        if (p == NULL)
        {
            printf("�����Ѿ���ɣ�\n");//��Ϊ���н��̵�needtime��Ϊ0����p���ᱻ��ֵ����Ϊ��
            printf("�Ƿ��ӡ���̽���ʱ�������������0����ӡ����0��ӡ��");
            int booler = 0;
            scanf_s("%d", &booler);
            if (booler)
            {
                system("cls||clear");//�������Ļ��ʹ��ϵͳ���ã�cls||clear���д�����Լ���windows��linux��MacOS��
                printf("������\t����ʱ��\n");
                for (int i = 0; i < num; i++)
                {
                    printf("%s    \t%d\n", (*jingcheng)[i].name, (*jingcheng)[i].finish);
                }
            }
            exit(1);//��������
        }

        for (; i < num; i++)
        {
            if ((*jingcheng)[i].needtime != 0 && (*jingcheng)[i].super < p->super)
            {//�������һ�����̻�ûִ���겢�����ȼ�����
                p = &(*jingcheng)[i];//�Ͱ�ָ��ָ���������ڣ�pִ�еľ���Ŀǰִ�еĽ���һ��λ
            }
        }
        p->needtime -= 1;//ʱ��Ƭʹ����ʱ���һ
        (*time)++;
        if (p->needtime == 0)//���̽���
        {
            p->finish = *time;
            printf("����%s����ɣ�\n", p->name);
        }
        outputjingcheng(&p);//������̵��������
        p = NULL;//ָ��ʹ����Ҫ�鵽��ָ�룬��ֹҰָ��
    }

}