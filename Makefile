.SILENT:

#COLOR
RED =`tput setaf 1`
GREEN =`tput setaf 2`
YELLOW =`tput setaf 3`
BLUE =`tput setaf 4`
CLEAR =`tput sgr0`

#FILES
EXEC = library
SRCS = srcs/book.hpp \
		srcs/bookDb.hpp \
		srcs/csvParser.hpp \
		srcs/library.hpp \
		srcs/suscriber.hpp \
		srcs/suscriberDb.hpp \
		srcs/utils.hpp
MAIN = main.cpp
DB = databases/books.db databases/suscribers.db

#ALIASES
G = g++
FLAGS = -g -fsanitize=address -Wall -Wextra -Werror

all: $(MAIN)
	echo "$(BLUE)Compiling $(YELLOW)$(EXEC)$(BLUE) from $(YELLOW)$^$(BLUE) ..$(CLEAR)"
	$(G) $(FLAGS) main.cpp -l sqlite3 -o library
	echo "$(YELLOW)- $(EXEC)$(GREEN) is ready to use.$(CLEAR)"

clean:
	rm -rf $(DB) $(EXEC)
	echo "$(BLUE)Deleting following files :$(CLEAR)"
	echo "$(YELLOW)- $(DB) $(RED) deleted.$(CLEAR)"

fclean: clean
	rm -rf $(EXEC)
	echo "$(YELLOW)- $(EXEC) $(RED) deleted.$(CLEAR)"


re: fclean all