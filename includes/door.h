/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:21:11 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 22:22:24 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef enum
{
	OPEN,
	OPENING,
	CLOSING,
	CLOSED
}	t_door_states;

typedef struct s_door
{
	t_animation		*anim;
	t_door_states	state;
	t_vec2i			pos;
}	t_door;


