/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 21:49:33 by webxxcom         ###   ########.fr       */
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
		exit_game(ERROR_INVALID_FILE, game);
	if (len < 4 || ft_strcmp(basename + len - 4, ".cub"))
		exit_game(ERROR_FILE_EXTENSION, game);
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



static void	save_map(t_game *game, int j, char *l, const size_t longest)
{
	size_t	i;

	i = 0;
	game->map.tiles[j] = ft_calloc(longest, sizeof (t_tile));
	if (!game->map.tiles[j])
	{
		printf("oops, malloc failed\n");
		exit(1); // ! HARDCODED EXIT
	}
	while (l[i] && l[i] != '\n')
	{
		game->map.tiles[j][i].type = l[i];
		++i;
	}
	while (i < longest)
	{
		game->map.tiles[j][i].type = ' ';
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
		exit_game(ERROR_EMPTY_FILE, game);
	game->map.tiles = ft_calloc(map_height, sizeof(t_tile *));
	if (!game->map.tiles)
	{
		ft_lstclear(&list, free);
		exit_game(ERROR_PARSE_MAP_FAILED, game);
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

void	parse(t_game *game, const char *map_file)
{
	t_list	*list;

	list = NULL;
	validate_filename(game, map_file);
	read_file(game, &list, map_file);
	load_map(game, list);
	ft_lstclear(&list, free);
	validate_map(game);
}
