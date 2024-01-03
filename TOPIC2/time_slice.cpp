#include "time_slice.h"
#include "qdebug.h"
Time_slice::Time_slice(QObject *parent) : QObject(parent)
{

}
void Time_slice::RR_MAIN(void){
    sort(process, process + n);

        int time = 0;

        // int count;

        queue<PCB> q;

        for (int i = 0; i < n; i++)

        {

            q.push(process[i]);
        }

        int times = stime;

        time = q.front().arrivetime;

        while (true)

        {

            if (times == 0) // 重置时间片

            {

                times = stime;
            }

            if (q.front().arrivetime > time)

            {

                q.push(q.front());

                q.pop();

                continue;
            }

            q.front().begintime = time;

            while (times != 0)

            {

                --times;

                ++time;

                --q.front().resttime;

                if (q.front().resttime == 0)
                    break;
            }

            q.front().finishtime = time;
            output_data.id = q.front().id;
            output_data.arrivetime = q.front().arrivetime;
            output_data.begintime = q.front().begintime;
            output_data.finishtime = q.front().finishtime;
            output_data.finishtime = q.front().finishtime;
            emit send_output_data(output_data);



            qDebug() << "进程号" << q.front().id << endl;

            qDebug() << "到达时间：" << q.front().arrivetime << endl;

            qDebug() << "开始运行时间: " << q.front().begintime << endl;

            qDebug() << "结束运行时间: " << q.front().finishtime << endl;

            if (q.front().resttime != 0)

            {

//                cout << "此进程运行了一个时间片，切换到下一进程！" << endl;

                q.push(q.front());

                q.pop();
            }

            else

            {

                q.front().zhouzhuantime = time - q.front().arrivetime;

                q.front().weightzhouzhuantime = q.front().zhouzhuantime / (double)q.front().runtime;

                weighttotaltime += q.front().weightzhouzhuantime;

//                cout << "此进程已完成！" << endl;

//                cout << "进程" << q.front().id << "的周转时间为：" << q.front().zhouzhuantime << endl;

//                cout << "进程" << q.front().id << "的带权周转时间为: " << q.front().weightzhouzhuantime << endl;

                q.pop();

                times = 0;
            }

//            cout << "****************************************" << endl;

//            cout << endl;

//            cout << endl;

            if (q.empty())

                break;
        }

//        cout << "**********************************" << endl;

//        cout << "平均周转时间：" << totaltime / (double)n << endl;

//        cout << "平均带权周转时间：" << weighttotaltime / (double)n << endl;

//        cout << "**********************************" << endl;
}
