/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:50 by phutran           #+#    #+#             */
/*   Updated: 2025/10/15 20:37:54 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	cleanup_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
void	exit_game(char *error, t_game *game)
{
	cleanup_game(game);
	if (error)
	{
		printf("Error\n");
		if (errno)
			printf("%s: %s\n", error, strerror(errno));
		else
			printf("%s\n", error);
		exit(1);
	}
	exit(0);
}
