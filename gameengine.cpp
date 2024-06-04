#include "gameengine.h"
#include "HelperUtils.h"
#include "qdebug.h"
#include <QFile>
#define questionValue (50)


void GameEngine::startGame(const QString& username) {
    currentPlayer.setName(username);
    currentPlayer.resetStats();

    initialise();
    loadQuestionsForCountries();
    currentCountry = travelManager.findCountry("Ireland");
}

void GameEngine::endGame() {
    float correctPercentage = currentPlayer.getScore() * 100.0 / currentPlayer.getQuestionCount();
    qDebug() << "Game Over!";
    qDebug() << "Percentage of Questions Correct: " << correctPercentage << "%";
    if (currentCountry->getName() == "Ireland" && getCurrentDay() != 0) {
        if (day > highscore) {
            highscore = day;
        }
        qDebug() << "Total Days Spent: " << day;
        updateLeaderboards();
    }

    qDebug() << "Updated Leaderboards:";
    qDebug() << "Days Leaderboard:";
    leaderboardDays.display();
    qDebug() << "Score Leaderboard:";
    leaderboardScore.display();

    saveLeaderboardData();
    resetData();
}

void GameEngine::resetData() {
    currentPlayer.resetStats();
}

void GameEngine::saveLeaderboardData() const {
    QString filename = "leaderboardData.txt";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filename;
        return;
    }

    QTextStream out(&file);
    // Assuming leaderboardDays and leaderboardScore are your leaderboard objects
    out << "Days Leaderboard:\n";
    for (const auto& entry : leaderboardDays.getEntries()) {
        out << entry.playerName << ", " << entry.score << "\n";
    }
    out << "Score Leaderboard:\n";
    for (const auto& entry : leaderboardScore.getEntries()) {
        out << entry.playerName << ", " << entry.score << "\n";
    }

    file.close();
    qDebug() << "Leaderboard data saved successfully to" << filename;
}


void GameEngine::initialise() {
    CountryUtils::createCountries(travelManager);
    CountryUtils::createTravelOptions(travelManager);
    CountryUtils::createItems(travelManager);
}

void GameEngine::loadQuestionsForCountries() {
    auto countries = travelManager.getCountries();
    auto questionPool = QuestionUtils::createQuestionPool();

    for (auto& country : countries) {
        auto questions = QuestionUtils::getRandomQuestions(questionPool, 3);
        for (auto& question : questions) {
            country->addQuestion(std::move(question));
        }
    }
}

void GameEngine::answerQuestion(int questionId, QString answer) {
    const auto& questions = currentCountry->getQuestions();
    auto& question = questions[questionId];

    if (question->checkAnswer(answer)) {
        awardCoins(questionValue);
    }
}

void GameEngine::awardCoins(int baseCoins) {
    static int allowance = 3;
    int coinsToAward = baseCoins;
    if (allowance > 0)
    if (currentPlayer.hasBonus("x2 coin multiplier")) {
        if (allowance > 0) {
            coinsToAward *= 2;
            allowance --;
        }
        else {
            currentPlayer.removeBonus("x2 coin multiplier");
        }
    }
    currentPlayer.earnCoins(coinsToAward);
}

void GameEngine::purchaseItem(int itemIndex) {
    const auto& items = currentCountry->getItems();
    if (itemIndex < 0 || static_cast<size_t>(itemIndex) >= items.size()) {
        return; // Ensure itemIndex is within the range
    }

    auto& item = items[itemIndex];
    if (currentPlayer.getCoins() >= item->getCost()) {
        currentPlayer.spendCoins(item->getCost());
        currentPlayer.addItem(item);
        currentCountry->removeItem(itemIndex); // Ensure to remove the item from the country after transfer
    }
}

void GameEngine::travelToCountry(std::optional<TravelOption> option) {
    if (option.has_value()) {
        // Apply travel time, which also increments the day by the duration of the travel
        day += option->getDuration();

        // Move to the new country
        currentCountry = option->getDestination();
        qDebug() << "Travelled to " << option->getDestination() << ". Day: " << day;

    } else {
        qDebug() << "Destination country not found or no valid travel option to " << option->getDestination();
    }
}
void GameEngine::selectTravelOption(const QString& destination, int cost) {
    applyTravelTimeBonus();
    auto option = travelManager.getTravelOption(currentCountry, destination, cost);

    // checking for option
    if (option.has_value()) {
        // apply cost related bonuses
        if (currentPlayer.hasBonus("50% of next trip")) {
            option->setCost(static_cast<int> (option->getCost() * 0.5));
            currentPlayer.removeBonus("50% of next trip");
        }

        if (currentPlayer.getCoins() >= option->getCost()) {
            currentPlayer.spendCoins(option->getCost());
            travelToCountry(option);
        } else {
            return;
        }
    }

    else {
        qDebug() << "No option found";
    }

}

void GameEngine::applyTravelTimeBonus() {
    auto& options = travelManager.getAvailableTravelOptions(*currentCountry);
    for (auto& option : options) {
        if (currentPlayer.hasBonus("50% faster travel")) {
            option.setDuration(static_cast<int>(option.getDuration() * 0.5));
        }
    }
}

int GameEngine::getCurrentDay() const {
    return day;
}

QString GameEngine::getCurrentCountry() const {
    if (currentCountry) {
        return currentCountry->getName();
    } else {
        return "No country selected";
    }
}



void GameEngine::updateLeaderboards() {
    // Update the days leaderboard
    leaderboardDays.addEntry(currentPlayer.getName(), getCurrentDay());

    // Update the score leaderboard
    leaderboardScore.addEntry(currentPlayer.getName(), currentPlayer.getScore() / currentPlayer.getQuestionCount());
}


void GameEngine::debugPrintPlayerInventory() {
#ifdef DEBUG_MODE
    currentPlayer.printInventory();
#endif
}












