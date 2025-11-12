/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:39:22 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/12 14:49:30 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

# include "../libft/libft.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// command node struct (CHANGED FROM t_cmdnode to t_cmd)
typedef struct s_cmd
{
	char			**cmd;
	char			*path;
	char			*delim;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;
// Note: I think is_append might not be necessary.

// environment variable struct
typedef struct s_envar
{
	char			*varname;
	char			*value;
	int				ascii_index;
	struct s_envar	*next;
}					t_envar;

// overarching struct
typedef struct s_minishell
{
	t_envar			*envars;
	t_cmd			*cmds;
	int 			**pfds; // stands for pipe file descriptors
	int				*pids;
}					t_minishell;

// GUI
void				print_cat(void);

// environment vars list helpers (CHANGED NAMES)
int					env_list_size(t_envar *env);
void				env_list_add_back(t_envar **envars, t_envar *new);
t_envar				*env_list_new(char *new_var);
char				*getvarname(char *new_var);
t_envar				*find_envar(char *varname, t_envar *ptr);
void				clean_env_list(t_minishell *michi);

// command list helpers (pipex)
int					cmd_list_size(t_cmd *cmd);
void				free_cmds(t_cmd **cmds);
t_cmd				*cmd_list_new(char *cmd, char *delim);
void				cmd_list_add_back(t_cmd **cmds, t_cmd *new);

// builtins
void				echo(char **cmd);
void				cd(char **cmd, t_minishell *michi);
void				pwd(t_envar **envars);
void				env(t_envar *envars);
void				michi_exit(t_minishell *michi, bool print_msg);

// builtins: export
void				export(t_minishell *michi, char **cmd);
void 				write_envars(t_envar *envar, bool order_alpha);

// builtins: export helpers
void				set_ascii_indices(t_envar **s);
int					max_strncmp(char *s1, char *s2);

// builtins: unset
void				unset(t_envar **envars, char **cmd);
int					count_args(char **cmd);

// error handling
void				handle_err(int errnum, int err, char *msg);

// Extract envars
void				add_envars(t_envar **envars, char **cmd,
						bool is_not_parsing);

// Input splitting
int					parse_pipes(t_minishell *michi, char *input);
int					is_builtin(t_cmd *node);

// executor
int					executor(t_cmd **cmds, t_envar **envars);

// executor helpers
void				start_children(t_minishell *michi);

// pipe handling
int					**setup_pipes(t_cmd **cmds);
int					**create_pipes(t_cmd *cmds, int **pfds);
void				close_pipe_ends(int i, int **pfds, int size);
void				free_pipe_arr(int **pfds);

#endif