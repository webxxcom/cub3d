/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:23:09 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 18:41:24 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_colorf	colorf_from_uint(uint32_t color)
{
	return ((t_colorf){
		.r = ((color >> 16)	& 0xFF) / 255.f,
		.g = ((color >> 8)	& 0xFF) / 255.f,
		.b = ( color		& 0xFF) / 255.f
	});
}

uint32_t	colorf_to_uint(t_colorf colorf)
{
	return (RGB(
		(int)(fminf(1.f, colorf.r) * 255),
		(int)(fminf(1.f, colorf.g) * 255),
		(int)(fminf(1.f, colorf.b) * 255)
	));
}

t_colorf	colorf_from_rgbf(float r, float g, float b)
{
	return ((t_colorf){
		.r = r,
		.g = g,
		.b = b
	});
}