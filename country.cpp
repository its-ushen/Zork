#include "country.h"

Country::Country(const QString& name, int distanceToIreland)
    : name(name), distanceToIreland(distanceToIreland) {}

void Country::addNeighbour(Country* neighbour, int duration, int cost, const QString& travelMethod) {
    TravelOption option(this, neighbour, duration, cost, travelMethod);
    travelOptions.push_back(option);
}

std::vector<TravelOption>& Country::getTravelOptions() {
    return travelOptions;
}

void Country::addQuestion(std::unique_ptr<Question> question) {
    questions.push_back(std::move(question));
}

QString Country::getName() {
    return name;
}

void Country::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

const std::vector<std::unique_ptr<Question>>& Country::getQuestions() const{
    return questions;
}

const std::vector<std::shared_ptr<Item>> Country::getItems() {
    return items;
}

void Country::removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(items.size())) {
        items.erase(items.begin() + index);
    }
}
