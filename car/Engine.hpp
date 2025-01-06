#ifndef ENGINE_HPP
#define ENGINE_HPP

typedef enum EngineType {
    V8,
    ELECTRICAL,
    V4,
} EngineType;

struct Engine {
    std::string name {"Volodymyr"};
    std::string surname {"Hrudnytskyi"};
    int age {40};  //error: 'auto' not allowed in non-static class member
    double height {183.5}; //error: 'auto' not allowed in non-static class member
    bool married {};
};

#endif //Engine.hpp
