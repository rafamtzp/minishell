/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:56:47 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:33 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*startfind(char const *s1, char const *set);
static char const	*endfind(char const *s1, char const *set,
						char const *start);

char	*ft_strtrim(char const *s1, char const *set)
{
	int			len;
	char const	*start;
	char const	*end;

	start = startfind(s1, set);
	if (*start == '\0')
		return (ft_substr(start, 0, 0));
	end = endfind(s1, set, start);
	len = 0;
	while (&start[len] != end)
		len++;
	return (ft_substr(start, 0, len + 1));
}

static char const	*startfind(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (!set[j])
			return (&s1[i]);
		i++;
	}
	return (&s1[i]);
}

static char const	*endfind(char const *s1, char const *set, char const *start)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && &s1[i] != start)
	{
		j = 0;
		while (set[j] && set[j] != s1[i])
			j++;
		if (!set[j])
			return (&s1[i]);
		i--;
	}
	return (&s1[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	char const *s = "aa";
	char const *set = "a";

	printf("%s\n", ft_strtrim(s, set));
}*/