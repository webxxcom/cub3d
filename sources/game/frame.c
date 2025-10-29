/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:52:23 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/29 10:47:17 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	frame_clean(void *mlx, t_frame *frame)
{
	im_cleanup(mlx, frame->image);
	freenull(&frame);
}
