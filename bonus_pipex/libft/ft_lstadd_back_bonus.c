/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:16:28 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:38:13 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst == 0 || new == 0)
		return ;
	ptr = *lst;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
}
/*
int	main(void)
{
	ft_lstadd_back(0, 0);
}*/
