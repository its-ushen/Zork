#include "FunctionalItem.h"

FunctionalItem::FunctionalItem(const QString& name, int cost, const QString& bonusType)
    : Item(name, cost), bonusType(bonusType) {}

QString FunctionalItem::getBonusType() const {
    return bonusType;
}

QString FunctionalItem::getDetails() const {
    return Item::getDetails() + " Bonus Type: " + bonusType;
}
