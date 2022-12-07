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
                throw CannotAddBook();
        }

        void    deleteBook(int id){
            if (this->books.deleteElement(id) == -1)
                throw CannotDeleteBook();
        }

        void    displayFreeBooks(){
            this->books.printLines("free");
        }

        void    displayBorrowedBooks(){
            this->books.printLines("borrowed");
        }

        int     getNbBooks(){
            return (this->books.getNbLines());
        }

        //Subscribers
        void    addSubscriber(Subscriber subscriber){
            if (this->subscribers.insertElement(subscriber) == -1)
                throw CannotAddSubscriber();
        }

        void    deleteSubscriber(int id){
            if (this->subscribers.deleteElement(id) == -1)
                throw CannotDeleteSubscriber();
        }

        void    displaySubscribers(){
            this->subscribers.printLines();
        }

        int     getNbSubscribers(){
            return (this->subscribers.getNbLines());
        }

        //Book borrowing
        void    borrowBook(int bookId, int subscriberId){
            if (this->books.borrowBook(bookId, subscriberId) == -1)
                throw CannotBorrowBook();
        }

        void    returnBook(int bookId){
            if (this->books.returnBook(bookId) == -1)
                throw CannotReturnBook();
        }

        //BOOK EXCEPTIONS
        class CannotAddBook : public std::exception{
			const char* what() const throw(){
                return ("Couldn't add this book, please check is the ID is unique");
            }
		};

        class CannotDeleteBook : public std::exception{
			const char* what() const throw(){
                return ("Couldn't delete this book, please check is the ID exist");
            }
		};

        class CannotReturnBook : public std::exception{
			const char* what() const throw(){
                return ("Couldn't return this book, please check if the book is not already free to borrow");
            }
		};

        //SUBSCRIBERS EXCEPTIONS
        class CannotAddSubscriber : public std::exception{
			const char* what() const throw(){
                return ("Couldn't add this subscriber, please check is the ID is unique");
            }
		};

        class CannotDeleteSubscriber : public std::exception{
			const char* what() const throw(){
                return ("Couldn't delete this subscriber, please check is the ID exist");
            }
		};

        class CannotBorrowBook : public std::exception{
			const char* what() const throw(){
                return ("Couldn't borrow this book, please check if the book is not already borrowed");
            }
		};

};

#endif
