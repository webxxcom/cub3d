/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 11:16:44 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static size_t	find_longest(t_list *l)
{
	size_t	longest;
	size_t	tmp_len;

	longest = 0;
	while (l)
	{
		tmp_len = ft_strlen(l->content);
		if (tmp_len > longest)
			longest = tmp_len;
		l = l->next;
	}
	return (longest);
}

static void	remove_nl(char *l, int32_t len)
{
	int32_t	i;
	bool	nl_found;

	i = 0;
	nl_found = false;
	while (!nl_found)
	{
		if (l[i] == '\n')
		{
			l[i] = ' ';
			nl_found = true;
		}
		++i;
	}
	while (i < len)
		l[i++] = ' ';
	l[i - 1] = '\0';
}

static void	load_map(t_game *game, t_list *list)
{
	const size_t	longest = find_longest(list);
	const size_t	map_height = ft_lstsize(list);
	int				i;

	if (!list)
		exit_game(ERROR_EMPTY_FILE, game);
	game->map.tiles = ft_calloc(map_height + 1, sizeof(char *));
	if (!game->map.tiles)
	{
		ft_lst_free(list);
		exit_game(ERROR_PARSE_MAP_FAILED, game);
	}
	i = 0;
	while (list)
	{
		game->map.tiles[i] = realloc(list->content, longest);
		remove_nl(game->map.tiles[i], longest);
		list = list->next;
		++i;
	}
	game->map.tiles[map_height] = NULL;
	game->map.size.x = longest;
	game->map.size.y = map_height;
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
