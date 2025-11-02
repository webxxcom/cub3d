/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:07:21 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 17:51:59 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image	*im_load_from_xpmfile(void *mlx, char *filename)
{
	t_image	*im;

	if (!filename || !mlx)
		return (NULL);
	im = ft_calloc(1, sizeof (t_image));
	if (!im)
		return (NULL);
	im->image = mlx_xpm_file_to_image(mlx, filename, &im->width, &im->height);
	if (!im->image)
		return (im_cleanup(mlx, im), NULL);
	im->data = mlx_get_data_addr(im->image,
			&im->bpp, &im->size_line, &im->endian);
	if (!im->data)
		return (im_cleanup(mlx, im), NULL);
	return (im);
}

t_image	*im_get_empty(void *mlx, const int width, const int height)
{
	t_image	*res;

	if (!mlx)
		return (NULL);
	res = ft_calloc(1, sizeof (t_image));
	if (!res)
		return (NULL);
	res->image = mlx_new_image(mlx, width, height);
	if (!res->image)
		return (im_cleanup(mlx, res), NULL);
	res->width = width;
	res->height = height;
	res->data = mlx_get_data_addr(res->image,
			&res->bpp, &res->size_line, &res->endian);
	if (!res->data)
		return (im_cleanup(mlx, res), NULL);
	return (res);
}

void	im_clear(t_image *im)
{
	ft_memset(im->data, 0, im->height * im->size_line);
}

void	im_cleanup(void *mlx, t_image *image)
{
	if (!image || !mlx)
		return ;
	if (image->image)
		mlx_destroy_image(mlx, image->image);
	freenull(&image);
	image = NULL;
}
