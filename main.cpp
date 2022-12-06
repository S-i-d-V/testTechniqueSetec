#include <sqlite3.h>
#include <string>
#include "srcs/library.hpp"

int     main(){
    Library lib("CSV/livres.csv", "CSV/abonnes.csv");
    
    return (0);
}