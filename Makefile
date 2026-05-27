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
SRC = ./src/apply_redir.c \
	  ./src/checker.c \
	  ./src/error_msg.c \
	  ./src/expander.c \
	  ./src/expander_2.c \
	  ./src/lexer.c \
	  ./src/lexer_postprocess.c \
	  ./src/main.c \
	  ./src/parser.c \
	  ./src/builtins/builtins_utils.c \
	  ./src/builtins/cd.c \
	  ./src/builtins/echo.c \
	  ./src/builtins/env.c \
	  ./src/builtins/exit.c \
	  ./src/builtins/export.c \
	  ./src/builtins/pwd.c \
	  ./src/builtins/unset.c \
	  ./src/executor/exec_pipe.c \
	  ./src/executor/exec_pipe_2.c \
	  ./src/executor/executor.c \
	  ./src/executor/executor_2.c \
	  ./src/signals/signals.c \
	  ./src/signals/signal_exit.c \
	  ./src/types/cmd.c \
	  ./src/types/envar.c \
	  ./src/types/redir.c \
	  ./src/types/token.c \
	  ./src/utils/envar_utils.c \
	  ./src/utils/gc_execvp.c \
	  ./src/utils/gc_getcwd.c \
	  ./src/utils/gc_readline.c \
	  ./src/utils/str_utils.c \
	  ./src/utils/str_utils_2.c \
	  ./src/utils/utils.c \
	  ./src/heredoc/heredoc.c

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
	@$(RM) $(NAME)
	@$(RM) minishell_tester
	@echo "Removed $(NAME) and test"

test: $(NAME)
	@bash tests/test.sh

bonus: $(NAME)
	@echo "Created $(NAME) with bonus"

re: fclean all

.PHONY: all clean fclean re test bonus
