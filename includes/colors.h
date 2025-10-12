/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:12:15 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/12 13:12:43 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/*
** Basic RGB color macros in 0xRRGGBB format
*/

# define COLOR_BLACK        0x000000
# define COLOR_WHITE        0xFFFFFF
# define COLOR_GRAY         0x808080
# define COLOR_LIGHT_GRAY   0xC0C0C0
# define COLOR_DARK_GRAY    0x404040

# define COLOR_RED          0xFF0000
# define COLOR_GREEN        0x00FF00
# define COLOR_BLUE         0x0000FF

# define COLOR_CYAN         0x00FFFF
# define COLOR_MAGENTA      0xFF00FF
# define COLOR_YELLOW       0xFFFF00
# define COLOR_ORANGE       0xFFA500
# define COLOR_PURPLE       0x800080
# define COLOR_PINK         0xFFC0CB
# define COLOR_BROWN        0x8B4513

# define COLOR_SKY_BLUE     0x87CEEB
# define COLOR_SEA_GREEN    0x2E8B57
# define COLOR_GOLD         0xFFD700
# define COLOR_BEIGE        0xF5F5DC
# define COLOR_IVORY        0xFFFFF0
# define COLOR_MAROON       0x800000
# define COLOR_NAVY         0x000080
# define COLOR_OLIVE        0x808000
# define COLOR_TEAL         0x008080

# define RGB(r, g, b)   (((r) << 16) | ((g) << 8) | (b))

#endif
