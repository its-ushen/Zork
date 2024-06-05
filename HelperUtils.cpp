#include "HelperUtils.h"
#include "outfititem.h"
#include "functionalitem.h"
#include "specialitem.h"
#include <numeric>
#include <random>

namespace QuestionUtils {
    std::vector<std::shared_ptr<Question>> createQuestionPool() {
        std::vector<std::shared_ptr<Question>> pool;

        // Multiple Choice Questions
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("What does the delete keyword do in C++?", std::vector<QString>{"Deletes a variable from memory", "Frees dynamically allocated memory", "Removes a file from disk"}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which of the following is a correct identifier in C++?", std::vector<QString>{"2names", "_name", "new"}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which keyword is used to define a class in C++?", std::vector<QString>{"class", "struct", "interface"}, 0));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which header file is required to use std::string?", std::vector<QString>{"<string.h>", "<cstring>", "<string>"}, 2));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which of the following is not a loop structure in C++?", std::vector<QString>{"for", "while", "repeat-until"}, 2));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which header file is required to use the std::vector container?", std::vector<QString>{"<vector>", "<array>", "<list>"}, 0));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("What keyword is used to define a namespace?", std::vector<QString>{"package", "module", "namespace"}, 2));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which of the following is true about constructors in C++?", std::vector<QString>{"Constructors can be virtual.", "A class can have more than one constructor.", "Constructors must always be public."}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which of the following is a correct way to initialize an object?", std::vector<QString>{"ClassName obj();", "ClassName obj = ClassName();", "ClassName obj->ClassName();"}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("What does the this pointer represent?", std::vector<QString>{"A pointer to the base class.", "A pointer to the current object.", "A pointer to a static member."}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which operator can NOT be overloaded in C++?", std::vector<QString>{"++", "--", "::"}, 2));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which feature in C++ is used to manage memory automatically?", std::vector<QString>{"Destructor", "Inline functions", "Smart pointers"}, 2));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("What is the purpose of the dynamic_cast operator?", std::vector<QString>{"For handling exceptions.", "For type conversion between related classes.", "For increase performance."}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which STL container provides constant time insertion and deletion at any position?", std::vector<QString>{"std::deque", "std::list", "std::array"}, 1));
        pool.push_back(std::make_shared<MultipleChoiceQuestion>("Which of the following correctly declares an abstract class?", std::vector<QString>{"Class with no member functions.", "Class with at least one pure virtual function.", "Class that cannot be instantiated."}, 1));


        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, the default access modifier for members of a class is private.", true));
        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, distributed inheritance is a type of inheritance.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("The delete operator in C++ is used to remove files from the disk.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, it is possible to overload the && and || operators.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, a template function can operate with any data type.", true));
        pool.push_back(std::make_shared<TrueFalseQuestion>("Function overloading in C++ allows the same function name to have different parameters.", true));
        pool.push_back(std::make_shared<TrueFalseQuestion>("The std::make_unique function in C++ is used to ensure data uniqueness in vectors.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("Function templates in C++ are the same as virtual functions.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, member variables of a struct are private by default.", false));
        pool.push_back(std::make_shared<TrueFalseQuestion>("In C++, a destructor is used to release memory allocated to a variable.", false));

        return pool;
    }

    std::vector<std::shared_ptr<Question>> getRandomQuestions(std::vector<std::shared_ptr<Question>>& pool, size_t count) {
        std::vector<std::shared_ptr<Question>> selected;
        std::vector<size_t> indices(pool.size());
        std::iota(indices.begin(), indices.end(), 0);

        std::mt19937 engine(static_cast<unsigned int>(time(nullptr)));
        std::shuffle(indices.begin(), indices.end(), engine);

        for (size_t i = 0; i < count && i < indices.size(); ++i) {
            selected.push_back(std::move(pool[indices[i]]));
        }
        return selected;
    }
}

namespace CountryUtils {
    void createCountries (TravelManager& manager) {
        manager.addCountry("Ireland", 0);
        manager.addCountry("UK", 900);
        manager.addCountry("Germany", 800);
        manager.addCountry("UAE", 700);
        manager.addCountry("America", 500);
        manager.addCountry("Iceland", 200);
    }

    void createTravelOptions (TravelManager& manager) {
        manager.addTravelOption("Ireland", "UK", 1, 50, "Ferry");
        manager.addTravelOption("Ireland", "Germany", 3, 100, "Plane");
        manager.addTravelOption("UK", "Germany", 3, 50, "Train");
        manager.addTravelOption("UK", "UAE", 2, 100, "Plane");
        manager.addTravelOption("UK", "America", 4, 250, "Plane");
        manager.addTravelOption("Germany", "UAE", 5, 50, "Plane");
        manager.addTravelOption("Germany", "UAE", 2, 100, "Plane");
        manager.addTravelOption("UAE", "America", 3, 100, "Plane");
        manager.addTravelOption("UAE", "America", 7, 50, "Plane");
        manager.addTravelOption("America", "Iceland", 3, 50, "Ferry");
        manager.addTravelOption("America", "Ireland", 2, 200, "Plane");
        manager.addTravelOption("Iceland", "Ireland", 3, 50, "Plane");
    }

    void createItems (TravelManager& manager) {
        auto ireland = manager.findCountry("Ireland");
        auto america = manager.findCountry("America");
        auto uk = manager.findCountry("UK");
        auto germany = manager.findCountry("Germany");
        auto uae = manager.findCountry("UAE");
        auto iceland = manager.findCountry("Iceland");

        ireland -> addItem(std::make_shared<OutfitItem>("Green Hat", 20, "A traditional Irish hat perfect for parades."));
        america -> addItem(std::make_shared<SpecialItem>("Runners", 50, "A quality pair of runners will reduce travel times", "Cut Travel Time in Half"));
        iceland -> addItem(std::make_shared<OutfitItem>("Jacket", 20, "Jacket Made out of Bear Skin"));
        uae -> addItem(std::make_shared<FunctionalItem>("Bonus", 40, "x2 Coin Multiplier"));
        uk -> addItem(std::make_shared<FunctionalItem>("Bonus", 40, "50% of next trip"));
        germany -> addItem(std::make_shared<OutfitItem>("Lederhosen", 20, "Perfect attire for Oktoberfest."));
    }
}
