/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:19:10 by webxxcom          #+#    #+#             */
/*   Updated: 2025/11/02 17:14:29 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include "cub3D.h"

uint64_t	get_time_in_ms(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL);
}

void	process_dtime(t_game *const game)
{
	const uint64_t	t = get_time_in_ms();

	game->dtime = (t - game->last_time) / 1000.;
	game->last_time = t;
}
