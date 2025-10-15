/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:39:22 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/15 14:19:50 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

// command node struct
typedef struct s_cmdnode
{
	char				**cmd;
	char				*path;
	int					infile;
	int					outfile;
	struct s_cmdnode	*next;
}						t_cmdnode;

// environment variable struct
typedef struct s_envar
{
	char				*varname;
	char				**values;
	// values instead of paths bc there could be values and paths mixed up (?)
	// can't remember why we need an index....
	struct s_envar		*next;
}						t_envar;

// overarching struct
typedef struct s_minishell
{
	t_envar				*envars;
	t_cmdnode			*cmds;
}						t_minishell;

#endif