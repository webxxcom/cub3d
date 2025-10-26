/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:35:22 by phutran           #+#    #+#             */
/*   Updated: 2025/10/26 13:29:40 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_game	t_game; 

void	parse(t_game *game, const char *filename);
void	read_file(t_game *game, t_list **list, const char *map_file);
void	validate_filename(t_game *game, const char *filename);
void	validate_element(t_game *game, char **elements, int *element_count);
void	validate_map(t_game *game);
void	parse_normal_wall_decoration(t_game *g, char *fields[]);
void	parse_door_decoration(t_game *g, char *fields[]);
void	parse_light_decoration(t_game *g, char *fields[]);
char	*remove_nl(char *el);

#endif