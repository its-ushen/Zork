#include "gameengine.h"
#include "HelperUtils.h"
#include "qdebug.h"
#include <QFile>
#define questionValue (50)

GameEngine::GameEngine() {
    // empty constructor
}
GameEngine::~GameEngine() {
    // empty destructor
}

void GameEngine::startGame(const QString& username) {
    gameState.isReady = 0;
    gameState.isRunning = 1;
    currentPlayer.setName(username);
    qDebug() << "Player Name: " << currentPlayer.getName();
    resetData();
    day = 0;

    initialise();
    loadQuestionsForCountries();
    currentCountry = travelManager.findCountry("Ireland");
}

void GameEngine::endGame() {
    gameState.isRunning = 0;
    gameState.isEnding = 1;

    qDebug() << "Player Name: " << currentPlayer.getName();
    float correctPercentage = currentPlayer.getScore() * 100.0 / currentPlayer.getQuestionCount();
    qDebug() << "Game Over!";
    qDebug() << "Percentage of Questions Correct: " << correctPercentage << "%";
    if (currentCountry->getName() == "Ireland" && getCurrentDay() != 0) {
        if (day > highscore) {
            highscore = day;
        }
        qDebug() << "Total Days Spent: " << day;

        leaderboardDays.addEntry(currentPlayer.getName(), day);
        leaderboardScore.addEntry(currentPlayer.getName(), correctPercentage);
    }
}

void GameEngine::resetData() {
    currentPlayer.resetStats();
    travelManager.resetTravelOptions();
}

void GameEngine::initialise() {
    CountryUtils::createCountries(travelManager);
    CountryUtils::createTravelOptions(travelManager);
    CountryUtils::createItems(travelManager);
}

void GameEngine::loadQuestionsForCountries() {
    auto countries = travelManager.getCountries();
    auto shuffledQuestions  = QuestionUtils::createQuestionPool();

    size_t questionIndex = 0;
    for (auto& country : countries) {
        qDebug() << "Assigning questions to country: " << country->getName();
        std::vector<std::shared_ptr<Question>> countryQuestions;

        // Assign next set of questions uniquely
        for (size_t i = 0; i < 3 && questionIndex < shuffledQuestions.size(); ++i, ++questionIndex) {
            countryQuestions.push_back(shuffledQuestions[questionIndex]);
        }

        // Add questions to country
        for (auto& question : countryQuestions) {
            country->addQuestion(question);
        }
    }
}

void GameEngine::answerQuestion(int questionId, const QString& answer) {
    const auto& questions = currentCountry->getQuestions();
    // Make sure the question ID is valid
    if (questionId < 0 || static_cast<std::size_t>(questionId) >= questions.size()) {
        qDebug() << "Invalid question ID";
        return;
    }

    currentPlayer.incrementQuestionCounter();
    auto& question = questions[questionId];
    if (question->checkAnswer(answer)) {
        awardCoins(questionValue);
        currentPlayer.incrementScore();
        qDebug() << "Answer Right: \n";
    }
}

void GameEngine::awardCoins(int baseCoins) {
    static int allowance = 3;
    int coinsToAward = baseCoins;

    if (currentPlayer.hasBonus("x2 Coin Multiplier") && allowance > 0) {
        coinsToAward *= 2;
        allowance--;

        // If allowance is depleted, remove the bonus
        if (allowance == 0) {
            currentPlayer.removeBonus("x2 Coin Multiplier");
        }
    }
    currentPlayer.earnCoins(coinsToAward);
    qDebug() << "Coins awarded: " << coinsToAward;
}

void GameEngine::purchaseItem(int itemIndex) {
    const auto& items = currentCountry->getItems();
    if (itemIndex < 0 || static_cast<size_t>(itemIndex) >= items.size()) {
        return; // Ensure itemIndex is within the range
    }

    //implementing arrarys
    auto& item = items[itemIndex];
    qDebug() << "Item Found, fine for now";
    if (currentPlayer.getCoins() >= item->getCost()) {
        currentPlayer.spendCoins(item->getCost());
        currentPlayer.addItem(item);
        // currentCountry->removeItem(itemIndex);
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

    if (option.has_value()) {
        // Apply cost-related bonuses
        if (currentPlayer.hasBonus("50% of next trip")) {
            int discountedCost = static_cast<int>(option->getCost() * 0.5);
            option->setCost(discountedCost);
            currentPlayer.removeBonus("50% of next trip");
        }

        if (currentPlayer.getCoins() >= option->getCost()) {
            currentPlayer.spendCoins(option->getCost());
            travelToCountry(option);
        } else {
            qDebug() << "Not enough coins";
            return;
        }
    } else {
        qDebug() << "No option found";
    }
}

void GameEngine::applyTravelTimeBonus() {
    auto& options = travelManager.getAvailableTravelOptions(*currentCountry);
    for (auto& option : options) {
        if (currentPlayer.hasBonus("Cut Travel Time in Half")) {
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

bool GameEngine::isOver() const {
    // Check if the current country is Ireland and days are >= 0
    if (getCurrentCountry() == "Ireland" && getCurrentDay() > 0) {
        return true;
    } else {
        return false;
    }
}


void GameEngine::debugPrintPlayerInventory() {
#ifdef DEBUG_MODE
    currentPlayer.printInventory();
#endif
}

const std::vector<Leaderboard<int>::Entry>& GameEngine::getDayLeaderboardEntries() const {
    return leaderboardDays.getEntries();
}

const std::vector<Leaderboard<float>::Entry>& GameEngine::getScoreLeaderboardEntries() const {
    return leaderboardScore.getEntries();
}








