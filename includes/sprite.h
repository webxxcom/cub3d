/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:48:25 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/17 12:53:33 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_sprite
{
	int		state;
	int		type;
	t_vec2f	pos;
}	t_sprite;

void	draw_sprite(t_game *g, t_sprite *sprite);
