#ifndef CONDITION_H
#define CONDITION_H
#include "time_slice.h"
#include <QMainWindow>

namespace Ui {
class condition;
}

class condition : public QMainWindow
{
    Q_OBJECT

public:
    explicit condition(QWidget *parent = nullptr);
    ~condition();
    int row = 0;


private slots:
    void on_exit_clicked();

public slots:
    void get_output_data(Time_slice::PCB out_data);

private:

    Ui::condition *ui;
};

#endif // CONDITION_H
