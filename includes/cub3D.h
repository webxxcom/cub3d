/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:16:53 by phutran           #+#    #+#             */
/*   Updated: 2025/10/09 12:45:51 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>
# include <X11/X.h>

# include "libft.h"
# include "mlx.h"
# include "parse.h"
# include "render.h"
# include "error.h"
# include "utils.h"
# include "key_codes.h"
# include "image.h"
# include "vectors.h"

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
}	t_textures;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_paths;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_view
{
	t_vec2f		plane;
	t_vec2f		dir;
	float 		rotateSpeed;
}	t_view;

typedef struct	s_player
{
	t_vec2f	pos;
	double speed;
}	t_player;

typedef struct s_game
{
	int			w;
	int			h;
	void		*mlx;
	void		*win;
	char		**map;
	t_player	player;
	t_paths		paths;
	t_textures	textures;
	t_view		cam;
	t_list		*pressedKeys;
	t_image		*buffer_image;

	double		dtime;
	double		lastTime;
}	t_game;

// Delta time
uint64_t	get_time_in_ms(void);
void		process_dtime(t_game *const game);

// Keys
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

// Game
void	start_game(t_game *game, const char *filename);
void	exit_game(char *error, t_game *game);

// Hooks
int		close_window(void *mlx);
int		main_loop(t_game *game);
void	keyboard_handle(t_game *const game);

// Parse

#endif