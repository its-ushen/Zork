#ifndef TRUEFALSEQUESTION_H
#define TRUEFALSEQUESTION_H
#include "question.h"

class TrueFalseQuestion : public Question {
private:
    bool correctAnswer;

public:
    TrueFalseQuestion(const QString& text, bool correctAnswer)
        : Question(), correctAnswer(correctAnswer) {
        this->questionText = text;  // Assigning to the protected member inherited from Question
    }

    QString getQuestionsText() const override {
        return questionText;
    }

    bool checkAnswer (const QString& answer) const override {
        bool answerbool = (answer.toLower() == "true");
        return answerbool == correctAnswer;
    }
};

#endif // TRUEFALSEQUESTION_H
