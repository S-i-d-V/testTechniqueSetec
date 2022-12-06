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
            return;
        }

        //Constructor
        Library(std::string const& booksPath, std::string const &suscribersPath){
            this->books = BookDb(booksPath);
            this->suscribers = SuscriberDb(suscribersPath);
            return;
        }

        ~Library(){
            return;
        }

        //Books
        void    addBook(Book book){
            if (this->books.insertElement(book) == -1)
                std::cerr << "Couldn't insert this element" << std::endl;
        }

        void    deleteBook(int id){
            if (this->books.deleteElement(id) == -1)
                std::cerr << "Couldn't delete this element" << std::endl;
        }

        void    displayBooks(){
            this->books.printLines();
        }

        int     getNbBooks(){
            return (this->books.getNbLines());
        }

        //Suscribers
        void    addSuscriber(Suscriber suscriber){
            if (this->suscribers.insertElement(suscriber) == -1)
                std::cerr << "Couldn't insert this element" << std::endl;
        }

        void    deleteSuscriber(int id){
            if (this->suscribers.deleteElement(id) == -1)
                std::cerr << "Couldn't delete this element" << std::endl;
        }

        void    displaySuscribers(){
            this->suscribers.printLines();
        }

        int     getNbSuscribers(){
            return (this->suscribers.getNbLines());
        }

        //Book borrowing
        void    borrowBook(){
            //Check if book exist
            //Notify book as used
        }

        void    returnBook(){
            //Check if book exist
            //Check if book is borrowed by the user
            //Notify book is free to borrow
        }
};
#endif