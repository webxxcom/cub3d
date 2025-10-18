/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:14:36 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 11:52:26 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# define ANIMATION_DELAY 200

typedef struct s_game t_game;
typedef struct s_frame t_frame;
typedef struct s_image t_image;

typedef enum
{
	ANIM_DOOR_OPEN_CLOSE = 0,
	ANIM_NUMBER
}	t_animation_kinds;

typedef struct s_animation
{
	int		total_frames;
	int		curr_frame_n;
	t_frame	**frames;
}	t_animation;

void			sprite_to_frames(void *mlx, t_image *sprite, t_animation *anim);

t_animation		*init_animation(void *mlx, char *animation_file);

/**
 * 	A hook function for mlx to loop it and animate the
 * animation anim passed to the function.
 * 	To use properly the animation's argument must
 * be passed to mlx_loop_hook when called
 */
int			animation_update(t_game *g, t_animation *anim, int anim_state);

/**
 * 	Get current animation's frame.
 */
t_image		*animation_get_current_image(t_animation *anim);

/**
 * 	Free all resources allocated by s_animation structure and pointer itself
 */
void			animation_clean(void *mlx, t_animation *anim);

#endif