/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:16:53 by phutran           #+#    #+#             */
/*   Updated: 2025/09/24 15:10:39 by phutran          ###   ########.fr       */
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

typedef	struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
}			t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_point		player;
	t_textures	*textures;
}				t_game;

// Game
void	start_game(t_game *game, const char *filename);
void	exit_game(char *error, t_game *game);

// Parse

#endif