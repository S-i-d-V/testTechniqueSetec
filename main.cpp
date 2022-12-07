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

        std::cout << "Select a menu :" << std::endl;
        std::cout << "<books> or <subscribers>" << std::endl;
        std::cin >> prompt;
        std::cout << std::endl;

        //BOOKS MENU
        if (prompt == "books"){
            std::cout << "Select an action :" << std::endl;
            std::cout << "<add> or <delete> or <display>" << std::endl;
            std::cin >> prompt;
            std::cout << std::endl;

            //MANAGE LIST
            if (prompt == "add"){
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
                lib.addBook(element);
            }
            else if (prompt == "delete"){
                int id;

                std::cout << "Which book do you want to delete ? (id)" << std::endl;
                std::cin >> id;

                lib.deleteBook(id);
            }
            //DISPLAY LIST
            else if (prompt == "display"){
                std::cout << "What books do you want to display ?" << std::endl;
                std::cout << "<free> or <borrowed>" << std::endl;
                std::cin >> prompt;

                if (prompt == "free")
                    lib.displayFreeBooks();
                else if (prompt == "borrowed")
                    lib.displayBorrowedBooks();
            }
        }
        //SUBSCRIBERS MENU
        else if (prompt == "subscribers"){
            std::cout << "Select an action :" << std::endl;
            std::cout << "<add> or <delete> or <display>" << std::endl;
            std::cin >> prompt;
            std::cout << std::endl;

            //MANAGE LIST
            if (prompt == "add"){
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
                lib.addSubscriber(element);
            }
            else if (prompt == "delete"){
                int id;

                std::cout << "Which subscriber do you want to delete ? (id)" << std::endl;
                std::cin >> id;

                lib.deleteSubscriber(id);
            }
            //DISPLAY LIST
            else if (prompt == "display"){
                lib.displaySubscribers();
            }
            //BORROW/RETURN
            else if (prompt == "borrow"){
                std::cout << "borrow" << std::endl;
            }
            else if (prompt == "return"){
                std::cout << "return" << std::endl;
            }
        }
        //EXIT
        else if (prompt == "exit")
            return (0);
    }
    return (0);
}