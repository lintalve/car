/*
 In this file we write all main functions to see calls
 of main functions in different situations
 in den vershiedene Situationen
 */
#include <iostream>
#include <string>
#include <OpenGL/gl.h>  // for OpenGL functions
#include <OpenGL/glu.h> // for OpenGL utility functions
#include <random>
#include <ctime>
#include "Person.hpp"
#include "Body.hpp"

class myException : public std::exception {
    std::string message;
public:
    myException(const std::string& mes) : message(mes) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Object {
    int someInt{};
    std::string someString{};
public:
    
};


typedef enum Color {
    RED = 0,
    GREEN,
    BLACK,
    WHITE,
    BLUE,
    COUNT  //special value for total count - 1;
} Color;

Color getRandomColor() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr))); // Seed the RNG
    std::uniform_int_distribution<int> dist(0, COUNT - 1); // Generate random index
    return static_cast<Color>(dist(rng)); // Cast to enum type
}






class Vehicle {
protected:
    class LicPlate {
        // !!! Derived classes can then inherit the state without needing to redefine it !!!
        
        //let it be public here and private further
        //so these (const char* string literals) are
        //stored in read-only area of the memory
        //deleting them is undefined behaviour
    public:
        Color color {};
        const char* number {nullptr};
        LicPlate() {
            std::cout << "LicPlate Default constructor" << std::endl;
        };
        LicPlate(const char* num) : number(num) {
            std::cout << "LicPlate Parametrized constructor" << std::endl;
            color = getRandomColor();
        }
        //Copy-constructor
        LicPlate(const LicPlate& lp) : color(lp.color), number(lp.number) {
            std::cout << "LicPlate Copy-constructor" << std::endl;
        }
        //Copy-operator=
        LicPlate& operator=(const LicPlate& lp) {
            std::cout << "LicPlate Copy-operator=" << std::endl;
            if(&lp == this) return *this;
            color = lp.color;
            number = lp.number;
            return *this;
        }
        //Move-constructor
                                        //here you call copy-constructors
        LicPlate(LicPlate&& lp) noexcept : color(lp.color), number(lp.number) {
            //leave the moved from object in an empty valid state
            //you have access to private members in a constructor of the same
            //type as its argument, so
            lp.color = {};
            lp.number = {nullptr};
        }
        //Move-operator=
        LicPlate& operator=(LicPlate&& lp) noexcept {
            color = lp.color;
            number = lp.number;
            //leave the moved from object in an empty valid state
            lp.color = {};
            lp.number = {nullptr};
            return *this;
        }
        virtual void set_number(const char* num) { number = num; }
        virtual const char* get_number() const { return number; }
        virtual Color getColor() const { return color; }
    }lp;
    //If MyClass does not have a default constructor, and the braces are empty (i.e., {}),
    //value-initialization occurs, which means that obj is initialized to its default value
    //(for example, zero for primitive types or calling the default constructor for class members).
    //LicPlate lp {};  //CALLS the defaault constructor right there!!
    float top_speed {};
    std::string maker {"Mercedes"};
    std::string place_of_origing {"Germany"};
public:
    Vehicle() : lp("DE93745"), top_speed(230.5f) {
        std::cout << "Vehicle Default constructor" << std::endl;
    }
    //Copy-constructor
    Vehicle(const Vehicle& vh) {
        std::cout << "Vehicle Copy-constructor" << std::endl;
        if(&vh == this) throw myException("self assignment");
        lp = vh.lp;
        top_speed = vh.top_speed;
    }
    //Copy-operator=
    Vehicle& operator=(const Vehicle& vh) {
        std::cout << "Vehicle Copy-operator=" << std::endl;
        if(&vh == this) return *this;
        lp = vh.lp;
        top_speed = vh.top_speed;
        return *this;
    }
    //Move-constructor
    Vehicle(Vehicle&& vh) : lp(vh.lp), top_speed(vh.top_speed) {
        std::cout << "Vehicle Move-constructor" << std::endl;
        //leave the moved from...
        //with an initeresting syntax
        vh.lp = {};
        vh.top_speed = {};
    }
    //Move-operator=
    Vehicle& operator=(Vehicle&& vh) {
        std::cout << "Vehicle Move-operator=" << std::endl;
        lp = vh.lp;  //Calls lps Move constructor due to its && nature
        top_speed = vh.top_speed;
        //leave the moved from...
        //with an initeresting syntax
        vh.lp = {};  //creates a temporary default-initialized object (1 constructor call)
                     //and than move or copy that temp obj to vh.lp or copy eliscit since c++17
        vh.top_speed = {};
        return *this;
    }
    virtual void set_lp_number(const char* num) = 0;
    virtual std::string getPaint() const = 0;
    const char* get_lp() const { return lp.number; }
    
};

//########################################//

class Car : public Vehicle {
    //COMPOSITION
    Body body;
    Person driver;
    
public:
    //Car calls member object body constructor in its init-list
    Car() : Vehicle(), body(), driver() { std::cout << "Car Default constructor" << std::endl; }
    void setNumber(const char* number) {
        set_lp(number);
    }
    Car(const Car& c) {  //remember self copy
        if(this == &c) throw myException("Self Copy contruction attempt");
    }
    void set_lp_number(const char* num) override {
        number = "DE0987";
    }
    std::string getPaint() const override {
        return "Car statin dark grey film";
    }
                        
};

class Mercedes_C : public Car {
    //Nothing to extend car wiwth so far
    //Polymorpysm, functions overriding
    Mercedes_C() : Car() {
        std::cout << "Mercedes_C Default constructor" << std::endl;
    }
    std::string getPaint() const override {
        return "fine quality Mecedes dark grey satin film";
    }
};

//Global functions:
Car modifyCar(Car c, const char* number) {
    c.setNumber(number);
    return c;
}
Car getCar(const char* number) {
    Car c;
    return c;
}
/*
Car&& returnCar(const char* number = "UA23745") {
    
    //return Car();  //WARNING:: returns rvalue but not a reference to it
    //return std::move(Car());   //UNDEFINED BEHAVIOUR, compiler destroys temp Car() object before returning
    Car c;
    return std::move(c);
}
*/
int main(int argc, const char* argv[]) {
    //Door rFd(new Window());  //default constructor
    //Door lFd(new Window());
    //Door rRd(new Window());
    //Door lRd(new Window());
    
    //Window* front = new Window; //also default constructor
    //Window* rear = new Window;
    
    //Body bd(rFd, lFd, rRd, lRd, Door());
    
    Car car1;
    //Body bd1;
    
    
    
    // !!!VERY IMPORTANT !!! - next lines are very important
    std::cout << "##############################" << std::endl;
    Door myDoor;
    myDoor = Door(); //Move operator= on Door
    std::cout << "===========Door dr1; dr1 = myDoor;=================" << std::endl;
    Door dr1;     //default constructor
    dr1 = myDoor; // copy operator=
    dr1 = std::move(myDoor);
    std::cout << "==============Door dr2 = Door();===============" << std::endl;
                //should've been moving but:
    Door dr2 = Door(); //Copy Elision in C++17 and Later, so no moving or copying, direct initialisation
    std::cout << "=============Door dr3 = dr1;================" << std::endl;
    Door dr3 = dr1;   //classic Copy-constructor syntax
    Door dr4(dr3);    //direct Copy constructor invocation
    std::cout << "##############################" << std::endl;
    /*
    ##############################
    Window Default constructor
    Door default Constructor
    Window Default constructor
    Door default Constructor
    Door Move-assignment operator
    ##############
    Window Copy-constructor
     ##############################
    */
    //Car car1;
    //Car car2 = modifyCar(car1, "UA24564");
    
    
    return 0;
}



