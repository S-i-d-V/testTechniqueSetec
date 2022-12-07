#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

class Book{

    public:
        int id;
        std::string isbn;

        std::string title;
        std::string desc;

        std::string authorName;
        std::string authorFirstname;
        std::string authorJob;

        std::string coAuthorName;
        std::string coAuthorFirstname;
        std::string coAuthorJob;

        std::string editor;

        std::string borrower;

        Book(
            int id,
            std::string const &isbn,

            std::string const &title,
            std::string const &desc,

            std::string const &authorName,
            std::string const &authorFirstname,
            std::string const &authorJob,

            std::string const &coAuthorName,
            std::string const &coAuthorFirstname,
            std::string const &coAuthorJob,

            std::string const &editor,
            std::string const &borrower
        ){
            this->id = id;
            this->isbn = isbn;

            this->title = title;
            this->desc = desc;

            this->authorName = authorName;
            this->authorFirstname = authorFirstname;
            this->authorJob = authorJob;

            this->coAuthorName = coAuthorName;
            this->coAuthorFirstname = coAuthorFirstname;
            this->coAuthorJob = coAuthorJob;

            this->editor = editor;

            this->borrower = borrower;
        }

        Book(Book const &src){
            *this = src;
            return;
        }

        Book&   operator=(Book const &rhs){
            this->id = rhs.id;
            this->isbn = rhs.isbn;

            this->title = rhs.title;
            this->desc = rhs.desc;

            this->authorName = rhs.authorName;
            this->authorFirstname = rhs.authorFirstname;
            this->authorJob = rhs.authorJob;

            this->coAuthorName = rhs.coAuthorName;
            this->coAuthorFirstname = rhs.coAuthorFirstname;
            this->coAuthorJob = rhs.coAuthorJob;

            this->editor = rhs.editor;
            this->borrower = rhs.borrower;
            return (*this);
        }
};

#endif
