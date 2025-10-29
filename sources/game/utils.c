/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:48:47 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/29 10:54:00 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline t_image	*animation_get_current_image(t_animation *anim)
{
	return (anim->frames[anim->curr_frame_n]->image);
}

t_decoration	*find_decoration_at(t_game *const g, t_vec2i pos)
{
	t_decoration	*tmp;
	size_t			i;

	i = 0;
	while (i < array_size(&g->map.decorations))
	{
		tmp = array_get(&g->map.decorations, i);
		if (vec2i_equals(tmp->pos, pos))
			return (tmp);
		++i;
	}
	return (NULL);
}
