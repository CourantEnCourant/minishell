NAME = minishell

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_DIR)/include
	LDFLAGS += -L$(READLINE_DIR)/lib
endif
AR = ar rcs
RM = rm -rf

INCLUDE = -I ./include
SRC = ./src/checker.c \
	  ./src/cmd.c \
	  ./src/exec_pipe.c \
	  ./src/executor.c \
	  ./src/lexer.c \
	  ./src/lexer_postprocess.c \
	  ./src/main.c \
	  ./src/parser.c \
	  ./src/redir.c \
	  ./src/token.c \
	  ./src/utils/gc_execvp.c \
	  ./src/utils/gc_getcwd.c \
	  ./src/utils/gc_readline.c \
	  ./src/utils/utils.c

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
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIB_ARCHIVES) -lreadline -o $(NAME)
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
	@$(CC) $(CFLAGS) $(LDFLAGS) -Wno-error=unused-function $(INCLUDE) $(TEST_OBJ) -x c tests/test.norminette -x none $(LIB_ARCHIVES) -lreadline -o test
	@echo "Compiled ./test"

re: fclean all

.PHONY: all clean fclean re test bonus
