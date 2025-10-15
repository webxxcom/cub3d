/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:21:48 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 21:39:16 by webxxcom         ###   ########.fr       */
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

t_frame	*frame_get_with_size(void *mlx, int width, int height)
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

void	sprite_to_frames(void *mlx, t_image *sprite, t_animation *anim)
{
	const int	frame_offset = 64;
	int			curr_frame;

	anim->total_frames = sprite->width / frame_offset;
	anim->frames = ft_calloc(1, anim->total_frames * sizeof (t_frame *));
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

t_animation	*init_animation(void *mlx, char *animation_file)
{
	t_animation	*animation;
	t_image		*sprite;

	animation = ft_calloc(1, sizeof (t_animation));
	if (!animation)
		return (NULL);
	sprite = im_load_from_xpmfile(mlx, animation_file);
	if (!sprite)
		return (free(animation), NULL);
	sprite_to_frames(mlx, sprite, animation);
	im_cleanup(mlx, sprite);
	return (animation);
}

void	animation_clean(void *mlx, t_animation *anim)
{
	int	i;

	i = 0;
	while (i < anim->total_frames)
		frame_clean(mlx, anim->frames[i++]);
	free(anim->frames);
	free(anim);
}
