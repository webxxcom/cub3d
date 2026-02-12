/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 17:33:51 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_filename(const char *filename)
{
	char	*basename;
	size_t	len;

	basename = ft_strrchr(filename, '/');
	if (!basename)
		basename = (char *)filename;
	if (*basename == '/')
		basename++;
	len = ft_strlen(basename);
	if (len == 4 && !ft_strcmp(basename + len - 4, ".cub"))
		return (error_found(ERROR_INVALID_FILE));
	if (len < 4 || ft_strcmp(basename + len - 4, ".cub"))
		return (error_found(ERROR_FILE_EXTENSION));
	return (0);
}

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

static int	save_map(t_game *g, size_t j, char *l, size_t const longest)
{
	size_t	i;

	i = 0;
	g->map.tiles[j] = ft_calloc(longest, sizeof (t_tile));
	if (!g->map.tiles[j])
		return (error_found(ERROR_MALLOC_FAILED));
	while (l[i] && l[i] != '\n')
	{
		g->map.tiles[j][i].type = l[i];
		++i;
	}
	while (i < longest)
	{
		g->map.tiles[j][i].type = TILE_VOID;
		++i;
	}
	return (0);
}

static int	load_map(t_game *game, t_list *list)
{
	const size_t	longest = find_longest(list);
	const size_t	map_height = ft_lstsize(list);
	size_t			j;

	if (!list)
		return (error_found(ERROR_EMPTY_FILE));
	game->map.tiles = ft_calloc(map_height, sizeof (t_tile *));
	if (!game->map.tiles)
		return (error_found(ERROR_MALLOC_FAILED));
	game->map.size.x = longest;
	game->map.size.y = map_height;
	j = 0;
	while (list)
	{
		if (save_map(game, j, list->content, longest))
			return (1);
		list = list->next;
		++j;
	}
	return (0);
}

// list is a temporary buffer; load_map deep-copies all data
void	parse(t_game *g, const char *map_file)
{
	t_list	*list;

	list = NULL;
	if (validate_filename(map_file)
		|| read_file(g, &list, map_file)
		|| load_map(g, list)
		|| validate_map(g))
	{
		if (list)
			ft_lstclear(&list, free);
		exit_game(NULL, g);
	}
	ft_lstclear(&list, free);
}
