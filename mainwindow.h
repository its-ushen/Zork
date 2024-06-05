#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameengine.h"
#include "qradiobutton.h"
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QTableWidget>
#include "Leaderboard.h"

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
    void runGameLoop();
    void displayGreetings();
    void displayQuestions();
    void displayCoins();
    void displayItem();
    void addToInventory();
    void displayTravelOptions();
    void updateOptions(const std::shared_ptr<Question>& question, int questionNumber);
    QRadioButton* findRadioButton(int questionNumber, int optionNumber);
    void submitAnswers();
    QString checkAnswer(int questionNumber);
    void processTravelOption(int optionIndex);
    void resetAndEnableRadioButtons(int questionNumber);
    void updateLeaderboards();
    void updateLeaderboardUI(QTableWidget* tableWidget, const std::vector<Leaderboard<int>::Entry>& entries);
    void updateLeaderboardUI(QTableWidget* tableWidget, const std::vector<Leaderboard<float>::Entry>& entries);
    void handleGameEnded();


private slots:
    void on_startGameButton_clicked();

    void on_submitButton_clicked();

    void on_buyItem_clicked();

    void on_buyOption1_clicked();

    void on_buyOption2_clicked();

    void on_buyOption3_clicked();

private:
    Ui::MainWindow *ui; // pointer to the game enginer class
    GameEngine *gameEngine; // pointer to the Game Engine class

    QPushButton *startGameButton;
    QStackedWidget *stackedWidget;
    friend class Leaderboard<int>;
    friend class Leaderboard<float>;
};
#endif // MAINWINDOW_H
