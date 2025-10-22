/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/22 22:26:25 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_map(t_game *game, t_list *list)
{
	int	i;
	int	width;

	if (!list)
		exit_game(ERROR_EMPTY_FILE, game);
	game->map.tiles = malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (!game->map.tiles)
	{
		ft_lst_free(list);
		exit_game(ERROR_PARSE_MAP_FAILED, game);
	}
	i = 0;
	while (list)
	{
		game->map.tiles[i] = list->content;
		width = ft_strlen(list->content);
		if (game->map.tiles[i][width - 1] == '\n')
			game->map.tiles[i][width - 1] = '\0';
		list = list->next;

		++i;
	}
	game->map.tiles[i] = NULL;
	game->map.size.x = width;
	game->map.size.y = i;
}

void	parse(t_game *game, const char *map_file)
{
	t_list	*list;

	list = NULL;
	validate_filename(game, map_file);
	read_file(game, &list, map_file);
	load_map(game, list);
	ft_lst_free(list);
	validate_map(game);
}
