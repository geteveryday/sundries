#include "condition.h"
#include "ui_condition.h"

condition::condition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::condition)
{
    ui->setupUi(this);
}

condition::~condition()
{
    delete ui;
}

void condition::on_exit_clicked()
{
    this->close();
}
void condition::get_output_data(Time_slice::PCB out_data){

    ui->output->setItem(row, 0, new QTableWidgetItem(out_data.id));
//    ui->output->setItem(row, 1, new QTableWidgetItem(QString::number(out_data.arrivetime, 10)));
    ui->output->setItem(row, 2, new QTableWidgetItem(QString::number(out_data.runtime, 10)));
    ui->output->setItem(row, 3, new QTableWidgetItem(QString::number(out_data.resttime, 10)));
    row++;
//    this->close();
    ui->output->viewport()->update();

}
