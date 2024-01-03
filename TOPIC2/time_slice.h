#ifndef TIME_SLICE_H
#define TIME_SLICE_H

#include <QObject>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <QString>
#include <queue>
using namespace std;
const int N = 10000;

class Time_slice : public QObject
{
    Q_OBJECT
public:
    explicit Time_slice(QObject *parent = nullptr);

    int n; // 进程数量

    int totaltime; // 总时间

    int weighttotaltime; // 总带权周转时间

    int stime; // 时间片

    struct PCB
    {

        QString id; // 进程名

        QString status; // 状态

        int priority; // 优先级

        int arrivetime; // 到达时间

        int begintime; // 开始时间

        int finishtime; // 完成时间

        int runtime; // 运行时间

        int resttime; // 剩余运行时间

        int zhouzhuantime; // 周转时间

        double weightzhouzhuantime; // 带权周转时间

        bool operator<(const PCB &p)

        {

            return arrivetime < p.arrivetime;
        }

    } process[N];

    PCB output_data;

    void RR_MAIN(void);
signals:
    void send_output_data(PCB outdata);
};

#endif // TIME_SLICE_H
