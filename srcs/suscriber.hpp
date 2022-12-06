#ifndef SUSCRIBER_HPP
#define SUSCRIBER_HPP

#include <string>

class Suscriber{
    public:
        int id;

        std::string name;
        std::string firstName;

        Suscriber(
            int id,
            std::string const &name,
            std::string const &firstName
        ){
            this->id = id;
            this->name = name;
            this->firstName = firstName;
        }

        Suscriber(Suscriber const &src){
            *this = src;
            return;
        }

        Suscriber&   operator=(Suscriber const &rhs){
            this->id = rhs.id;
            this->name = rhs.name;
            this->firstName = rhs.firstName;
            return (*this);
        }
};

#endif