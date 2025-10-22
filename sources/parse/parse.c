/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/21 18:11:15 by phutran          ###   ########.fr       */
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
