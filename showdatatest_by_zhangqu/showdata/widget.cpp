#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(0.0001);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateUI()));
    timer->start();
}

void Widget::updateUI()
{
    extern double tem1;
    extern double tem2;
    extern double tem3;
    extern double tem4;
    extern double tem5;
    extern double tem6;
    extern double tem7;
    extern double tem8;
    extern double tem9;
    extern double tem10;
    extern double tem11;
    extern double tem12;

    ui->lineEdit->setText(QString::number(tem1, 10,4));
    ui->lineEdit_2->setText(QString::number(tem2, 10,4));
    ui->lineEdit_3->setText(QString::number(tem3, 10,4));
    ui->lineEdit_4->setText(QString::number(tem4, 10,4));
    ui->lineEdit_5->setText(QString::number(tem5, 10,4));
    ui->lineEdit_6->setText(QString::number(tem6, 10,4));
    ui->lineEdit_7->setText(QString::number(tem7, 10,4));
    ui->lineEdit_8->setText(QString::number(tem8, 10,4));
    ui->lineEdit_9->setText(QString::number(tem9, 10,4));
    ui->lineEdit_10->setText(QString::number(tem10, 10,4));
    ui->lineEdit_11->setText(QString::number(tem11, 10,4));
    ui->lineEdit_12->setText(QString::number(tem12, 10,4));

}
Widget::~Widget()
{
    delete ui;
}
