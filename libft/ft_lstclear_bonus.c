/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:33:28 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/08 11:47:58 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (!*lst || !del)
		return ;
	current = *lst;
	while (current -> next != NULL)
	{
		next_node = current -> next;
		del(current -> content);
		free(current);
		current = next_node;
	}
	del(current -> content);
	free(current);
	*lst = NULL;
}
