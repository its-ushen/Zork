#ifndef TRAVELOPTION_H
#define TRAVELOPTION_H

#include <QString>

class Country; // forward declaration to use country in traveloption

class TravelOption {
public:
    TravelOption(Country* origin, Country* destination, int duration, int cost, const QString& method);
    Country* getOrigin() const;
    Country* getDestination() const;
    QString getMethod() const;
    int getDuration() const;
    int getCost() const;
    void setCost(const int);
    void setDuration(const int);

private:
    Country* origin;
    Country* destination;
    int duration;
    int cost;
    QString method;
};

#endif // TRAVELOPTION_H
