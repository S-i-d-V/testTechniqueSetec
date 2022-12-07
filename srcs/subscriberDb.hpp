#ifndef SUBSCRIBERDB_HPP
#define SUBSCRIBERDB_HPP

#include <sqlite3.h>
#include "csvParser.hpp"
#include <iostream>
#include <iomanip>

class SubscriberDb{
    private:
        sqlite3 *DB;

        //Open/Create DB
        sqlite3 *openDb(){
            sqlite3 *DB;
            int exit = sqlite3_open("databases/subscribers.db", &DB);

            if (exit) {
                std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
                return (NULL);
            }
            return (DB);
        }

        //CreateTable
        int createTable(){
            std::string sqlCreateTable = "CREATE TABLE SUBSCRIBER("
                                         "ID INT PRIMARY       KEY   NOT NULL, "
                                         "NAME                 TEXT  NOT NULL, "
                                         "FIRSTNAME            TEXT  NOT NULL); ";
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
                std::cout << std::left << std::setw(19) << azColName[i]; 
                std::cout << " = ";
                std::cout << std::right << std::setprecision(108) << argv[i];
                std::cout << std::endl;
            }
            std::cout << "========================================================================================================================" << std::endl;
            return 0;
        }

    public:
        //Constructors
        SubscriberDb(){
            this->DB = openDb();
            this->createTable();
            return;
        }

        SubscriberDb(std::string const &path){
            this->DB = openDb();
            this->createTable();
            int count = this->getNbLines();

            if (count == 0){
                std::vector<Subscriber> subscribers = importSubscribersCSV(path);

                for (std::size_t i = 0; i < subscribers.size(); i++){
                    if (this->insertElement(subscribers[i]) == -1)
                        std::cerr << "Error inserting element in SubscriberDb" << std::endl;
                }
            }
            return;
        }

        //Destructor
        ~SubscriberDb(){
            sqlite3_close(this->DB);
            return;
        }

        //Return the number of lines in the table
        int     getNbLines(){
            int count = 0;
            std::string query = "SELECT COUNT(*) from SUBSCRIBER;";

            sqlite3_exec(this->DB, query.c_str(), this->countCallback, &count, NULL);
            return (count);
        }

        //Print all lines in the table
        void    printLines(){
            std::string query = "SELECT * FROM SUBSCRIBER;";

            std::cout << "========================================================================================================================" << std::endl;
            std::cout << "Number of subscribers: " << this->getNbLines() << std::endl;
            std::cout << "========================================================================================================================" << std::endl;
            sqlite3_exec(this->DB, query.c_str(), this->printCallback, 0, NULL);
        }

        //Insert a book
        int     insertElement(Subscriber element){
            std::string sqlLine("INSERT INTO SUBSCRIBER VALUES(" +
                                std::to_string(element.id) + ", '" +
                                element.name + "', '" +
                                element.firstName +  "');");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK){
                return (-1);
            }
            return (0);
        }

        //Delete a book
        int     deleteElement(int id){
            std::string sqlLine("DELETE FROM SUBSCRIBER WHERE ID = " + std::to_string(id) + ";");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK)
                return (-1);
            return (0);
        }

};

#endif