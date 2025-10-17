/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:59:07 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/17 13:08:49 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_sprite	*init_sprites(t_game *g)
{
	t_sprite *const	sp = ft_calloc(1, sizeof (t_sprite));

	(void)g;
	if (!sp)
		return (NULL);
	sp[0] = (t_sprite){.pos = vec2f_construct(1.5, 2)};
	return (sp);
}