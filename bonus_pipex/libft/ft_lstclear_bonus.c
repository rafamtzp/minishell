/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:48:23 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/09 17:46:12 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr1;
	t_list	*ptr2;

	if (lst == 0 || del == 0 || *lst == 0)
		return ;
	ptr1 = *lst;
	while (ptr1->next != 0)
	{
		ptr2 = ptr1->next;
		ft_lstdelone(ptr1, del);
		ptr1 = ptr2;
	}
	ft_lstdelone(ptr1, del);
	*lst = 0;
	lst = 0;
}
