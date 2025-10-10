/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:06:21 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 11:24:14 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_image
{
	void	*image;
	void	*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

# define TRANSPARENT_COLOR 0xFF000000

/**
 * Get image from file for display 
 */
t_image			*im_load_from_xpmfile(void *mlx, char *filename);

/**
 * Initialize empty image with no pixels with width and height
 */
t_image			*im_get_empty(void *mlx, int const width, int const height);

/**
 * Clear image's pixel buffer by setting each byte to 0
 */
void			im_clear(t_image *im);

/**
 * Destroy image with its leftovers such as the pointer itself
 */
void			im_cleanup(void *mlx, t_image *image);

/**
 * Get image's pixel at (x, y) position
 */
unsigned int	im_get_pixel(t_image *img, int x, int y);

/**
 * Set the image's pixel with coordinates (x, y) to color 'color'
 */
void			im_set_pixel(t_image *img, int x, int y, unsigned int color);

/**
 * 	Move all pixels from 'src' t_image to 'dest' t_image
 * offsetting the 'dest' by (off_x * 32, off_y * 32)
 * 	The moving is performed on internal t_image->data raw byte array
 */
void			im_move_pixels(t_image *dest, int off_x,
					int off_y, t_image *src);

/**
 * 	Scale image by width to the desired width and height.
 * 	Assign scaled image to src and return it
 */
t_image			*image_scale(void *mlx, t_image *src,
					int target_width, int target_height);