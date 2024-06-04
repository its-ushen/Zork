#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question{
public:
    virtual ~Question() {} // this is a virtual destructor to ensure proper cleanup

    // pure v.f are defined to create the interface for M.C questions and T.F Questions
    virtual QString getQuestionsText() const = 0;
    virtual bool checkAnswer(const QString& answer) const = 0;

    // add more fucntionality here if needed
};

#endif // QUESTION_H
