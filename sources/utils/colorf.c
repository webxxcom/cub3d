/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:23:09 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 16:33:04 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline t_colorf	colorf_from_uint(uint32_t color)
{
	return ((t_colorf){
		.r = ((color >> 16) & 0xFF) / 255.f,
		.g = ((color >> 8) & 0xFF) / 255.f,
		.b = (color & 0xFF) / 255.f
	});
}

inline uint32_t	colorf_to_uint(t_colorf colorf)
{
	return (RGB((int)(fminf(1.f, colorf.r) * 255),
		(int)(fminf(1.f, colorf.g) * 255),
		(int)(fminf(1.f, colorf.b) * 255)
	));
}

inline t_colorf	colorf_from_rgbf(float r, float g, float b)
{
	return ((t_colorf){
		.r = r,
		.g = g,
		.b = b
	});
}

inline t_colorf	colorf_init(void)
{
	return ((t_colorf){
		.r = 0,
		.g = 0,
		.b = 0
	});
}

inline uint32_t	colorf_from_rgbf_to_uint(float r, float g, float b)
{
	return (RGB((int)(r * 255.f), (int)(g * 255.f), (int)(b * 255.f)));
}
