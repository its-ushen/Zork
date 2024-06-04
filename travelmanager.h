#ifndef TRAVELMANAGER_H
#define TRAVELMANAGER_H

#include <QString>
#include "country.h"

class TravelManager {
public:
    void addCountry(const QString& name, int distanceToIreland);
    Country* findCountry(const QString& name) const;
    void addTravelOption(const QString& originName, const QString& destName, int duration, int cost, const QString& method);
    std::optional<TravelOption> getTravelOption(Country* originName, const QString& destName, int cost) const;
    std::vector<Country*> getCountries() const;
    std::vector<TravelOption>& getAvailableTravelOptions(Country& country);


private:
    std::vector<std::unique_ptr<Country>> countries;
};

#endif // TRAVELMANAGER_H
