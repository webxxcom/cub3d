/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:20:26 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/18 00:30:36 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

#include "cub3D.h"

typedef enum e_door_states
{
	CLOSED,
	CLOSING,
	OPEN,
	OPENING
}	t_door_states;

typedef struct s_entity
{
	char		type;
	t_vec2i		pos;
	int32_t		state;
	t_animation	*anim;
	
	void	(*interact)(t_game *const,struct s_entity *);
	void	(*update)(t_game *const, struct s_entity *);
}	t_entity;

void	door_update(t_game *const g, t_entity *door);
void	door_interact(t_game *const g, t_entity *door);


#endif