#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H
#include "question.h"

class MultipleChoiceQuestion: public Question{
private:
    QString questionText;
    std::vector<QString> choices;
    int correctAnswerIndex; // within the choices

public:
    MultipleChoiceQuestion(const QString& text, const std::vector<QString>& choices, int correctIndex)
        : questionText(text), choices(choices), correctAnswerIndex(correctIndex) {}

    QString getQuestionsText() const override {
        return questionText;
    }

    bool checkAnswer(const QString& answer) const override {
        // assuming the answer is the index of the choice as a string.
        int answerIndex = answer.toInt();
        return answerIndex == correctAnswerIndex;
    }
};

#endif // MULTIPLECHOICEQUESTION_H
