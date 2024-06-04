#ifndef SPECIALITEM_H
#define SPECIALITEM_H

#include "FunctionalItem.h"
#include "OutfitItem.h"

class SpecialItem : public FunctionalItem, public OutfitItem {
public:
    SpecialItem(const QString& name, int cost, const QString& description, const QString& bonusType);
    QString getDetails() const override;
};

#endif // SPECIALITEM_H
