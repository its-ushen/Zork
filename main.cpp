// #include "mainwindow.h"

// #include <QApplication>
// #include <iostream>
// #include "HelperUtils.h"

// int main(int argc, char *argv[])
// {
//     // QApplication a(argc, argv);
//     // MainWindow w;
//     // w.show();
//     // return a.exec();

//     auto pool = QuestionUtils::createQuestionPool();
//     std::vector<Question*> questions = QuestionUtils::getRandomQuestions(pool, 3);
//     for (Question* q : questions) {
//         qDebug() << q->getQuestionsText();

//     }
// }


#include "TravelManager.h"
#include "Country.h"
#include "TravelOption.h"
#include <QCoreApplication>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    TravelManager travelManager;

    // Setup countries
    travelManager.addCountry("Ireland", 0);
    travelManager.addCountry("UK", 100);
    travelManager.addCountry("France", 300);
    travelManager.addCountry("Spain", 500);

    // Add travel options
    travelManager.addTravelOption("Ireland", "UK", 2, 50, "Ferry");
    travelManager.addTravelOption("Ireland", "UK", 1, 65, "Plane");
    travelManager.addTravelOption("UK", "France", 1, 75, "Plane");
    travelManager.addTravelOption("France", "Spain", 3, 90, "Train");
    travelManager.addTravelOption("Spain", "Ireland", 5, 120, "Flight");

    // Simulate player choosing to travel from Ireland to UK
    qDebug() << "Initial Country: Ireland";
    Country* currentCountry = travelManager.findCountry("Spain");

    if (currentCountry) {
        qDebug() << "Travel options from" << currentCountry->getName() << ":";
        const auto& options = currentCountry->getTravelOptions();
        for (const auto& option : options) {
            qDebug() << "To" << option.getDestination()->getName()
                     << "via" << option.getMethod()
                     << "- Duration:" << option.getDuration() << "hrs, Cost:"
                     << option.getCost() << "euros";
        }

        // Simulate travel to the first available destination
        if (!options.empty()) {
            currentCountry = options[0].getDestination();
            qDebug() << "Travelling to" << currentCountry->getName() << "...";
        }
    } else {
        qDebug() << "Country not found.";
    }

    // Arrival at the new country
    if (currentCountry) {
        qDebug() << "Arrived in" << currentCountry->getName();
    }

    return app.exec();
}

