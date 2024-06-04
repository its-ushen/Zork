#include "player.h"
#include "qdebug.h"
#include <iostream>

Player::Player(): coins(0){}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &name)
{
    this->name = name;
}


int Player::getCoins() const
{
    return coins;
}

void Player::incrementScore() {
    score ++;
}

int Player::getScore() const {
    return score;
}

void Player::incrementQuestionCounter() {
    score ++;
}

int Player::getQuestionCount() const {
    return score;
}

void Player::earnCoins(int amount)
{
    if (amount > 0){
        this->coins += amount;
    }
}

void Player::spendCoins(int amount)
{
    if (amount < getCoins()) {
        this->coins -= amount;
    } else {
        std::cout<<"Not enough money";
    }
}

void Player::setCoins(int coins) {
    this->coins = coins;
    this->coinsFloat = static_cast<float>(coins); // Convert int to float (potential loss of precision)
}

bool Player::hasBonus(const QString& bonusType) const{
    for (const auto& item : inventory) {
        if (auto funcItem = dynamic_cast<FunctionalItem*>(item.get())) {
            if (funcItem->getBonusType() == bonusType) return true;
        }
    }
    return false;
}

void Player::addItem(std::shared_ptr<Item> item) {
    inventory.push_back(item); // Correctly move the item into the player's inventory
}
void Player::resetStats() {
    this->coins = 0;
    name = "";
    score = 0;
    questionsAnswered = 0;
}

void Player::removeBonus(const QString& bonusType) {
    // Directly remove the bonus without checking if the iterator has reached the end
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
                                   [&bonusType](const std::shared_ptr<Item>& item) {
                                       auto functionalItem = std::dynamic_pointer_cast<FunctionalItem>(item);
                                       return functionalItem && functionalItem->getBonusType() == bonusType;
                                   }),
                    inventory.end());
}

void Player::printInventory() {
    std::cout << "Inventory:" << std::endl;
    for (const auto& item : inventory) {
        qDebug() << "- " << item->getName();
    }
}


