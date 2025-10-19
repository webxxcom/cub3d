/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:21:35 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/19 16:21:33 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

typedef enum e_textures_names
{
	TEXTR_GRAY_BRICKWALL_NORTH = 0,
	TEXTR_GRAY_BRICKWALL_SHADOWED_SOUTH,
	TEXTR_GRAY_BRICKWALL_EAST,
	TEXTR_GRAY_BRICKWALL_SHADOWED_WEST,
	TEXTR_HITLER_PICT,
	TEXTR_HITLER_PICT_SHDWD,
	TEXTR_NAZI_EAGLE_PICT,
	TEXTR_NAZI_EAGLE_PICT_SHDWD,
	TEXTR_CEILING_ANGLES6,
	TEXTR_FLOOR_CHESSED,
	TEXTR_OFFICE_BEIGE_FLAG_NAZI,
	TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_HITLER,
	TEXTR_OFFICE_BEIGE_FLAG_MILITARY,
	TEXTR_OFFICE_BEIGE_WALL_PLAIN,
	TEXTR_OFFICE_BEIGE_ARCHWAY,
	TEXTR_OFFICE_BEIGE_WALL_LAMP,
	TEXTR_OFFICE_BEIGE_WALL_WINDOW_LARGE_CURTAIN,
	TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_LENIN,
	TEXTR_OFFICE_BEIGE_WALL_PORTRAIT_STALIN,
	
	TEXTR_LAB_METAL_GREY_TILES,
	TEXTR_LAB_METAL_GREY_TILES_BLOOD1,
	TEXTR_LAB_METAL_GREY_TILES_BLOOD2,
	TEXTR_LAB_METAL_GREY_TILES_BLOOD3,
	TEXTR_LAB_METAL_GREY_TILES_BLOOD4,
	TEXTR_LAB_METAL_GREY_TILES_CLOCK,
	TEXTR_LAB_METAL_SIGN_RADIATION,
	TEXTR_LAB_METAL_LIGHT_ON,
	
	TEXTR_OFFICE_BEIGE_FLAG_BRITAIN,
	TEXTR_OFFICE_BEIGE_FLAG_JAPAN,
	TEXTR_OFFICE_BEIGE_FLAG_SOVIET,
	TEXTR_OFFICE_BEIGE_WALL_MAP,
	TEXTR_NUMBER
}	t_textures;

#endif