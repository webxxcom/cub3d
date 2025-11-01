/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:44:53 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/01 22:06:37 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline void	put_ui_text(t_game *g, char *text, uint32_t color)
{
	int32_t const	text_y = g->h - 200;
	int32_t const	char_w = 8;
	int32_t			text_x;

	if (!text || !*text)
		return ;
	text_x = (g->w - ft_strlen(text) * char_w) / 2;
	mlx_string_put(g->mlx, g->win, text_x, text_y, color, text);
}
