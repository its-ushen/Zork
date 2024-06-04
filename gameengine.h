#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <QString>
#include "player.h"
#include "question.h"
#include "country.h"
#include "travelmanager.h"
#include "leaderboard.h"

class GameEngine
{
public:
    int highscore = 0;
    GameEngine();
    ~GameEngine();

    // game control
    void startGame(const QString& username);
    void endGame();

    // Gameplay mechanics
    void answerQuestion(int questionId, QString answer);
    void travelToCountry(std::optional<TravelOption> option);
    void purchaseItem(int itemId);
    void selectTravelOption(const QString& destination, int cost);
    void saveLeaderboardData() const;
    void resetData();

    // Accessors
    int getCurrentDay() const;
    QString getCurrentCountry() const;


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
    void updateLeaderboards();
    void applyTravelTimeBonus();
    void awardCoins(int);

    // adding friendship
    friend class Player;

};

#endif // GAMEENGINE_H
