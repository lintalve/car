#ifndef PERSON_HPP
#define PERSON_HPP

struct Person {
    std::string name {"Volodymyr"};
    std::string surname {"Hrudnytskyi"};
    int age {40};  //error: 'auto' not allowed in non-static class member
    double height {183.5}; //error: 'auto' not allowed in non-static class member
    bool married {};
};

#endif //Person.hpp
