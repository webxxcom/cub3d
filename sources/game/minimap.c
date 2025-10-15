/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:28:21 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 19:00:12 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_minimap	minimap_init(t_game *g)
{
	return ((t_minimap){
		.pos = vec2i_construct(0, g->h),
		.size = vec2i_construct(g->map.size.x * 8, g->map.size.y * 6),
		.bgcol = 0x1A1A1A,
		.pcol = COLOR_RED,
		.wcol = COLOR_GRAY,
		.rcol = 0x03A9F4,
		.fcol = 0x2E2E2E,
		.dcol = COLOR_YELLOW
	});
}
