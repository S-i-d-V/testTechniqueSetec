#ifndef BOOKDB_HPP
#define BOOKDB_HPP

#include <sqlite3.h>
#include "csvParser.hpp"

class BookDb{
    private:
        sqlite3 *DB;

        //Open/Create DB
        sqlite3 *openDb(){
            sqlite3 *DB;
            int exit = sqlite3_open("databases/books.db", &DB);

            if (exit) {
                std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
                return (NULL);
            }
            return (DB);
        }

        //CreateTable
        int createTable(){
            std::string sqlCreateTable = "CREATE TABLE BOOK("
                                         "ID INT PRIMARY       KEY   NOT NULL, "
                                         "ISBN                 TEXT  NOT NULL, "
                                         "TITLE                TEXT  NOT NULL, "
                                         "DESC                 TEXT  NOT NULL, "
                                         "AUTHOR_NAME          TEXT  NOT NULL, "
                                         "AUTHOR_FIRSTNAME     TEXT  NOT NULL, "
                                         "AUTHOR_JOB           TEXT  NOT NULL, "
                                         "CO_AUTHOR_NAME       TEXT  NOT NULL, "
                                         "CO_AUTHOR_FIRSTNAME  TEXT  NOT NULL, "
                                         "CO_AUTHOR_JOB        TEXT  NOT NULL, "
                                         "EDITOR               TEXT  NOT NULL); ";
            int exit = sqlite3_exec(this->DB, sqlCreateTable.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK)
                return (-1);
            return (exit);
        }

        //Count the number of lines in the table
        static int countCallback(void *count, int argc, char **argv, char **azColName) {
            (void)argc;
            (void)argv;
            (void)azColName;
            int *c = (int *)count;
            *c = std::atoi(argv[0]);
            return 1;
        }

        //Print the content of the table
        static int printCallback(void* data, int argc, char** argv, char** azColName){
            (void)data;
            for (int i = 0; i < argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }

            printf("\n");
            return 0;
        }

    public:
    //Constructors
        BookDb(){
            this->DB = openDb();
            this->createTable();
            return;
        }

        BookDb(std::string const &path){
            this->DB = openDb();
            this->createTable();
            int count = this->getNbLines();

            if (count == 0){
                std::vector<Book> books = importBooksCSV(path);

                for (std::size_t i = 0; i < books.size(); i++){
                    if (this->insertElement(books[i]) == -1)
                        std::cerr << "Error inserting element in BookDb" << std::endl;
                }
            }
            //this->printLines();
            return;
        }

        //Destructor
        ~BookDb(){
            sqlite3_close(this->DB);
            return;
        }

        //Return the number of lines in the table
        int     getNbLines(){
            int count = 0;
            std::string query = "SELECT COUNT(*) from BOOK;";

            sqlite3_exec(this->DB, query.c_str(), this->countCallback, &count, NULL);
            return (count);
        }

        //Print all lines in the table
        void    printLines(){
            std::string query = "SELECT * FROM BOOK;";

            sqlite3_exec(this->DB, query.c_str(), this->printCallback, 0, NULL);
        }

        //Insert a book
        int     insertElement(Book element){
            std::string sqlLine("INSERT INTO BOOK VALUES(" +
                                std::to_string(element.id) + ", '" +
                                element.isbn + "', '" +
                                element.title + "', '" +
                                element.desc + "', '" +
                                element.authorName + "', '" +
                                element.authorFirstname + "', '" +
                                element.authorJob + "', '" +
                                element.coAuthorName + "', '" +
                                element.coAuthorFirstname + "', '" +
                                element.coAuthorJob + "', '" +
                                element.editor + "');");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK){
                return (-1);
            }
            return (0);
        }

        //Delete a book
        int     deleteElement(int id){
            std::string sqlLine("DELETE FROM BOOK WHERE ID = " + std::to_string(id) + ";");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK)
                return (-1);
            return (id);
        }

};

#endif