/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:14:36 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:35:41 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# define ANIMATION_DELAY 200

typedef struct s_game	t_game;
typedef struct s_frame	t_frame;
typedef struct s_image	t_image;

typedef enum e_animation_types
{
	ANIM_DOOR_OPEN_CLOSE = 0,
	ANIM_LAB_METAL_GREY_TILES_HEXDOOR,
	ANIM_NUMBER
}						t_animation_types;

typedef struct s_animation
{
	size_t				total_frames;
	size_t				curr_frame_n;
	t_frame				**frames;
}						t_animation;

t_animation				*init_animation(t_game *g, char *filename);

/**
 * 	Get current animation's frame.
 */
t_image					*animation_get_current_image(t_animation *anim);

/**
 * 	Free all resources allocated by s_animation structure and pointer itself
 */
void					animation_cleanup(void *mlx, t_animation *anim);

#endif