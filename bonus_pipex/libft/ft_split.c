/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:00:18 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:33:49 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	wordlen(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static unsigned int	wordcounter(char const *s, char c)
{
	unsigned int	wordcount;
	int				firstfound;

	wordcount = 0;
	firstfound = 0;
	while (*s)
	{
		if (*s != c && firstfound == 0)
		{
			firstfound = 1;
			wordcount++;
		}
		else if (*s == c)
			firstfound = 0;
		s++;
	}
	return (wordcount);
}

static void	kill(char **split, int i)
{
	while (i >= 0)
		free(split[i--]);
	free(split);
}

static char	**splitfill(char **split, char const *s, char c,
		unsigned int wordcount)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	while (*s && i < wordcount)
	{
		len = wordlen(s, c);
		if (len > 0)
		{
			split[i] = malloc(len + 1);
			if (split[i] == 0)
			{
				kill(split, i);
				return (0);
			}
			ft_strlcpy(split[i], s, len + 1);
			s += len - 1;
			i++;
		}
		s++;
	}
	split[wordcount] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	wordcount;
	char			**split;

	wordcount = wordcounter(s, c);
	split = malloc((wordcount + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	split = splitfill(split, s, c, wordcount);
	return (split);
}
/*
#include <stdio.h>

int	main(void)
{
	char **split = ft_split("hello, world. How are you?", ' ');
	for (unsigned int i = 0; i < wordcounter("hello, world. How are you?",
			' '); i++)
		printf("%s\n", split[i]);
}*/