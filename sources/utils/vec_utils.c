/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:51:01 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 23:37:13 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2f	vec2f_init(void)
{
	return ((t_vec2f){.x = 0, .y = 0});
}

t_vec2i	vec2i_init(void)
{
	return ((t_vec2i){.x = 0, .y = 0});
}

t_vec2f	vec2f_construct(float x, float y)
{
	return ((t_vec2f){.x = x, .y = y});
}

t_vec2i	vec2i_construct(int x, int y)
{
	return ((t_vec2i){.x = x, .y = y});
}
