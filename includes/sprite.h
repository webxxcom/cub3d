/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:48:25 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 12:24:11 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "cub3D.h"

typedef enum e_sprite_type
{
	SPRITE_STATIC = 0,
	SPRITE_ENEMY
}	t_sprite_type;

typedef struct s_sprite
{
	t_vec2f			pos;
	t_sprite_type	type;
	char			*texture_path;
	t_image			*texture;
	t_animation		*animation;
	float			dist;
	char			*interact_text;
	char			*looking_at_text;
	void			(*interact)(t_game *const, struct s_sprite *);
	void			(*update)(t_game *const, struct s_sprite *);
}	t_sprite;
