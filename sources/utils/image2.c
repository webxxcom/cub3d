/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:07:45 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 22:07:08 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline uint32_t	im_get_pixel(t_image *img, int x, int y)
{
	if (y < 0 || y >= img->height || x < 0 || x >= img->width)
		return (0);
	return (*(unsigned int *)
		((char *)img->data + y * img->size_line + x * (img->bpp / 8)));
}

inline void	im_set_pixel(t_image *img, int x, int y, unsigned int color)
{
	if (y < 0 || y >= img->height || x < 0 || x >= img->width)
		return ;
	*(unsigned int *)
		((char *)img->data + y * img->size_line + x * (img->bpp / 8)) = color;
}

inline uint32_t	im_scale_pixel(uint32_t pixel, float factor)
{
	int	inv;

	if (factor < 0.f)
		factor = 0.f;
	inv = 0xFF * factor;
	return (RGB(
			(uint8_t)fminf(255.f, round(((pixel >> 16 & 0xFF) * inv) >> 8)),
			(uint8_t)fminf(255.f, round(((pixel >> 8 & 0xFF) * inv) >> 8)),
			(uint8_t)fminf(255.f, round(((pixel & 0xFF) * inv) >> 8))));
}

inline uint32_t	im_scale_pixel_rgbf(uint32_t pixel, t_colorf rgbf)
{
	return (RGB(
			(uint8_t)fminf(255.f, ((pixel >> 16 & 0xFF) * rgbf.r)),
			(uint8_t)fminf(255.f, ((pixel >> 8 & 0xFF) * rgbf.g)),
			(uint8_t)fminf(255.f, ((pixel & 0xFF) * rgbf.b)))
	);
}
