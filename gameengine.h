#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <QString>
#include "GameState.h"
#include "player.h"
#include "question.h"
#include "country.h"
#include "travelmanager.h"
#include "leaderboard.h"
#include <QObject>

class GameEngine
{
public:
    int highscore = 0;

    GameState gameState;
    GameEngine();
    ~GameEngine();

    // game control
    void startGame(const QString& username);
    void endGame();

    // Gameplay mechanics
    void answerQuestion(int questionId, const QString& answer);
    void travelToCountry(std::optional<TravelOption> option);
    void purchaseItem(int itemId);
    void selectTravelOption(const QString& destination, int cost);
    void resetData();
    bool isOver() const;

    // Accessors
    int getCurrentDay() const;
    QString getCurrentCountry() const;
    Player getPlayer() const { return currentPlayer; } // sends a copy
    const TravelManager& getTravelManager() const { return travelManager; }
    const std::vector<Leaderboard<int>::Entry>& getDayLeaderboardEntries() const;
    const std::vector<Leaderboard<float>::Entry>& getScoreLeaderboardEntries() const;




private:
    Player currentPlayer;
    Country* currentCountry;
    std::vector<Country*> countries;
    TravelManager travelManager;
    Leaderboard<int> leaderboardDays;
    Leaderboard<float> leaderboardScore;

    int day;
    void initialise();
    void loadQuestionsForCountries();
    void applyTravelTimeBonus();
    void awardCoins(int);

    // adding friendship
    friend class Leaderboard<int>;
    friend class Leaderboard<float>;

    void debugPrintPlayerInventory();
};

#endif // GAMEENGINE_H
