/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:35:22 by phutran           #+#    #+#             */
/*   Updated: 2025/10/21 17:31:35 by phutran          ###   ########.fr       */
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

#endif