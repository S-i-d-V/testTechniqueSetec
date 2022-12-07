#include <sqlite3.h>
#include <string>
#include "srcs/library.hpp"

int     main(){
    Library lib("CSV/livres.csv", "CSV/abonnes.csv");

    std::cout << "========================================================================================================================" << std::endl;
    std::cout << "                                                 Welcome to LibManager!                                                 " << std::endl;
    std::cout << "========================================================================================================================" << std::endl << std::endl;
    //INTERFACE LOOP
    while (1){
        std::string prompt;

        std::cout << "Type the number of the chosen menu:" << std::endl;
        std::cout << "1. Books menu" << std::endl;
        std::cout << "2. Subscribers menu" << std::endl;
        std::cin >> prompt;
        std::cout << std::endl;
        system("clear");

        //BOOKS MENU
        if (prompt == "1"){
            std::cout << "Type the number of the chosen action :" << std::endl;
            std::cout << "1. Add a book" << std::endl;
            std::cout << "2. Delete a book" << std::endl;
            std::cout << "3. Display free books" << std::endl;
            std::cout << "4. Display borrowed books " << std::endl;
            std::cout << "5. Return a book " << std::endl;
            std::cin >> prompt;
            std::cout << std::endl;
            system("clear");

            //ADD
            if (prompt == "1"){
                int id;
                std::string isbn;
                std::string title;
                std::string desc;
                std::string authorName;
                std::string authorFirstname;
                std::string authorJob;
                std::string coAuthourName;
                std::string coAuthourFirstname;
                std::string coAuthourJob;
                std::string editor;

                std::cout << "What's the id of the book ?" << std::endl;
                std::cin >> id;
                std::cout << "What's the ISBN of the book ?" << std::endl;
                std::cin >> isbn;

                std::cout << "What's the title of the book ?" << std::endl;
                std::cin >> title;
                std::cout << "A little description of the book ?" << std::endl;
                std::cin >> desc;

                std::cout << "What's the name of the author ?" << std::endl;
                std::cin >> authorName;
                std::cout << "What's the firstname of the author ?" << std::endl;
                std::cin >> authorFirstname;
                std::cout << "What's the job of the author ?" << std::endl;
                std::cin >> authorJob;

                std::cout << "What's the name of the cauthor ?" << std::endl;
                std::cin >> coAuthourName;
                std::cout << "What's the firstname of the co-author ?" << std::endl;
                std::cin >> coAuthourFirstname;
                std::cout << "What's the job of the author ?" << std::endl;
                std::cin >> coAuthourJob;

                std::cout << "What's the name of the editor ?" << std::endl;
                std::cin >> editor;

                Book element(
                    id,
                    isbn,
                    title,
                    desc,
                    authorName,
                    authorFirstname,
                    authorJob,
                    coAuthourName,
                    coAuthourFirstname,
                    coAuthourJob,
                    editor,
                    ":FREE:"
                );
                try {
                    lib.addBook(element);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                system("clear");
                std::cout << "Book succesfully added" << std::endl << std::endl;
            }
            //DELETE
            else if (prompt == "2"){
                int id;

                std::cout << "Which book do you want to delete ? (id)" << std::endl;
                std::cin >> id;

                try {
                    lib.deleteBook(id);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                system("clear");
                std::cout << "Book succesfully deleted" << std::endl << std::endl;
            }
            //DISPLAY TABLE
            else if (prompt == "3")
                lib.displayFreeBooks();
            else if (prompt == "4")
                lib.displayBorrowedBooks();
            //RETURN A BOOK
            else if (prompt == "5"){
                int bookId;

                std::cout << "What is the id of the book to return ?" << std::endl;
                std::cin >> bookId;

                try {
                    lib.returnBook(bookId);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                system("clear");
                std::cout << "Book successfully returned" << std::endl << std::endl;
            }
        }
        //SUBSCRIBERS MENU
        else if (prompt == "2"){
            std::cout << "1. Add a subscriber" << std::endl;
            std::cout << "2. Delete a subscriber" << std::endl;
            std::cout << "3. Display subscribers" << std::endl;
            std::cout << "4. Borrow a book" << std::endl;
            std::cin >> prompt;
            std::cout << std::endl;
            system("clear");

            //ADD
            if (prompt == "1"){
                int id;
                std::string name;
                std::string firstName;

                std::cout << "What's the id of the subscriber ?" << std::endl;
                std::cin >> id;
                std::cout << "What's the name of the subscriber ?" << std::endl;
                std::cin >> name;
                std::cout << "What's the firstname of the subscriber ?" << std::endl;
                std::cin >> firstName;

                Subscriber element(id, name, firstName);

                try {
                    lib.addSubscriber(element);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                system("clear");
                std::cout << "Subscriber successfully added" << std::endl << std::endl;
            }
            //DELETE
            else if (prompt == "2"){
                int id;

                std::cout << "Which subscriber do you want to delete ? (id)" << std::endl;
                std::cin >> id;

                try {
                    lib.deleteSubscriber(id);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                system("clear");
                std::cout << "Subscriber successfully deleted" << std::endl << std::endl;
            }
            //DISPLAY LIST
            else if (prompt == "3")
                lib.displaySubscribers();
            //BORROW A BOOK
            else if (prompt == "4"){
                int bookId;
                int subscriberId;

                std::cout << "Which book the subscriber want to borrow ? (book id)" << std::endl;
                std::cin >> bookId;
                std::cout << "Which subscriber want to borrow this book ? (subscriber id)" << std::endl;
                std::cin >> subscriberId;

                try {
                    lib.borrowBook(bookId, subscriberId);
                }
                catch (std::exception& e){
                    std::cerr << "[Error]: " << e.what() << std::endl << std::endl;
                }
                std::cout << "Book successfully borrowed" << std::endl << std::endl;
                system("clear");
            }
        }
        //EXIT
        else if (prompt == "exit")
            return (0);
    }
    return (0);
}