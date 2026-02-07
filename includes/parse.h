/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:35:22 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 16:31:35 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_game	            t_game; 
typedef struct s_map	            t_map;
typedef struct s_vector_2d_float	t_vec2f;

void	parse(t_game *game, const char *filename);
int 	read_file(t_game *game, t_list **list, const char *map_file);
int		validate_tile_texture(t_game *game, char **elements, int *element_count);
int		validate_map(t_game *const game);
int		parse_normal_wall_decoration(t_game *g, char *fields[]);
int		parse_door_decoration(t_game *g, char *fields[]);
int		parse_light_decoration(t_game *g, char *fields[]);
int		parse_decoration(t_game *g, char *line);
int		parse_sprite_decoration(t_game *g, char *fields[]);
int		read_decorations(t_game *g, int fd);
void	set_player_start_pos(t_game *g, int x, int y, char dir);
void	find_and_set_player_pos(t_game *g, char *l, int j);
char	*remove_nl(char *el);
char	**get_chars_map(t_map *map);
int 	error_found(char *error);

t_vec2f	extract_posf(t_game *const g, char *fields[]);

bool	is_valid_mapelement(int el);
bool	is_player_tile(int el);

#endif