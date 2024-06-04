#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <item.h>
#include <functionalitem.h>

class Player
{
public:
    // inserting global variable
    Player();

    void setName(const QString &name);
    // getters
    QString getName () const;
    int getCoins() const;

    void earnCoins(int amount);
    void spendCoins(int amount);
    bool hasBonus(const QString& bonusType) const;
    void resetStats();
    void addItem(const std::shared_ptr<Item> item);
    void removeBonus(const QString& bonusType);
    std::vector<std::shared_ptr<Item>> inventory;
    void incrementScore();
    int getScore() const;
    void incrementQuestionCounter();
    int getQuestionCount() const;

private:
    QString name;

    //defining a union
    union {
        int coins;
        float coinsFloat;
    };
    int score;
    int questionsAnswered;

    // to decide
    void setCoins(int coins);

    // adding friendship
    friend class GameEngine;

    void printInventory();
};

#endif // PLAYER_H
