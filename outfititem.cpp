#include "OutfitItem.h"

OutfitItem::OutfitItem(const QString& name, int cost, const QString& description)
    : Item(name, cost), description(description) {}

QString OutfitItem::getDescription() const {
    return description;
}

QString OutfitItem::getDetails() const {
    return Item::getDetails() + " Description: " + description;
}
