NAME = minishell

CC		= cc
CFLAGS 	= -Wall -Werror -Wextra -g
SRC 	= src/main.c src/gui.c
OBJ 	= $(SRC:src/%.c=obj/%.o)
OBJ_DIR	= ./obj

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INLCUDES = -Iinclude -I$(LIBFT_DIR)

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INLCUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

obj/%.o: src/%.c

	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INLCUDES) -c $< -o $@

$(LIBFT):

	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re