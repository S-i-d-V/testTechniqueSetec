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

        static int callback(void *count, int argc, char **argv, char **azColName) {
            (void)argc;
            (void)argv;
            (void)azColName;
            int *c = (int *)count;
            *c = std::atoi(argv[0]);
            return 1;
        }

    public:
        SuscriberDb(){
            this->DB = openDb();
            this->createTable();
            return;
        }

        SuscriberDb(std::string const &path){
            this->DB = openDb();
            this->createTable();

            //Count lines
            std::string query = "SELECT COUNT(*) from SUSCRIBER;";
            int count = 0;
            sqlite3_exec(this->DB, query.c_str(), this->callback, &count, NULL);

            if (count == 0){
                std::vector<Suscriber> suscribers = importSuscribersCSV(path);

                std::cout << "Import " << suscribers.size() << " suscribers from CSV into DB" << std::endl;
                for (std::size_t i = 0; i < suscribers.size(); i++){
                    if (this->insertElement(suscribers[i]) == -1)
                        std::cerr << "Error inserting element in SuscriberDb" << std::endl;
                    else
                        std::cerr << "Succesfully inserted element in SuscriberDb" << std::endl;
                }
            }
            
            return;
        }

        ~SuscriberDb(){
            sqlite3_close(this->DB);
            return;
        }

        sqlite3 *getDB(){
            return (this->DB);
        }

        //Insert a book
        int     insertElement(Suscriber element){
            char* messaggeError;
            std::string sqlLine("INSERT INTO SUSCRIBER VALUES(" +
                                std::to_string(element.id) + ", '" +
                                element.name + "', '" +
                                element.firstName +  "');");
            int exit = sqlite3_exec(this->DB, sqlLine.c_str(), NULL, 0, &messaggeError);

            if (exit != SQLITE_OK){
                std::cout << "id : " << element.id << "| error = " << messaggeError << std::endl;
                sqlite3_free(messaggeError);
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