/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:57:05 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/07 16:39:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	consume_color(int *col, const char **p, bool expect_coma)
{
	char	*end;
	
	errno = 0;
	*col = ft_strtoi(*p, &end);
	if (errno == ERANGE || end == *p || *col < 0 || *col > 255)
		return (error_found(ERROR_LIGHT_PARSING));
	if (expect_coma)
	{
		if (*end != ',')
			return (error_found(ERROR_LIGHT_PARSING));
		++end;
	}
	else if (*end != '\0')
		return (error_found(ERROR_LIGHT_PARSING));
	*p = end;
	return (0);
}

static int	extract_light_color(t_colorf *color, const char *field)
{
	int		r;
	int		g;
	int		b;

	if (consume_color(&r, &field, true)
		|| consume_color(&g, &field, true)
		|| consume_color(&b, &field, false))
		return (1);
	*color = colorf_from_uint(RGB(r, g, b));
	return (0);
}

int	parse_light_decoration(t_game *g, char *fields[])
{
	t_light			light;

	ft_memset(&light, 0, sizeof (light));
	light.intensity = ft_atof(fields[2]);
	light.strength = ft_atof(fields[3]);
	if (extract_light_color(&light.color, fields[4]))
		return (1);
	array_push(&g->lights, &light);
	return (0);
}