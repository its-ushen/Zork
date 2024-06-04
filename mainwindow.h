#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
//#include "GameEngine.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startGameButton_clicked();
    void submitAnswer();

private:
    Ui::MainWindow *ui; // pointer to the game enginer class
    // GameEngine *gameEngine // pointer to the Game Engine class

    QPushButton *startGameButton;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
