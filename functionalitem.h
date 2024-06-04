#ifndef FUNCTIONALITEM_H
#define FUNCTIONALITEM_H

#include "Item.h"

class FunctionalItem : public virtual Item {
public:
    FunctionalItem(const QString& name, int cost, const QString& bonusType);
    QString getBonusType() const;
    QString getDetails() const override;

private:
    QString bonusType;
};

#endif // FUNCTIONALITEM_H
