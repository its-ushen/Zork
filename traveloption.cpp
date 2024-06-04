#include "travelOption.h"
#include "country.h"

TravelOption::TravelOption(Country* origin, Country* destination, int duration, int cost, const QString& method)
    : origin(origin), destination(destination), duration(duration), cost(cost), method(method) {}

Country* TravelOption::getDestination() const {
    return destination;
}

Country* TravelOption::getOrigin() const {
    return origin;
}

QString TravelOption::getMethod() const {
    return method;
}

int TravelOption::getDuration() const {
    return duration;
}

int TravelOption::getCost() const {
    return cost;
}

void TravelOption::setCost(const int cost) {
    this->cost = cost;
}

void TravelOption::setDuration(const int time) {
    duration = time;
}
