/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:34:14 by phutran           #+#    #+#             */
/*   Updated: 2025/10/22 15:59:59 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	read_textures(t_game *game, int fd)
{
	char	*line;
	char	**elements;
	int		element_count;

	element_count = 6;
	while (element_count)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		elements = ft_split(line, ' ');
		if (!elements)
			break ;
		if (elements[0][0] != '\n')
			validate_element(game, elements, &element_count);
		free(elements);
		free(line);
	}
	if (element_count)
	{
		close(fd);
		exit_game(ERROR_MISSING_TEXTURE, game);
	}
}

static void	read_map(t_game *game, t_list **list, int fd)
{
	t_list	*new;
	char	*line;

	new = NULL;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' && !new)
		{
			free(line);
			continue ;
		}
		new = ft_lstnew(line);
		if (!new)
			break ;
		ft_lstadd_back(list, new);
	}
	if (errno)
	{
		close(fd);
		ft_lst_free(*list);
		exit_game(ERROR_READ_FILE_FAILED, game);
	}
}

void	read_file(t_game *game, t_list **list, const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(ERROR_OPEN_FILE_FAILED, game);
	read_textures(game, fd);
	read_map(game, list, fd);
	close(fd);
}
