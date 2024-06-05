#include <exception>
#include <cstring>

class MyException : public std::exception {
private:
    char* message;
public:
    MyException(const char* message) {
        this->message = new char[std::strlen(message) + 1];
        std::strcpy(this->message, message);
    }

    virtual ~MyException() noexcept {
        delete[] message;
    }

    virtual const char* what() const noexcept {
        return message;
    }
};
