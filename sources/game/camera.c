/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkravche <rkravche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:48:47 by rkravche          #+#    #+#             */
/*   Updated: 2026/02/06 15:20:37 by rkravche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

inline float	cam_get_pitch(t_cam *cam)
{
	float const	bob_amplitude_y = 10.0f;
	float const	pitch_offset = sinf(cam->bob_phase) * bob_amplitude_y;

	return (cam->pitch + pitch_offset);
}

inline void	cam_process_bob(t_cam *cam, float player_speed, float dtime)
{
	if (cam->bob_phase > 3.14f)
		cam->bob_phase = -cam->bob_phase;
	if (dtime > 0.1f)
		dtime = 0.1f;
	cam->bob_phase += player_speed * dtime * 2.f;
}
