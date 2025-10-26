/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:57:01 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 13:41:07 by webxxcom         ###   ########.fr       */
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
	if (!elements[1] || access(elements[1], F_OK | R_OK) == 0)
		exit_game(ERROR_TEXTURE_PATH, game);
	else
		errno = 0;
	if (!ft_strncmp(elements[0], "NO", 3) && !game->paths.north)
		game->paths.north = remove_nl(elements[1]);
	else if (!ft_strncmp(elements[0], "SO", 3) && !game->paths.south)
		game->paths.south = remove_nl(elements[1]);
	else if (!ft_strncmp(elements[0], "WE", 3) && !game->paths.west)
		game->paths.west = remove_nl(elements[1]);
	else if (!ft_strncmp(elements[0], "EA", 3) && !game->paths.east)
		game->paths.east = remove_nl(elements[1]);
	else if (!ft_strncmp(elements[0], "F", 2) && !game->paths.floor)
		game->paths.floor = remove_nl(elements[1]);
	else if (!ft_strncmp(elements[0], "C", 2) && !game->paths.ceiling)
		game->paths.ceiling = remove_nl(elements[1]);
	else
		exit_game(ERROR_INVALID_IDENTIFIER, game);
	--*element_count;
}
