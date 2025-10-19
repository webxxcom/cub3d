/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:21:14 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 19:07:19 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

#include "cub3D.h"

typedef struct	s_colorf
{
	float	r;
	float	g;
	float	b;
}	t_colorf;

t_colorf	colorf_from_uint(uint32_t color);
uint32_t	colorf_to_uint(t_colorf colorf);
t_colorf	colorf_from_rgbf(float r, float g, float b);
t_colorf	colorf_init(void);
uint32_t	colorf_from_rgbf_to_uint(float r, float g, float b);

#endif