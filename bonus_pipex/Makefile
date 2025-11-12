NAME = pipex
LIBFT = libft/libft.a
LIBFT_DIR = libft
CFLAGS = -Wall -Werror -Wextra -g

SRC = cmd_list_helpers.c exec.c exit.c main.c parsing.c setup_pipes.c
OBJ = $(SRC:.c=.o)

all : $(LIBFT) $(NAME) 

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all noflags clean fclean re