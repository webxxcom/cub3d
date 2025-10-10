/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:28:21 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/11 00:58:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_minimap	minimap_init(void)
{
	return ((t_minimap){
		.pos = vec2i_construct(0, 650),
		.size = vec2i_construct(200, 150),
		.bgcol = 0x1A1A1A,
		.pcol = 0x4CAF50,
		.wcol = 0x9E9E9E,
		.rcol = 0x03A9F4,
		.fcol = 0x2E2E2E
		//.bcol = 0x606060
	});
}
