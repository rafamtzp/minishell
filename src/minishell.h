/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:39:22 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/21 13:49:14 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// command node struct
typedef struct s_cmdnode
{
	char				**cmd; // last ptr is NULL
	char				*path;
	int					infile;
	int					outfile;
	struct s_cmdnode	*next;
}						t_cmdnode;

// environment variable struct
typedef struct s_envar
{
	char				*varname;
	char				*value;
	// values instead of paths bc there could be values and paths mixed up (?)
	int					ascii_index;
	int					ascii_sum;
	struct s_envar		*next;
}						t_envar;

// overarching struct
typedef struct s_minishell
{
	t_envar				*envars;
	t_cmdnode			*cmds;
}						t_minishell;

/*GUI*/
void					print_cat(void);

/* environment vars list helpers */
int						env_lstsize(t_envar *env);
void					envlst_add_back(t_envar **envars, t_envar *new);
t_envar					*envlst_new(char *new_var);

/* builtins */
void					cd(char *path);
void					pwd(void);
void					env(t_envar **envars);
void					unset(t_envar **envars, char **cmd);
void					michi_exit(void);

/* builtins: export */
void					write_envars(t_envar *envar, bool order_alpha);

/* builtins: unset */
void					unset(t_envar **envars, char **cmd);
int						count_args(char **cmd); // seems useful but idk...

/* push swap helpers */
void					set_ascii_indices(t_envar **s);

/* error handling */
void					handle_err(int errnum, int err, char *msg);

//Extract envars
void					add_envars(t_envar **envars, char **cmd, bool is_not_parsing);


#endif