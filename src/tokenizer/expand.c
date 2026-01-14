/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:14:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/14 16:59:59 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *clean_and_expand(char *word)
{
	char *tmp;
	int quotes[2];
	int i;
	int len;

	i = 0;
	len = get_wlen(word);
	while (i < len)
	{
		
		tmp[i] = word[i];
		i++;
	}
	tmp[i] = 0;
	printf("tmp: %s\n", tmp);
	return (NULL);
}
