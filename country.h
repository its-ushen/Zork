#ifndef COUNTRY_H
#define COUNTRY_H
#include <vector>
#include "TravelOption.h"
#include "question.h"
#include "item.h"
class Country {
public:
    Country(const QString& name, int distanceToIreland);
    void addNeighbour(Country* neighbour, int duration, int cost, const QString& travelMethod);
    std::vector<TravelOption>& getTravelOptions();
    void addQuestion(std::unique_ptr<Question> question);
    const std::vector<std::unique_ptr<Question>>& getQuestions() const;
    QString getName();
    void addItem (std::shared_ptr<Item> item);
    const std::vector<std::shared_ptr<Item>> getItems();
    void removeItem(int index);

private:
    QString name;
    int distanceToIreland;
    std::vector<Country*> neighbours;
    std::vector<TravelOption> travelOptions;
    std::vector<std::unique_ptr<Question>> questions;
    std::vector<std::shared_ptr<Item>> items;
};

#endif // COUNTRY_H
