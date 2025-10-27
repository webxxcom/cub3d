/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:53:48 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/27 17:04:29 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_player	player_init(void)
{
	return ((t_player){
		.speed = 3.f,
		.base_speed = 3.f,
		.sprint_speed = 6.f,
		.radius = 6.f 
	});
}

t_input	init_input(void)
{
	t_input	res;

	ft_memset(&res, 0, sizeof (res));
	res.pressed_keys = array_init(sizeof (int));
	return (res);
}

t_cam	cam_init(void)
{
	return ((t_cam){
		.sensitivity = 0.0008f,
		.pitch = 0,
		.bob_phase = 0
	});
}
//cube = {NORTH, WEST, SOUTH, EAST}
