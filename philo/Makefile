NAME = philo

CFLAGS = -Wall -Werror -Wextra -pthread

SRC = ./src/ft_atol.c ./src/handles.c ./src/init.c ./src/get_set.c ./src/time.c ./src/dinner.c ./src/printing.c ./src/utils.c ./src/main.c
OBJ_DIR = ./out
OBJ = $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SRC))
CC = cc

# Colors
YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

# Progress bar variables
TOTAL := $(words $(SRC))
COUNT = 0

all: $(NAME)

# Rule to create the object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to compile each .c file into an .o file while showing a progress bar
$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@$(eval COUNT=$(shell echo $$(($(COUNT) + 1)))) # Increase counter
	@echo -ne "$(YELLOW)[Compiling]$(RESET) $< ($(COUNT)/$(TOTAL))\r"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the final executable
$(NAME): $(OBJ)
	@echo -e "\n$(GREEN)[Linking]$(RESET) $@"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo -e "$(GREEN)✔ Build complete!$(RESET)"

# Clean up object files and executable
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)✗ Objects removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)✗ Executable removed$(RESET)"

re: fclean $(NAME)

.PHONY: all clean fclean re
