/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:16:53 by phutran           #+#    #+#             */
/*   Updated: 2025/09/25 15:35:39 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3D_H
# define cub3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>

# include "libft.h"
# include "mlx.h"
# include "parse.h"
# include "render.h"
# include "error.h"

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
}			t_textures;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}			t_paths;

typedef	struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_point		player;
	t_paths		paths;
	t_textures	textures;
}				t_game;

// Game
void	start_game(t_game *game, const char *filename);
void	exit_game(char *error, t_game *game);

// Parse

#endif