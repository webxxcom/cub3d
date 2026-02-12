/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoration_parse_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:43:00 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:22:07 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_direction(char *dir, t_txtres_sides *side)
{
	if (ft_strcmp(dir, "SOUTH") == 0)
		return (*side = SOUTH, 0);
	if (ft_strcmp(dir, "EAST") == 0)
		return (*side = EAST, 0);
	if (ft_strcmp(dir, "WEST") == 0)
		return (*side = WEST, 0);
	if (ft_strcmp(dir, "NORTH") == 0)
		return (*side = NORTH, 0);
	return (error_found(ERROR_DECOR_DIR));
}

bool	pos_is_parseable(char *field)
{
	while (ft_isspace(*field))
		++field;
	if (*field == '-' || *field == '+')
		++field;
	return (ft_isdigit(*field));
}
