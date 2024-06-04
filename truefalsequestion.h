#ifndef TRUEFALSEQUESTION_H
#define TRUEFALSEQUESTION_H
#include "question.h"

class TrueFalseQuestion : public Question {
private:
    QString questionText;
    bool correctAnswer;

public:
    TrueFalseQuestion(const QString& text, bool correctAnswer)
        : questionText(text), correctAnswer(correctAnswer) {}

    QString getQuestionsText() const override {
        return questionText;
    }

    bool checkAnswer (const QString& answer) const override {
        // assuming answer is either "true" or "false"
        bool answerbool = (answer.toLower() == "true");
        return answerbool == correctAnswer;
    }
};

#endif // TRUEFALSEQUESTION_H
