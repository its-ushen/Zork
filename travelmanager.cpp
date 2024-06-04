#include "travelManager.h"
#include "country.h"
#include <optional>

void TravelManager::addCountry(const QString& name, int distanceToIreland) {
    auto country = std::make_unique<Country>(name, distanceToIreland);
    countries.push_back(std::move(country));
}

Country* TravelManager::findCountry(const QString& name) const {
    for (const auto& country : countries) {
        if (country->getName() == name) {
            return country.get();
        }
    }
    return nullptr; // Return nullptr if no country found
}

void TravelManager::addTravelOption(const QString& originName, const QString& destName, int duration, int cost, const QString& method) {
    Country* origin = findCountry(originName);
    Country* destination = findCountry(destName);
    if (origin && destination) {
        origin->addNeighbour(destination, duration, cost, method);
    }
}

std::vector<Country*> TravelManager::getCountries() const {
    std::vector<Country*> result;
    for (const auto& country : countries) {
        result.push_back(country.get());
    }
    return result;
}

std::optional<TravelOption> TravelManager::getTravelOption(Country* originName, const QString& destName, int cost) const {
    const std::vector<TravelOption>& options = originName->getTravelOptions();

    for (const TravelOption& t: options) {
        if (t.getDestination()->getName() == destName && t.getCost() == cost) {
            return t;
        }
    }
    return std::nullopt;
}

std::vector<TravelOption>& TravelManager::getAvailableTravelOptions(Country& country) {
    return country.getTravelOptions();
}
