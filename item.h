#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item {
public:
    Item(const QString& name, int cost);
    virtual ~Item();

    QString getName() const;
    int getCost() const;

    virtual QString getDetails() const;

private:
    QString name;
    int cost;
};

#endif // ITEM_H
