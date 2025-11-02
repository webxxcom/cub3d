/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2025/11/02 16:25:21 by webxxcom         ###   ########.fr       */
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
		exit_game(ERROR_TEXTURE_PATH, game);
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
		exit_game(ERROR_INVALID_IDENTIFIER, game);
	--*element_count;
}
