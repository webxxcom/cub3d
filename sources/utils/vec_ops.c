/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:46:53 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 11:54:12 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	vec2f_translate(t_vec2f *const vec2f, float const dx, float const dy)
{
    if (!vec2f)
        return ;
    vec2f->x += dx;
    vec2f->y += dy;
}
