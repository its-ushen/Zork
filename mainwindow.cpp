#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startGameButton_clicked()
{
    const QString username = ui->username->toPlainText();
    Player player = Player();

    qDebug()<<player.getName();

    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::submitAnswer()
{
    //
}
