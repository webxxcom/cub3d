/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:21:35 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/28 10:39:04 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

typedef enum e_texture_sides
{
	NORTH = 0,
	WEST,
	SOUTH,
	EAST
}	t_txtres_sides;

typedef enum e_textures_names
{
	TEXTR_NORTH,
	TEXTR_WEST,
	TEXTR_SOUTH,
	TEXTR_EAST,
	TEXTR_FLOOR,
	TEXTR_CEILING,
}	t_textures;

#endif