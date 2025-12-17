NAME = minishell

CC		= cc
CFLAGS 	= -Wall -Werror -Wextra

SRC 	= src/builtins/builtins.c		src/executor/executor.c\
		  src/builtins/export.c			src/executor/executor_helpers.c\
		  src/builtins/export_helpers.c	src/gui.c\
		  src/builtins/unset.c			src/parsing/is_builtin.c\
		  src/parsing/syntax_check.c	src/parsing/syntax_check_utils.c\
		  src/tokenizer/tokenize.c\
		  src/lists/cmd_list_helpers.c	src/main.c\
		  src/lists/env_list_cleanup.c	src/lists/env_list_helpers.c\
		  src/executor/pipe_handling.c	src/error_handling.c\
		  src/TESTING.c
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
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INLCUDES) -c $< -o $@

dbg_obj/%.o: src/%.c
	@mkdir -p $(dir $@)
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