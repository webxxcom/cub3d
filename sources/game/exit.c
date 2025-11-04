/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:08:50 by phutran           #+#    #+#             */
/*   Updated: 2025/11/04 14:57:36 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_game(char *error, t_game *game, char **map)
{
	if (map)
		ft_free_matrix(map);
	game_cleanup(game);
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
