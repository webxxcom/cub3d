/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2026/02/06 18:49:46 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_filename(t_game *game, const char *filename)
{
	char	*basename;
	int		len;

	basename = ft_strrchr(filename, '/');
	if (!basename)
		basename = (char *)filename;
	if (*basename == '/')
		basename++;
	len = ft_strlen(basename);
	if (len == 4 && !ft_strcmp(basename + len - 4, ".cub"))
		exit_game(ERROR_INVALID_FILE, game, NULL);
	if (len < 4 || ft_strcmp(basename + len - 4, ".cub"))
		exit_game(ERROR_FILE_EXTENSION, game, NULL);
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

static void	save_map(t_game *g, int j, char *l, const size_t longest)
{
	size_t	i;

	i = 0;
	g->map.tiles[j] = ft_calloc(longest, sizeof (t_tile));
	if (!g->map.tiles[j])
		exit_game("oops, malloc failed\n", g, NULL);
	while (l[i] && l[i] != '\n')
	{
		g->map.tiles[j][i].type = l[i];
		++i;
	}
	while (i < longest)
	{
		g->map.tiles[j][i].type = ' ';
		++i;
	}
}

static void	load_map(t_game *game, t_list *list)
{
	const size_t	longest = find_longest(list);
	const size_t	map_height = ft_lstsize(list);
	int				j;
	char			*l;

	if (!list)
		exit_game(ERROR_EMPTY_FILE, game, NULL);
	game->map.tiles = ft_calloc(map_height, sizeof(t_tile *));
	if (!game->map.tiles)
	{
		ft_lstclear(&list, free);
		exit_game(ERROR_PARSE_MAP_FAILED, game, NULL);
	}
	j = 0;
	while (list)
	{
		l = list->content;
		save_map(game, j, l, longest);
		list = list->next;
		++j;
	}
	game->map.size.x = longest;
	game->map.size.y = map_height;
}

void	parse(t_game *g, const char *map_file)
{
	int		exit_status;
	t_list	*list;

	list = NULL;
	exit_status = false;
	validate_filename(g, map_file);
	exit_status = read_file(g, &list, map_file);
	if (!exit_status)
		load_map(g, list);
	if (list)
		ft_lstclear(&list, free);
	if (exit_status)
		exit_game(NULL, g, NULL);
	if (validate_map(g))
		exit_game(NULL, g, NULL);
}
