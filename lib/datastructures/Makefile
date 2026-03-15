NAME = datastructures.a
TEST = test

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f

INCLUDE = -I ../../include

SRC = darray_basic.c \
	  darray_io.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in datastructures"

fclean: clean
	@$(RM) $(NAME) $(TEST)
	@echo "Removed $(NAME) and $(TEST)"

test: $(NAME)
	@$(MAKE) -C ../libft
	@$(MAKE) -C ../gc_libft
	@$(CC) $(CFLAGS) $(INCLUDE) test.c $(NAME) ../libft/libft.a ../gc_libft/gc_libft.a -o $(TEST)
	@./$(TEST)

re: fclean all

.PHONY: all clean fclean re test
