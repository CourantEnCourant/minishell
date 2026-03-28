NAME = minishell

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -rf

INCLUDE = -I ./include
SRC = ./src/main.c \
	  ./src/lexer.c \
	  ./src/parser.c \
	  ./src/utils.c \
	  ./src/utils/gc_getcwd.c \
	  ./src/utils/gc_readline.c 

OBJ = $(SRC:.c=.o)

TEST_SRC = $(filter-out ./src/main.c, $(SRC))
TEST_OBJ = $(TEST_SRC:.c=.o)

LIB_ARCHIVES = ./lib/datastructures/datastructures.a \
			   ./lib/gc_libft/gc_libft.a \
			   ./lib/libft/libft.a

all: $(NAME)

$(LIB_ARCHIVES):
	@make -C $(dir $@)

$(NAME): $(LIB_ARCHIVES) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_ARCHIVES) -lreadline -o $(NAME)
	@echo "Created $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@for dir in $(dir $(LIB_ARCHIVES)); do make -C $$dir fclean; done
	@$(RM) $(OBJ)
	@echo "Removed *.o in $(NAME)"

fclean: clean
	@$(RM) $(NAME) test
	@echo "Removed $(NAME) and test"

test: $(LIB_ARCHIVES) $(TEST_OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE) tests/test.c $(TEST_OBJ) $(LIB_ARCHIVES) -lreadline -o test
	@echo "Compiled ./test"

re: fclean all

.PHONY: all clean fclean re test bonus
