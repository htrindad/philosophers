NAME = philo

CFLAGS = -Wall -Werror -Wextra -pthread

SRC = ./src/ft_atoul.c ./src/philosophers.c ./src/main.c
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NOCOLOR = \033[0m

# Total number of files and bar length
TOTAL_FILES := $(words $(SRC_FILES))
BAR_SYMBOL := ▓
BAR_LENGTH := 50
PROGRESS := 0

$(NAME): $(OBJ)
	@echo "\n$(YELLOW)Compiling $(NAME)..."
	@cc $(CFLAGS) $(OBJ) -o $(NAME)
	@sleep 0.2 #smooth ye ye
	@echo -n "\r\033[K" #Erase the loading bar
	@echo "\n$(GREEN)$(NAME) created successfully.$(NOCOLOR)"

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
