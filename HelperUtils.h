#ifndef HELPERUTILS_H
#define HELPERUTILS_H

#include <memory>
#include "truefalsequestion.h"
#include "multiplechoicequestion.h"
#include "travelmanager.h"


namespace QuestionUtils {
    std::vector<std::unique_ptr<Question>> createQuestionPool();
    std::vector<std::unique_ptr<Question>> getRandomQuestions (std::vector<std::unique_ptr<Question>>& pool, size_t count);
}

namespace CountryUtils {
    void createCountries (TravelManager& manager);
    void createTravelOptions (TravelManager& manager);
    void createItems (TravelManager& manager);
}
#endif // HELPERUTILS_H
