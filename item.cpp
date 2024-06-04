#include "Item.h"

Item::Item(const QString& name, int cost)
    : name(name), cost(cost) {}

Item::~Item() {}

QString Item::getName() const { return name; }
int Item::getCost() const { return cost; }

QString Item::getDetails() const {
    return name + " Cost: " + QString::number(cost);
}
