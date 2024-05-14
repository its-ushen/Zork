#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,counter(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_counterButton_clicked()
{
    counter ++;
    qDebug() << "Counter value:" << counter;
    ui->distanceTravellledDisplay->setText(QString:: number(counter));
}
