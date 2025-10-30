/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:34:14 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 21:51:11 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	read_tiles(t_game *game, int fd, int element_count)
{
	char	*line;
	char	**elements;

	while (element_count)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n' && line[0] != '[')
		{
			elements = ft_split(line, " ");
			if (!elements)
				break ;
			if (elements[0][0] != '\n')
				validate_element(game, elements, &element_count);
			ft_free_matrix(elements);
		}
		freenull(&line);
	}
	if (element_count)
	{
		close(fd);
		exit_game(ERROR_MISSING_TEXTURE, game);
	}
}

static int	save_line(t_list **list, char *line, t_list *new)
{
	if (!new)
	{
		free(line);
		return (0);
	}
	ft_lstadd_back(list, new);
	return (1);
}

static void	read_map(t_game *game, t_list **list, int fd)
{
	t_list	*new;
	char	*line;
	int32_t	j;

	(void)game;
	new = NULL;
	j = 0;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line [0] == '[')
		{
			free(line);
			if (!new)
				continue ;
			else
				break ;
		}
		find_and_set_player_pos(game, line, j++);
		new = ft_lstnew(line);
		if (!save_line(list, line, new))
			break ;
	}
}

static void	read_section_by_section(t_game *g, t_list **ls, int fd)
{
	char	*l;
	int32_t	sect_count;

	sect_count = 3;
	while (sect_count)
	{
		l = ft_get_next_line(fd);
		if (!l)
		{
			printf(".cub misses some configurations\n");
			exit(1);// ! HARDCODED EXIT
		}
		if (!line_is_whitespace(l))
		{
			if (ft_strcmp(l, "[TILES]\n") == 0)
				read_tiles(g, fd, 6);
			else if (ft_strcmp(l, "[MAP]\n") == 0)
				read_map(g, ls, fd);
			else if (ft_strcmp(l, "[DECORATIONS]\n") == 0)
				read_decorations(g, fd);
			else
			{
				printf(".cub misses some configurations\n");
				exit(1);// ! HARDCODED EXIT
			}
			--sect_count;
		}
		free(l);
	}
}

void	read_file(t_game *game, t_list **list, const char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(ERROR_OPEN_FILE_FAILED, game);
	read_section_by_section(game, list, fd);
	close(fd);
	if (errno)
	{
		ft_lstclear(list, free);
		exit_game(ERROR_READ_FILE_FAILED, game);
	}
}
