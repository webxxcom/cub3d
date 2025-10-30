/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 18:07:05 by phutran          ###   ########.fr       */
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

static void	save_map(t_game *game, t_list *list, const size_t longest)
{
	size_t			i;
	int				j;
	char			*l;

	j = -1;
	while (list)
	{
		l = list->content;
		i = 0;
		game->map.tiles[++j] = ft_calloc(longest, sizeof (t_tile));
		if (!game->map.tiles[j])
		{
			printf("oops, malloc failed\n");
			exit(1);// ! HARDCODED EXIT
		}
		while (l[++i] && l[i] != '\n')
			game->map.tiles[j][i].type = l[i];
		while (++i < longest)
			game->map.tiles[j][i].type = ' ';
		list = list->next;
	}
}

static void	load_map(t_game *game, t_list *list)
{
	const size_t	longest = find_longest(list);
	const size_t	map_height = ft_lstsize(list);

	if (!list)
		exit_game(ERROR_EMPTY_FILE, game);
	game->map.tiles = ft_calloc(map_height, sizeof(t_tile *));
	if (!game->map.tiles)
	{
		ft_lstclear(&list, free);
		exit_game(ERROR_PARSE_MAP_FAILED, game);
	}
	save_map(game, list, longest);
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
