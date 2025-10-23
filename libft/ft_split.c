/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:23:34 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/23 15:57:44 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcount(const char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (*str == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == c || !str[i])
		{
			if (i != 0 && str[i - 1] != c)
				count++;
		}
		i++;
	}
	if (str[i - 1] != c)
		count++;
	return (count);
}

static int	ft_mod_strlen(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	**free_arr(char **arr, int i)
{
	while (arr[i--])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	if (arr)
		free(arr);
	return (NULL);
}

static char	**ft_make_arr(char **arr, char const *s, char c, int wcount)
{
	int	i;
	int	wlen;

	i = 0;
	while (wcount-- && s && *s)
	{
		while (*s && *s == c)
			s++;
		wlen = ft_mod_strlen(s, c);
		if (wlen > 0)
		{
			arr[i] = ft_substr(s, 0, wlen);
			if (!arr[i])
				return (free_arr(arr, i));
			i++;
			s += wlen;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	char	**arr;

	if (!s)
		return (NULL);
	wcount = ft_strcount(s, c);
	arr = ft_calloc(sizeof(char *), (wcount + 1));
	if (!arr)
		return (0);
	return (ft_make_arr(arr, s, c, wcount));
}

/*int	main(void)
{
	//char *s = "hola mundo1";
	char **result = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
	int i = 0;
	printf("%s\n", result[0]);
	while(result[i])
		free(result[i++]);
	free(result);
	return 0;
}*/
