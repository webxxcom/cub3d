/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:16:53 by phutran           #+#    #+#             */
/*   Updated: 2025/10/11 00:07:50 by webxxcom         ###   ########.fr       */
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

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// Define possible player's movement to avoid faster diagonal movement
# define MOVING_FRWD 0
# define MOVING_BCK 1
# define MOVING_LFT 2
# define MOVING_RGHT 3

// Enumeration for wall sides, sued for textures obviously
typedef enum e_texture_sides
{
	NORTH = 0,
	WEST,
	SOUTH,
	EAST
}	t_txtres_sides;

typedef struct s_cube_textures
{
	t_image	*walls[4];
}	t_cube_txtrs;

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

typedef struct s_camera
{
	t_vec2f		plane;
	t_vec2f		dir;
	float		sensitivity;
	float		pitch;
}	t_cam;

typedef struct s_player
{
	t_vec2f	pos;
	float	speed;
	float	radius;
}	t_player;

/**
 * Minimap's pos is the placement of minimap's bottom-left corner
 */
typedef struct s_minimap
{
	t_vec2i		pos;
	t_vec2i		size;
	uint32_t	bgcol;
	uint32_t	pcol;
	uint32_t	wcol;
	uint32_t	rcol;
	uint32_t	fcol;
}	t_minimap;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	char			**map;
	t_player		player;
	t_minimap		minimap;
	t_paths			paths;
	t_cube_txtrs	cubes[2];
	t_cam			cam;
	t_list			*pressed_keys;
	bool			moving_keys[4];
	t_image			*buffer_image;

	int				w;
	int				h;
	double			dtime;
	double			last_time;
	bool			show_dbg;
}	t_game;

t_minimap   minimap_init(void);
void	put_minimap(t_game *g);

// Delta time
uint64_t	get_time_in_ms(void);
void		process_dtime(t_game *const game);

// Handles
void		handle_movement(t_game *const g);

// Hooks
int			close_window_hook(void *mlx);
int			main_loop(t_game *game);
void		repetition_handle(t_game *const game);
int			key_press_hook(int key, t_game *game);
int			key_release_hook(int key, t_game *game);
int			mouse_move_hook(int x, int y, t_game *game);
void		process_mvkeys(t_game *const g, int key, bool pressed);
void		process_keypress(t_game *const game, int key);

// Game
void		start_game(t_game *game, const char *filename);
void		exit_game(char *error, t_game *game);

// Cleanups
void 		game_cleanup(t_game *game);

// Utils
void		toggle_bool(bool *flag);
bool 		key_should_repeat(int key);
bool		movement_key(int key);

// Parse

#endif