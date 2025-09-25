/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:35:39 by phutran           #+#    #+#             */
/*   Updated: 2025/09/25 15:35:41 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



static void	read_map(t_game *game, t_list **list, const char *map_file)
{
	t_list	*new;
	char	*line;
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(ERROR_OPEN_FILE_FAILED, game);
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		new = ft_lstnew(line);
		if (!new)
			break ;
		ft_lstadd_back(list, new);
	}
	close(fd);
	if (errno)
	{
		ft_lst_free(*list);
		exit_game(ERROR_READ_FILE_FAILED, game);
	}
}

static void	load_map(t_game *game, t_list *list)
{
	int	i;
	int	width;

	if (!list)
		exit_game(ERROR_EMPTY_FILE, game);
	game->map = malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (!game->map)
	{
		ft_lst_free(list);
		exit_game(ERROR_PARSE_MAP_FAILED, game);
	}
	i = 0;
	while (list)
	{
		game->map[i] = list->content;
		width = ft_strlen(list->content);
		if (game->map[i][width - 1] == '\n')
			game->map[i][width - 1] = '\0';
		list = list->next;
		++i;
	}
	game->map[i] = NULL;
}

void	parse_map(t_game *game, const char *map_file)
{
	t_list	*list;

	list = NULL;
	validate_filename(game, map_file);
	read_map(game, &list, map_file);
	load_map(game, list);
	ft_lst_free(list);
	validate_map(game);
}