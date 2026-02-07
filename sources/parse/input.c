/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:34:14 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 12:26:05 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	read_tiles(t_game *game, int fd, int el_count)
{
	char	*line;
	char	**els;
	int		exit_status;

	exit_status = 0;
	while (el_count && (exit_status == 0))
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (!line_is_whitespace(line) && line[0] != '[')
		{
			els = ft_split(line, " ");
			if (els)
			{
				if (els[0][0] != '\n')
					exit_status = validate_element(game, els, &el_count);
				ft_free_matrix(els);
			}
			else
				exit_status = 1;
		}
		freenull(&line);
	}
	return ((el_count != 0) || (exit_status != 0));
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

static int	read_map(t_game *game, t_list **list, int fd)
{
	t_list	*new;
	char	*line;
	int32_t	j;

	new = NULL;
	j = 0;
	while (1)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		if (line_is_whitespace(line) || line [0] == '[')
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
	return (0);
}

static int	read_section_by_section(t_game *g, t_list **ls, int fd)
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
			exit(1); // ! HARDCODE
		}
		if (!line_is_whitespace(l))
		{
			if (ft_strcmp(l, "[TILES]\n") == 0)
			{
				if (read_tiles(g, fd, 6) != 0)
					return (freenull(&l), 1);
			}
			else if (ft_strcmp(l, "[MAP]\n") == 0)
			{
				if (read_map(g, ls, fd) != 0)
					return (freenull(&l), 1);
			}
			else if (ft_strcmp(l, "[DECORATIONS]\n") == 0)
			{
				if (read_decorations(g, fd) != 0)
					return (freenull(&l), 1);
			}
			else
			{
				printf("unknown configuration occured in .cub file: %s\n", l);
				free(l);
				return (1);
			}
			--sect_count;
		}
		freenull(&l);
	}
	return (0);
}



int		read_file(t_game *game, t_list **list, const char *map_file)
{
	int	res;
	int	fd;

	res = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return error_found(ERROR_OPEN_FILE_FAILED);
	res = read_section_by_section(game, list, fd);
	close(fd);
	if (errno)
		return (error_found(ERROR_READ_FILE_FAILED));
	return (res);
}
