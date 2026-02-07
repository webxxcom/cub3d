/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 12:27:00 by webxxcom         ###   ########.fr       */
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

int	validate_element(t_game *game, char **elements, int *element_count)
{
	if (!elements[1] || access(elements[1], F_OK | R_OK) == 0) // ! ACCESS is forbidden
		return error_found(ERROR_TEXTURE_PATH);
	else
		errno = 0;
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

inline int	error_found(char *error)
{
	if (errno)
		printf("%s: %s\n", error, strerror(errno));
	else
		printf("%s\n", error);
	return (1);
}

inline bool	is_valid_mapelement(int el)
{
	return (el == TILE_FLOOR || el == TILE_WALL || el == TILE_PLAYER_N
		|| el == TILE_PLAYER_S || el == TILE_PLAYER_E || el == TILE_PLAYER_W
		|| el == TILE_VOID || el == TILE_DOOR);
}
