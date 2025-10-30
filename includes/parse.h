/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:35:22 by phutran           #+#    #+#             */
/*   Updated: 2025/10/30 16:29:34 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_game	t_game; 
typedef struct s_map	t_map;

void	parse(t_game *game, const char *filename);
void	read_file(t_game *game, t_list **list, const char *map_file);
void	validate_element(t_game *game, char **elements, int *element_count);
void	validate_map(t_game *game);
void	parse_normal_wall_decoration(t_game *g, char *fields[]);
void	parse_door_decoration(t_game *g, char *fields[]);
void	parse_light_decoration(t_game *g, char *fields[]);
void	parse_decoration(t_game *g, char *line);
void	read_decorations(t_game *g, int fd);
void	set_player_start_pos(t_game *g, int x, int y, char dir);
void	find_and_set_player_pos(t_game *g, char *l, int j);
char	*remove_nl(char *el);
char	**get_chars_map(t_map *map);

#endif