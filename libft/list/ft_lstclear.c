/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:48:51 by phutran           #+#    #+#             */
/*   Updated: 2025/08/08 14:34:26 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		current = *lst;
		*lst = (*lst)->next;
		del(current->content);
		free(current);
	}
	*lst = NULL;
}
