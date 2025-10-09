/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:53:22 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 10:53:42 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_vector_2d_float	t_vec2f;
typedef struct s_vector_2d_int		t_vec2i;

t_vec2f	vec2f_init(void);
t_vec2f	vec2f_construct(float x, float y);

t_vec2i	vec2i_init(void);
t_vec2i	vec2i_construct(int x, int y);
