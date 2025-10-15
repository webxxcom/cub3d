/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:51:34 by webxxcom          #+#    #+#             */
/*   Updated: 2025/10/15 21:37:58 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_H
# define FRAME_H

typedef struct s_frame
{
	t_image		*image;
	uint64_t	time;
}	t_frame;

void	frame_clean(void *mlx, t_frame *frame);

#endif
