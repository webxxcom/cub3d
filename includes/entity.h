/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:20:26 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:21:09 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "cub3D.h"

typedef enum e_door_states
{
	CLOSED,
	CLOSING,
	OPEN,
	OPENING
}				t_door_states;

typedef struct s_entity
{
	char		type;
	t_vec2i		pos;
	int32_t		state;
	t_animation	*anim;

	void		(*interact)(t_game *const, struct s_entity *);
	void		(*update)(t_game *const, struct s_entity *);
}				t_entity;

#endif