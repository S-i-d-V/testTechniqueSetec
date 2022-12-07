#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "bookDb.hpp"
#include "subscriberDb.hpp"

class Library {
    private:
        BookDb books;
        SubscriberDb subscribers;
    public:

        //Default constructor
        Library(){
            return;
        }

        //Constructor
        Library(std::string const& booksPath, std::string const &subscribersPath): books(BookDb(booksPath)), subscribers(SubscriberDb(subscribersPath)){
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

        void    displayFreeBooks(){
            this->books.printLines("free");
        }

        void    displayBorrowedBooks(){
            this->books.printLines("borrowed");
        }

        int     getNbFreeBooks(){
            return (this->books.getNbLines("free"));
        }

        int     getNbBorrowedBooks(){
            return (this->books.getNbLines("borrowed"));
        }

        int     getNbBooks(){
            return (this->books.getNbLines("borrowed") + this->books.getNbLines("free"));
        }

        //Subscribers
        void    addSubscriber(Subscriber subscriber){
            if (this->subscribers.insertElement(subscriber) == -1)
                std::cerr << "Couldn't insert this element" << std::endl;
        }

        void    deleteSubscriber(int id){
            if (this->subscribers.deleteElement(id) == -1)
                std::cerr << "Couldn't delete this element" << std::endl;
        }

        void    displaySubscribers(){
            this->subscribers.printLines();
        }

        int     getNbSubscribers(){
            return (this->subscribers.getNbLines());
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
