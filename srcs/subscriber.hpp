#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include <string>

class Subscriber{

    public:
        int id;

        std::string name;
        std::string firstName;

        Subscriber(
            int id,
            std::string const &name,
            std::string const &firstName
        ){
            this->id = id;
            this->name = name;
            this->firstName = firstName;
        }

        Subscriber(Subscriber const &src){
            *this = src;
            return;
        }

        Subscriber&   operator=(Subscriber const &rhs){
            this->id = rhs.id;
            this->name = rhs.name;
            this->firstName = rhs.firstName;
            return (*this);
        }
};

#endif
