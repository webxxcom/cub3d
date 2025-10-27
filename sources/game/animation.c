/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:21:48 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 16:06:59 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_frame	*extract_frame_from_sprite(
	int curr_frame, t_frame *frame, t_image *sprite)
{
	int		i;
	int		j;
	int		z;

	if (!frame)
		return (NULL);
	j = 0;
	while (j < frame->image->height)
	{
		i = curr_frame * frame->image->width;
		z = 0;
		while (z < frame->image->width)
		{
			im_set_pixel(frame->image, z, j, im_get_pixel(sprite, i, j));
			++z;
			++i;
		}
		++j;
	}
	return (frame);
}

static t_frame	*frame_get_with_size(void *mlx, int width, int height)
{
	t_frame	*frame;

	frame = ft_calloc(1, sizeof (t_frame));
	if (!frame)
		return (NULL);
	frame->image = im_get_empty(mlx, width, height);
	if (!frame->image)
		return (NULL);
	return (frame);
}

static void	sprite_to_frames(void *mlx, t_image *sprite, t_animation *anim)
{
	const int	frame_offset = TILE_SIZE;
	size_t		curr_frame;

	anim->total_frames = sprite->width / frame_offset;
	anim->frames = ft_calloc(anim->total_frames, sizeof (t_frame *));
	if (!anim->frames)
		return ;
	curr_frame = 0;
	while (curr_frame < anim->total_frames)
	{
		anim->frames[curr_frame] = extract_frame_from_sprite(curr_frame,
				frame_get_with_size(mlx, frame_offset, sprite->height), sprite);
		++curr_frame;
	}
}

t_animation	*init_animation(t_game *g, char *filename)
{
	t_animation	*animation;
	t_image		*sprite;

	animation = ft_calloc(1, sizeof (t_animation));
	if (!animation)
		return (NULL);
	sprite = im_load_from_xpmfile(g->mlx, filename);
	if (!sprite)
		return (free(animation), NULL);
	sprite_to_frames(g->mlx, sprite, animation);
	return (animation);
}

void	animation_clean(void *mlx, t_animation *anim)
{
	size_t	i;

	i = 0;
	while (i < anim->total_frames)
		frame_clean(mlx, anim->frames[i++]);
	free(anim->frames);
	free(anim);
}
