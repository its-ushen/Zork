#ifndef OUTFITITEM_H
#define OUTFITITEM_H

#include "Item.h"

class OutfitItem : public virtual Item {
public:
    OutfitItem(const QString& name, int cost, const QString& description);
    QString getDescription() const;
    QString getDetails() const override;

private:
    QString description;
};

#endif // OUTFITITEM_H
