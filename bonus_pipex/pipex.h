/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:16:59 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/10 12:17:15 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1

typedef struct s_cmd
{
	char				**cmd; // last ptr is NULL
	char				*path;
	int					infile;
	int					outfile;
	bool				is_append; // false by default
	char				*delim; // NULL by default
	struct s_cmd	*next;
}	t_cmd;

// parsing
void parsing_storing_checking(int argc, char **argv, t_cmd **cmds);
int	max_strlen(char *s1, char *s2);

// execution
void	start_children(t_cmd *cmds, pid_t *pids, int **pfds, char **env);

// exit
void	close_pipe_ends(int i, int **pfds, int size);
void	handle_err(t_cmd **cmds, int **pfds);
void	close_first_and_last(t_cmd **cmds);
void	free_pipe_arr(int **pfds);
void	free_cmds(t_cmd **cmds);

// cmd list helpers
t_cmd	*cmd_list_new(char *cmd, char *delim);
void	cmd_list_add_back(t_cmd **cmds, t_cmd *new);
int 	cmd_list_size(t_cmd *cmd);

// setup pipes
int  **setup_pipes(t_cmd **cmds);

#endif