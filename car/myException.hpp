#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP

class myException : public std::exception {
    std::string message;
public:
    myException(const std::string& mes) : message(mes) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif //MYEXCEPTION_HPP
