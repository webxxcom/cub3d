/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:50 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 17:05:24 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

__attribute__((noreturn))
void	exit_game(char *error, t_game *game)
{
	game_cleanup(game);
	if (error)
	{
		if (errno)
			printf("%s: %s\n", error, strerror(errno));
		else
			printf("%s\n", error);
	}
	exit(1);
}
