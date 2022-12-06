#ifndef SUSCRIBERDB_HPP
#define SUSCRIBERDB_HPP

#include <sqlite3.h>
#include "csvParser.hpp"
#include <iostream>

class SuscriberDb{
    private:
        sqlite3 *DB;

        //Open/Create DB
        sqlite3 *openDb(){
            sqlite3 *DB;
            int exit = sqlite3_open("databases/suscribers.db", &DB);

            if (exit) {
                std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
                return (NULL);
            }
            return (DB);
        }

        //CreateTable
        int createTable(){
            std::string sqlCreateTable = "CREATE TABLE SUSCRIBER("
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
            int i;
            fprintf(stderr, "%s: ", (const char*)data);

            for (i = 0; i < argc; i++) {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }

            printf("\n");
            return 0;
        }

    public:
        //Constructors
        SuscriberDb(){
            this->DB = openDb();
            this->createTable();
            return;
        }

        SuscriberDb(std::string const &path){
            this->DB = openDb();
            this->createTable();
            int count = this->getNbLines();

            if (count == 0){
                std::vector<Suscriber> suscribers = importSuscribersCSV(path);

                for (std::size_t i = 0; i < suscribers.size(); i++){
                    if (this->insertElement(suscribers[i]) == -1)
                        std::cerr << "Error inserting element in SuscriberDb" << std::endl;
                }
            }
            this->printLines();
            return;
        }

        //Destructor
        ~SuscriberDb(){
            sqlite3_close(this->DB);
            return;
        }

        //Return the number of lines in the table
        int     getNbLines(){
            int count = 0;
            std::string query = "SELECT COUNT(*) from SUSCRIBER;";

            sqlite3_exec(this->DB, query.c_str(), this->countCallback, &count, NULL);
            return (count);
        }

        //Print all lines in the table
        void    printLines(){
            std::string query = "SELECT COUNT(*) from SUSCRIBER;";

            sqlite3_exec(this->DB, query.c_str(), this->printCallback, 0, NULL);
        }

        //Insert a book
        int     insertElement(Suscriber element){
            std::string sqlLine("INSERT INTO SUSCRIBER VALUES(" +
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
            std::string sqlLine("DELETE FROM SUSCRIBER WHERE ID = " + std::to_string(id) + ";");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, NULL);

            if (exit != SQLITE_OK)
                return (-1);
            return (id);
        }

};

#endif