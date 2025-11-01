/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:30:53 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 22:14:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static inline void	update_sprite_animations(t_game *g, t_array *sprites)
{
	t_sprite	*tmp;
	size_t		i;

	i = 0;
	while (i < array_size(sprites))
	{
		tmp = array_get(sprites, i);
		if (tmp->update)
			tmp->update(g, tmp);
		++i;
	}
}

static inline void	update_decor_animations(t_game *g, t_array *decors)
{
	t_decoration	*tmp;
	size_t			i;

	i = 0;
	while (i < array_size(decors))
	{
		tmp = array_get(decors, i);
		if (tmp->update)
			tmp->update(g, tmp);
		++i;
	}
}

void	update_animations(t_game *g)
{
	update_decor_animations(g, &g->map.decorations);
	update_sprite_animations(g, &g->sprites);
}
