/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_keybindings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:02:56 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 22:03:32 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_keybindings(t_game *g)
{
	const int32_t	dbg_x = 10;
	const int32_t	dbg_line_h = 20;
	int32_t			y;

	if (!g->show_keys)
		return ;
	y = g->h / 3;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"W / ARROW_UP : Move forward");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"S / ARROW_DOWN : Move backward");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"A / ARROW_LEFT : Move left");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"D / ARROW_RIGHT : Move right");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"Left Shift : Sprint");
	y += dbg_line_h;
	mlx_string_put(g->mlx, g->win, dbg_x, y, COLOR_WHITE,
		"F1 : Toggle debug info");
}
