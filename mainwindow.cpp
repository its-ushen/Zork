#include "mainwindow.h"
#include "gameengine.h"
#include "multiplechoicequestion.h"
#include "ui_mainwindow.h"
#include "player.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    gameEngine = new GameEngine();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameEngine;
}

void MainWindow::on_startGameButton_clicked()
{
    const QString username = ui->username->toPlainText();
    qDebug() << username;
    gameEngine->startGame(username);
    qDebug() << "Player Name: " << gameEngine->getPlayer().getName();

    ui->stackedWidget->setCurrentIndex(1);
    runGameLoop();
}

void MainWindow::runGameLoop() {
    static int counter = 0;  // Preserves counter across function calls
    qDebug() << "Iteration: " + QString::number(counter);
    displayCoins();
    qDebug() << "Coins Iteration: " + QString::number(counter);
    displayGreetings();
    qDebug() << "Greetings Iteration: " + QString::number(counter);
    displayQuestions();
    qDebug() << "Questions Iteration: " + QString::number(counter);
    displayItem();
    qDebug() << "Items Iteration: " + QString::number(counter);
    displayTravelOptions();
    qDebug() << "Travel Options Iteration: " + QString::number(counter);
    counter++;

    if (gameEngine->isOver()) {
        qDebug() << "Ending game";
        handleGameEnded();
    }
}

void MainWindow::handleGameEnded() {
    qDebug() << "Player Name: " << gameEngine->getPlayer().getName();
    ui->stackedWidget->setCurrentIndex(0);
    gameEngine->endGame();
    updateLeaderboards();

}
void MainWindow::displayTravelOptions() {
    auto travelOptions = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getTravelOptions();

    QTextBrowser* browsers[] = {ui->travelOption1, ui->travelOption2, ui->travelOption3};
    int index = 0;

    for (const auto& option : travelOptions) {
        QString displayText;
        QTextStream stream(&displayText);

        // Collect data from the TravelOption object
        stream << "Origin: " << (option.getOrigin() ? option.getOrigin()->getName() : "Unknown") << "\n"
               << "Destination: " << (option.getDestination() ? option.getDestination()->getName() : "Unknown") << "\n"
               << "Cost: " << option.getCost() << "\n"
               << "Duration: " << option.getDuration() << " days\n";

        // Setting text to the appropriate text browser
        if (index < 3) { // Ensure we do not go out of bounds
            browsers[index]->setText(displayText);
            index++;
        }
    }

    // Clear remaining text browsers if there are fewer than 3 options
    for (; index < 3; index++) {
        browsers[index]->clear();
    }
    qDebug() << "Player Name: " << gameEngine->getPlayer().getName();
}

void MainWindow::displayItem() {
    ui->buyItem->setEnabled(true);
    Item* item = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getItems()[0].get();
    QString description = item->getDetails();

    ui->itemDescription->setText(description);

}

void MainWindow::displayCoins() {
    QString coins = "Coins: " + QString::number(gameEngine->getPlayer().getCoins());
    ui->coinDisplay->setText(coins);
}

void MainWindow::displayGreetings() {
    const QString name = gameEngine->getPlayer().getName();
    QString currentCountry = gameEngine->getCurrentCountry();
    QString day = QString::number(gameEngine->getCurrentDay());

    QString playerInfo = "Welcome to Day: " + day +"\n" + "You are in " + currentCountry + "\n" + "Complete Challenges to get more coins";

    ui->infoTextBrowser->setText(playerInfo);
}

void MainWindow::displayQuestions() {
    qDebug() << "Looking for questions of country: " + (gameEngine->getCurrentCountry());
    const auto& questions = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getQuestions();
    qDebug() << "found questions";
    // Check the size of questions and populate the UI
    if (questions.size() >= 3) {
        ui->question1Text->setText(questions[0]->getQuestionsText());
        qDebug() << "Set second";
        ui->question2Text->setText(questions[1]->getQuestionsText());
        qDebug() << "Set third";
        ui->question3Text->setText(questions[2]->getQuestionsText());

        qDebug() << "Setting Questions";
        updateOptions(questions[0], 1);
        qDebug() << "Update 1";
        updateOptions(questions[1], 2);
        qDebug() << "Update 2";
        updateOptions(questions[2], 3);

        ui->submitButton->setEnabled(true);
    }
    else {
        qDebug() << "Question Size too big";
    }


}




void MainWindow::updateOptions(const std::shared_ptr<Question>& question, int questionNumber) {
    auto* mcQuestion = dynamic_cast<MultipleChoiceQuestion*>(question.get());
    if (mcQuestion) {
        // It's a multiple-choice question
        const auto& choices = mcQuestion->getChoices();
        if (choices.size() >= 3) {
            findRadioButton(questionNumber, 1)->setText(choices[0]);
            findRadioButton(questionNumber, 2)->setText(choices[1]);
            findRadioButton(questionNumber, 3)->setText(choices[2]);
        }
    } else {
        // It's a true/false question
        findRadioButton(questionNumber, 1)->setText("True");
        findRadioButton(questionNumber, 2)->setText(""); // Disable the second button
        findRadioButton(questionNumber, 2)->setEnabled(false);
        findRadioButton(questionNumber, 3)->setText("False");
    }
}

QRadioButton* MainWindow::findRadioButton(int questionNumber, int optionNumber) {
    QString radioButtonName = QString("question%1Option%2").arg(questionNumber).arg(optionNumber);
    return this->findChild<QRadioButton*>(radioButtonName);
}

void MainWindow::submitAnswers() {
    std::vector<QString> results;
    results.push_back(checkAnswer(1));
    results.push_back(checkAnswer(2));
    results.push_back(checkAnswer(3));

    for (int i = 0; i < results.size(); ++i) {
        gameEngine->answerQuestion(i, results[i]);
    }

    displayCoins();
}

QString MainWindow::checkAnswer(int questionNumber) {
    const auto& questions = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getQuestions();

    if (questionNumber - 1 < questions.size()) {
        // Access the question at index and attempt to cast it to MultipleChoiceQuestion
        auto* question = dynamic_cast<MultipleChoiceQuestion*>(questions[questionNumber - 1].get());

        if (question) {
            // The question is a MultipleChoiceQuestion, process it
            for (int i = 1; i <= 3; i++) {
                QRadioButton* button = findRadioButton(questionNumber, i);
                if (button->isChecked()) {
                    return QString::number(i - 1); // Correct option index
                }
            }
        } else {
            // It's not a MultipleChoiceQuestion, assume it's a TrueFalseQuestion
            QRadioButton* trueButton = findRadioButton(questionNumber, 1);
            QRadioButton* falseButton = findRadioButton(questionNumber, 3);
            if (trueButton && trueButton->isChecked()) {
                return "true";
            }
            if (falseButton && falseButton->isChecked()) {
                return "false";
            }
        }
    }
    return "";
}

void MainWindow::on_submitButton_clicked()
{
    submitAnswers();
    ui->submitButton->setEnabled(false);
}


void MainWindow::on_buyItem_clicked()
{
    gameEngine->purchaseItem(0);
    displayCoins();
    addToInventory();
    ui->buyItem->setEnabled(false);
}

void MainWindow::addToInventory() {
    ui->itemInventory->setText(gameEngine->getPlayer().getInventory());
}

void MainWindow::on_buyOption1_clicked() {
    auto options = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getTravelOptions();
    if (!options.empty()) {
        const TravelOption& option = options[0];

        // Get destination name and cost
        QString destination = option.getDestination() ? option.getDestination()->getName() : "";
        int cost = option.getCost();

        // Call the GameEngine function with these parameters
        gameEngine->selectTravelOption(destination, cost);
    } else {
        qDebug() << "No travel options available";
    }
    if (!gameEngine->isOver()) {
        qDebug() << gameEngine->getCurrentCountry();
        runGameLoop();
    }else {
        handleGameEnded();
    }
}




void MainWindow::on_buyOption2_clicked()
{
    auto options = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getTravelOptions();
    if (options.size() > 1) {
        const TravelOption& option = options[1];

        // Get destination name and cost
        QString destination = option.getDestination() ? option.getDestination()->getName() : "";
        int cost = option.getCost();

        // Call the GameEngine function with these parameters
        gameEngine->selectTravelOption(destination, cost);
    } else {
        qDebug() << "No second travel option available";
    }
    if (!gameEngine->isOver()) {
        qDebug() << gameEngine->getCurrentCountry();
        runGameLoop();
    } else {
        handleGameEnded();
    }
}


void MainWindow::on_buyOption3_clicked()
{
    auto options = gameEngine->getTravelManager().findCountry(gameEngine->getCurrentCountry())->getTravelOptions();
    if (options.size() > 2) {
        const TravelOption& option = options[2];

        // Get destination name and cost
        QString destination = option.getDestination() ? option.getDestination()->getName() : "";
        int cost = option.getCost();

        // Call the GameEngine function with these parameters
        gameEngine->selectTravelOption(destination, cost);
    } else {
        qDebug() << "No third travel option available";
    }
    if (!gameEngine->isOver()) {
        qDebug() << gameEngine->getCurrentCountry();

        runGameLoop();
    }else {
        handleGameEnded();
    }
}

void MainWindow::updateLeaderboards() {
    const auto& dayEntries = gameEngine->getDayLeaderboardEntries();
    const auto& scoreEntries = gameEngine->getScoreLeaderboardEntries();

    updateLeaderboardUI(ui->dayLeaderboard, dayEntries);
    updateLeaderboardUI(ui->scoreLeaderboard, scoreEntries);
}

void MainWindow::updateLeaderboardUI(QTableWidget* tableWidget, const std::vector<Leaderboard<int>::Entry>& entries) {
    tableWidget->setRowCount(0);
    for (const auto& entry : entries) {
        int rowIndex = tableWidget->rowCount();
        tableWidget->insertRow(rowIndex);
        tableWidget->setItem(rowIndex, 0, new QTableWidgetItem("Ushen"));
        tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(entry.score)));
    }
}

void MainWindow::updateLeaderboardUI(QTableWidget* tableWidget, const std::vector<Leaderboard<float>::Entry>& entries) {
    tableWidget->setRowCount(0);
    for (const auto& entry : entries) {
        int rowIndex = tableWidget->rowCount();
        tableWidget->insertRow(rowIndex);
        tableWidget->setItem(rowIndex, 0, new QTableWidgetItem("Ushen"));
        tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(QString::number(entry.score)));
    }
}
