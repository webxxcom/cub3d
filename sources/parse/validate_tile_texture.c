/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tile_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2026/02/12 10:20:43 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*remove_nl(char *el)
{
	const size_t	len = ft_strlen(el);

	if (el[len - 1] == '\n')
		el[len - 1] = '\0';
	return (el);
}

int	validate_tile_texture(t_game *game, char **elements, int *element_count)
{
	if (!elements[1])
		return (error_found(ERROR_TEXTURE_PATH));
	if (!ft_strcmp(elements[0], "NO") && !game->paths.north)
		game->paths.north = ft_strdup(remove_nl(elements[1]));
	else if (!ft_strcmp(elements[0], "SO") && !game->paths.south)
		game->paths.south = ft_strdup(remove_nl(elements[1]));
	else if (!ft_strcmp(elements[0], "WE") && !game->paths.west)
		game->paths.west = ft_strdup(remove_nl(elements[1]));
	else if (!ft_strcmp(elements[0], "EA") && !game->paths.east)
		game->paths.east = ft_strdup(remove_nl(elements[1]));
	else if (!ft_strcmp(elements[0], "F") && !game->paths.floor)
		game->paths.floor = ft_strdup(remove_nl(elements[1]));
	else if (!ft_strcmp(elements[0], "C") && !game->paths.ceiling)
		game->paths.ceiling = ft_strdup(remove_nl(elements[1]));
	else
		return (error_found(ERROR_INVALID_IDENTIFIER));
	--*element_count;
	return (0);
}
