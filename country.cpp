#include "country.h"
#include <QDebug>

Country::Country(const QString& name, int distanceToIreland)
    : name(name), distanceToIreland(distanceToIreland) {}

void Country::addNeighbour(Country* neighbour, int duration, int cost, const QString& travelMethod) {
    TravelOption option(this, neighbour, duration, cost, travelMethod);
    travelOptions.push_back(option);
}

std::vector<TravelOption>& Country::getTravelOptions() {
    return travelOptions;
}

void Country::addQuestion(std::shared_ptr<Question> question) {
    if (question) {
        qDebug() << "Adding question: " << question->getQuestionsText();
        questions.push_back(std::move(question));
    } else {
        qDebug() << "Attempted to add a null question";
    }
}

QString Country::getName() {
    return name;
}

void Country::addItem(std::shared_ptr<Item> item) {
    items.push_back(std::move(item));
}

const std::vector<std::shared_ptr<Question>>& Country::getQuestions() const{
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

void Country::resetTravelOptions() {
    travelOptions.clear();  // This clears the vector of travel options
}
