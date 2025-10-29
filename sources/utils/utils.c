/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:40:28 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/29 10:43:01 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline void	toggle_bool(bool *flag)
{
	if (*flag == true)
		*flag = false;
	else
		*flag = true;
}

bool	line_is_whitespace(char *l)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		if (!ft_isspace(l[i]))
			return (false);
		++i;
	}
	return (true);
}
