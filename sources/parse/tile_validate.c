/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:59:55 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 10:35:06 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline int	error_found(char *error)
{
	if (errno)
		printf("%s: %s\n", error, strerror(errno));
	else
		printf("%s\n", error);
	return (1);
}

inline bool	is_valid_mapelement(int el)
{
	return (el == TILE_FLOOR || el == TILE_WALL || el == TILE_PLAYER_N
		|| el == TILE_PLAYER_S || el == TILE_PLAYER_E || el == TILE_PLAYER_W
		|| el == TILE_VOID || el == TILE_DOOR);
}

inline bool	is_player_tile(int el)
{
	return (el == TILE_PLAYER_N || el == TILE_PLAYER_S
		|| el == TILE_PLAYER_E || el == TILE_PLAYER_W);
}
