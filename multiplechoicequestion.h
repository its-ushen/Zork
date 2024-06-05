#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H
#include "question.h"

class MultipleChoiceQuestion: public Question{
private:
    std::vector<QString> choices;
    int correctAnswerIndex;

public:
    MultipleChoiceQuestion(const QString& text, const std::vector<QString>& choices, int correctIndex)
        : Question(), choices(choices), correctAnswerIndex(correctIndex) {
        this->questionText = text;  // Assigning to the protected member inherited from Question
    }

    QString getQuestionsText() const override {
        return questionText;
    }

    bool checkAnswer(const QString& answer) const override {
        int answerIndex = answer.toInt();
        return answerIndex == correctAnswerIndex;
    }

    const std::vector<QString> getChoices() {
        return choices;
    }
};

#endif // MULTIPLECHOICEQUESTION_H
