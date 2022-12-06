#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "bookDb.hpp"
#include "suscriberDb.hpp"

class Library {
    private:
        BookDb books;
        SuscriberDb suscribers;
    public:

        //Default constructor
        Library(){
            std::cout << "Library successfully built" << std::endl;
            return;
        }

        //Constructor
        Library(std::string const& booksPath, std::string const &suscribersPath){
            this->books = BookDb(booksPath);
            this->suscribers = SuscriberDb(suscribersPath);
            std::cout << "Library successfully built" << std::endl;
            return;
        }

        ~Library(){
            std::cout << "Library successfully closed" << std::endl;
            return;
        }
};
#endif