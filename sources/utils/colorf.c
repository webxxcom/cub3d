/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:23:09 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 11:38:58 by danslav1e        ###   ########.fr       */
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
	int	r;
	int	g;
	int	b;

	r = (int)(fminf(1.f, colorf.r) * 255);
	g = (int)(fminf(1.f, colorf.g) * 255);
	b = (int)(fminf(1.f, colorf.b) * 255);
	return (rgb(r, g, b));
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
	return (rgb((int)(r * 255.f), (int)(g * 255.f), (int)(b * 255.f)));
}
