/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:44:27 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/10 10:25:15 by webxxcom         ###   ########.fr       */
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
t_vec2f	vec2f_translate(t_vec2f const vec2f, float const dx, float const dy);

/**
 * Mathematics transaltion of the vector to the vector right.
 * Depicted as res = (left.x + right.x, left.y + right.y)
 */
t_vec2f	vec2f_vtranslate(t_vec2f const left, t_vec2f const right);

/**
 * Return the normalized vector from the parameter by dividing each axis by magnitude
 */
t_vec2f	vec2f_normalize(t_vec2f const vec2f);

/**
 * Negate vector vec2f taking it's coordinates as (-x, -y);
 */
t_vec2f	vec2f_neg(t_vec2f const vec2f);
