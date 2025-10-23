NAME = minishell

CC		= cc
CFLAGS 	= -Wall -Werror -Wextra -g
SRC 	= src/main.c src/gui.c src/builtins_export.c src/builtins_unset.c \
			src/builtins.c src/envlist_helpers.c src/error_handling.c src/push_swap_helpers.c \
			src/memory_cleanup.c
OBJ 	= $(SRC:src/%.c=obj/%.o)
OBJ_DBG	= $(SRC:src/%.c=dbg_obj/%.o)
OBJ_DIR	= ./obj
DIR_DBG	= ./dbg_obj

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INLCUDES = -Iinclude -I$(LIBFT_DIR)

all: $(NAME)

debug: $(OBJ_DBG) $(LIBFT)
	$(CC) -g $(INLCUDES) $(OBJ_DBG) $(LIBFT) -lreadline -o $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INLCUDES) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INLCUDES) -c $< -o $@

dbg_obj/%.o: src/%.c
	@mkdir -p $(DIR_DBG)
	$(CC) -g $(INLCUDES) -c $< -o $@

$(LIBFT):

	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DIR_DBG)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re debug