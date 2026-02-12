/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:40:28 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 11:49:40 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freenull(void *p)
{
	free(*(void **)p);
	*(void **)p = NULL;
}

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

uint32_t	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
