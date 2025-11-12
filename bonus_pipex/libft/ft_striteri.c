/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:08:30 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:33:25 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}
/*
void	func(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z' && i % 2 == 1)
		*c = 'x';
	return ;
}
#include <stdio.h>

int	main(void)
{
	char s[] = "hello, world";
	ft_striteri(s, func);
	printf("%s\n", s);
}*/
