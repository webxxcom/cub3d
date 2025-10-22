/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2025/10/22 15:59:52 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate_element(t_game *game, char **elements, int *element_count)
{
	if (!elements[1] || access(elements[1], F_OK | R_OK) == 0)
		exit_game(ERROR_TEXTURE_PATH, game);
	else
		errno = 0;
	if (!ft_strncmp(elements[0], "NO", 3) && !game->paths.north)
		game->paths.north = elements[1];
	else if (!ft_strncmp(elements[0], "SO", 3) && !game->paths.south)
		game->paths.south = elements[1];
	else if (!ft_strncmp(elements[0], "WE", 3) && !game->paths.west)
		game->paths.west = elements[1];
	else if (!ft_strncmp(elements[0], "EA", 3) && !game->paths.east)
		game->paths.east = elements[1];
	else if (!ft_strncmp(elements[0], "F", 2) && !game->paths.floor)
		game->paths.floor = elements[1];
	else if (!ft_strncmp(elements[0], "C", 2) && !game->paths.ceiling)
		game->paths.ceiling = elements[1];
	else
		exit_game(ERROR_INVALID_IDENTIFIER, game);
	--*element_count;
}
