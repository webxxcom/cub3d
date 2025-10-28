/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decorations.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:24:25 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/28 22:18:57 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECORATIONS_H
# define DECORATIONS_H

# include "cub3D.h"

typedef enum e_decor_types
{
	DECOR_WALL = 0,
	DECOR_LIGHT,
	DECOR_DOOR
}	t_decor_types;

typedef struct s_decoration
{
	t_decor_types	type;
	t_vec2i			pos;
	t_txtres_sides	direction;
	char			*texture_path;
	t_image			*texture;
	t_animation		*animation;
	int				state;
	void			(*interact)(t_game *const, struct s_decoration *);
	void			(*update)(t_game *const, struct s_decoration *);

	union
	{
		struct s_light
		{
			float		intensity;
			float		strength;
			t_colorf	color;
		}	light;
	};
}	t_decoration;

#endif