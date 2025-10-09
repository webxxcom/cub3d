/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:07:45 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 11:18:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	im_get_pixel(t_image *img, int x, int y)
{
	if (y < 0 || y >= img->height || x < 0 || x >= img->width)
		return (0);
	return (*(unsigned int *)
		(img->data + y * img->size_line + x * (img->bpp / 8)));
}

void	im_set_pixel(t_image *img, int x, int y, unsigned int color)
{
	if (y < 0 || y >= img->height || x < 0 || x >= img->width)
		return ;
	*(unsigned int *)
		(img->data + y * img->size_line + x * (img->bpp / 8)) = color;
}

void	im_move_pixels(t_image *dest, int off_x, int off_y, t_image *src)
{
	int				i;
	int				j;
	unsigned int	col;

	j = 0;
	while (j < src->height)
	{
		i = 0;
		while (i < src->width)
		{
			col = im_get_pixel(src, i, j);
			if (col != TRANSPARENT_COLOR && col != 0)
				im_set_pixel(dest, i + off_x, j + off_y, col);
			++i;
		}
		++j;
	}
}

t_image	*image_scale(void *mlx, t_image *src, int trgt_w, int trgt_h)
{
	const float		scale = (float)src->width / trgt_w;
	int				i;
	int				j;
	t_image			*res;
	unsigned int	col;

	res = im_get_empty(mlx, trgt_w, trgt_h);
	i = 0;
	while (i < trgt_w)
	{
		j = 0;
		while (j < trgt_h)
		{
			col = im_get_pixel(src, (int)(i * scale), (int)(j * scale));
			if (col != TRANSPARENT_COLOR)
				im_set_pixel(res, i, j, col);
			++j;
		}
		++i;
	}
	image_clean(mlx, src);
	src = res;
	return (src);
}
