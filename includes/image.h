/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:06:21 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:25:51 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "cub3D.h"

# define TRANSPARENT_COLOR 0xFF000000

typedef struct s_image
{
	void	*image;
	void	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}			t_image;

/**
 * Get image from file for display
 */
t_image		*im_load_from_xpmfile(void *mlx, char *filename);

/**
 * Initialize empty image with no pixels with width and height
 */
t_image		*im_get_empty(void *mlx, int const width, int const height);

/**
 * Clear image's pixel buffer by setting each byte to 0
 */
void		im_clear(t_image *im);

/**
 * Destroy image with its leftovers such as the pointer itself
 */
void		im_cleanup(void *mlx, t_image *image);

/**
 * Get image's pixel at (x, y) position
 */
uint32_t	im_get_pixel(t_image *img, int x, int y);

/**
 * Set the image's pixel with coordinates (x, y) to color 'color'
 */
void		im_set_pixel(t_image *img, int x, int y, unsigned int color);

/**
 * Returns the pixel darkened or brightened by factor.
 * Pixel becomes brighter if factor > 1 and darker if 0 < factor < 1
 */
uint32_t	im_scale_pixel(uint32_t pixel, float const factor);

/**
 * Scales each pixel's channel by factor descripted in rgbf
 * NOTE that the factors must be in range [0, 1] either way
 * 	the function's behaviour is undefined
 */
uint32_t	im_scale_pixel_rgbf(uint32_t pixel, t_colorf rgbf);

/**
 * 	Scale image by width to the desired width and height.
 * 	Assign scaled image to src and return it
 */
t_image		*image_scale(void *mlx, t_image *src, int target_width,
				int target_height);

#endif