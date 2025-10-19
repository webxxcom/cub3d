/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:35:22 by phutran           #+#    #+#             */
/*   Updated: 2025/09/25 15:35:36 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_game	t_game; 

void	parse_map(t_game *game, const char *filename);
void	validate_filename(t_game *game, const char *filename);
void	validate_map(t_game *game);

#endif