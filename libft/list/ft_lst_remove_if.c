/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:29:18 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 12:51:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_remove_if(t_list **lst, void *data_ref,
			int (*cmp)(void *, void *),
			void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;

	if (!lst || !*lst || !cmp || !del)
		return;
	curr = *lst;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (cmp(curr->content, data_ref) == 0)
		{
			if (prev)
				prev->next = next;
			else
				*lst = next;
			del(curr->content);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}
