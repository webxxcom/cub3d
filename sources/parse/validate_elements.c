/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2025/11/04 15:01:28 by phutran          ###   ########.fr       */
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

void	validate_element(t_game *game, char **elements, int *element_count)
{
	if (!elements[1] || access(elements[1], F_OK | R_OK) == 0) // ! ACCESS is forbidden
		exit_game(ERROR_TEXTURE_PATH, game, NULL);
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
		exit_game(ERROR_INVALID_IDENTIFIER, game, NULL);
	--*element_count;
}
