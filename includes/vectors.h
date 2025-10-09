/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:44:27 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/09 11:54:20 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_vector_2d_float
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vector_2d_int
{
	int	x;
	int	y;
}	t_vec2i;

/**
 * Mathematics transaltion of the vector.
 * Depicted as res = (left.x + dx, left.y + dy)
 */
void	vec2f_translate(t_vec2f *const vec2f, float const dx, float const dy);
