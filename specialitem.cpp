#include "SpecialItem.h"

SpecialItem::SpecialItem(const QString& name, int cost, const QString& description, const QString& bonusType)
    : Item(name, cost),
    FunctionalItem(name, cost, bonusType),
    OutfitItem(name, cost, description) {}

QString SpecialItem::getDetails() const {
    QString details = Item::getDetails();

    details += ", Bonus Type: " + getBonusType();
    details += ", Description: " + getDescription();

    return "SpecialItem: " + details;
}
