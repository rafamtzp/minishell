NAME = minishell

CFLAGS 	= -Wall -Werror -Wextra -g
SRC 	= src/main.c
OBJ 	= $(SRC:src/%.c=obj/%.o)
OBJ_DIR = ./obj

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

obj/%.o: src/%.c

	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re