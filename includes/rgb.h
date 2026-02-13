/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:21:14 by webxxcom          #+#    #+#             */
/*   Updated: 2026/02/12 09:38:25 by danslav1e        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RGB_H
# define RGB_H

# include "cub3D.h"

// Color representated as red, green and blue in range [0, 1]
typedef struct s_colorf
{
	float	r;
	float	g;
	float	b;
}			t_colorf;

t_colorf	colorf_from_uint(uint32_t color);
uint32_t	colorf_to_uint(t_colorf colorf);
t_colorf	colorf_from_rgbf(float r, float g, float b);
t_colorf	colorf_init(void);
uint32_t	colorf_from_rgbf_to_uint(float r, float g, float b);

#endif