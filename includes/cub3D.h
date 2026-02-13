/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danslav1e <danslav1e@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:16:53 by phutran           #+#    #+#             */
/*   Updated: 2026/02/12 11:49:40 by danslav1e        ###   ########.fr       */
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

# include "mlx.h"
# include "libft.h"
# include "array.h"
# include "parse.h"
# include "animation.h"
# include "colors.h"
# include "error.h"
# include "frame.h"
# include "rgb.h"
# include "image.h"
# include "key_codes.h"
# include "textures.h"
# include "vectors.h"
# include "sprite.h"
# include "raycaster.h"
# include "render.h"
# include "entity.h"
# include "decorations.h"
# include "sprite.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define FLOAT_EPSILON 1e-8

# define TILE_SIZE 64
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 650
# define CAMERA_FOV 0.66f

// Define possible player's movement to avoid faster diagonal movement
# define MOVING_FRWD 0
# define MOVING_BCK 1
# define MOVING_LFT 2
# define MOVING_RGHT 3

typedef struct s_paths
{
	char					*north;
	char					*south;
	char					*east;
	char					*west;
	char					*floor;
	char					*ceiling;
}							t_paths;

typedef struct s_camera
{
	t_vec2f					pos;
	t_vec2f					plane;
	t_vec2f					dir;
	float					sensitivity;
	float					pitch;
	float					bob_phase;
}							t_cam;

typedef struct s_player
{
	t_vec2f					pos;
	t_vec2f					plane;
	t_vec2f					dir;
	float					speed;
	float					base_speed;
	float					sprint_speed;
	float					radius;
}							t_player;

/**
 * Minimap's pos is the placement of minimap's bottom-left corner
 */
typedef struct s_minimap
{
	t_vec2i					pos;
	t_vec2i					size;
	uint32_t				bgcol;
	uint32_t				pcol;
	uint32_t				wcol;
	uint32_t				rcol;
	uint32_t				fcol;
	uint32_t				dcol;
}							t_minimap;

typedef enum e_tile_type
{
	TILE_VOID = ' ',
	TILE_WALL = '1',
	TILE_FLOOR = '0',
	TILE_DOOR = 'D',
	TILE_PLAYER_N = 'N',
	TILE_PLAYER_S = 'S',
	TILE_PLAYER_E = 'E',
	TILE_PLAYER_W = 'W',
}							t_tile_type;

typedef struct s_tile
{
	t_decoration			*sides[4];
	t_tile_type				type;
	t_vec2i					pos;
}							t_tile;

typedef struct s_map
{
	t_tile					**tiles;
	t_array					decorations;
	t_vec2i					size;
}							t_map;
void						door_update(t_game *const g, t_decoration *door);
void						door_interact(t_game *const g, t_decoration *door);
void						light_interact(t_game *const g,
								t_decoration *light);
void						anim_def_update(t_game *const g,
								t_decoration *light);
void						sprite_update_anim(t_game *const g, t_sprite *self);

/**
 * The input structure which describes current keyboard input.
 * 	To revised: mouse keys.
 *
 * Field descriptions:
 *  ::pressed_keys - a list of currently pressed keys
 * which can hold any key until it's a movement key or a key that should repeat.
 * 	::moving_keys - the static array of currently allowed pressed movement keys.
 * required to improve optimization of the diagonal movement calculations.
 */
typedef struct s_input
{
	t_array					pressed_keys;
	bool					moving_keys[4];
}							t_input;

typedef struct s_dda_ray	t_dda_ray;

/**
 * The struct s_game describes global game's state.
 *
 * Field descriptions:
 *  ::map 		- an instance of the map downloaded from the file.
 *  ::player 	- an instance of an entity moveable by keyboard.
 *  ::minimap 	- an instance of the minimap structure which
 * 					has setting for minimap display on ther screen.
 *  ::paths 	- paths to files which store textures to each cardinal direction.
 * 	::cubes 	- all the possible combinations of textures
 * 					on the cube fo each cardinal direction.
 *  ::cam		- current game's POV.
 *  ::input		- describes currently allowed pressed keys
 *  ::buffer_image - describes the current frame to be drawn on the screen.
 * All the minimap's, map's, enemy's etc. pixels are moved to that image
 *  and then this image is to be put on the mlx display.
 *  ::w			- window width
 *  ::h			- window height
 *  ::dtime		- delta time between two frames
 *  ::show_dbg	- debug information triggered on F1
 */
typedef struct s_camera_curve
{
	t_vec2f					p0;
	t_vec2f					p1;
	t_vec2f					p2;
}							t_camera_curve;

typedef struct s_cutscene
{
	float					speed;
	double					dtime;
	bool					is_going;
	float					lerp_t;
	t_camera_curve			curve;
}							t_cutscene;

typedef enum e_game_state
{
	GAME_STATE_CUTSCENE = 1,
	GAME_STATE_ON
}							t_game_state;

typedef struct s_game
{
	void					*mlx;
	void					*win;
	int						w;
	int						h;
	bool					show_dbg;
	bool					show_keys;
	double					dtime;
	uint64_t				last_time;
	t_game_state			state;
	t_array					cutscenes;
	t_array					sprites;
	t_array					lights;
	float					*z_buffer;

	t_map					map;
	t_player				player;
	t_minimap				minimap;
	t_paths					paths;
	t_cam					cam;
	t_input					input;
	t_image					*buffer_image;
	t_dda_ray				*rays;

	t_image					**textures;

	t_image					*ceiling;
	t_image					*floor;
}							t_game;

t_decoration				*find_decoration_at(t_game *const g, t_vec2i pos);
t_sprite					*find_sprite_at(t_game *const g, t_vec2f pos);
float						cam_get_pitch(t_cam *cam);
void						cam_process_bob(t_cam *cam, float player_speed,
								float dtime);
void						load_decorations(t_game *g);
void						load_sprites(t_game *g);
t_colorf					get_light_bonus(t_game *g, float base_shade,
								t_vec2f obs_pos);
void						cam_rotate(t_game *const g, const float dx,
								float const dy);
t_vec2f						cam_get_plane_vec(t_vec2f dir_vec);
void						cutscene_update(t_game *g, t_cutscene *cs);
void						update_animations(t_game *g);
void						update(t_game *g);

// Inits
void						cutscenes_init(t_game *g);
t_input						input_init(void);
t_player					player_init(void);
t_cam						cam_init(void);
t_minimap					minimap_init(t_game *g);

// Delta time
uint64_t					get_time_in_ms(void);
void						process_dtime(t_game *const game);

// Handles
void						handle_movement(t_game *const g);

// Hooks
int							close_window_hook(void *mlx);
int							main_loop(t_game *game);
void						repetition_handle(t_game *const game);
int							key_press_hook(int key, t_game *game);
int							key_release_hook(int key, t_game *game);
int							mouse_move_hook(int x, int y, t_game *game);
void						process_mvkeys(t_game *const g, int key,
								bool pressed);
void						process_keypress(t_game *const game, int key);

// Game
void						start_game(t_game *game, const char *filename);
void						exit_game(char *error, t_game *game);
void						game_cleanup(t_game *game);

// Cleanups
void						game_cleanup(t_game *game);
void						decoration_cleanup(void *mlx, void *decor);
void						map_cleanup(void *mlx, t_map *m);
void						textures_cleanup(t_game *g);
void						paths_cleanup(t_game *g);
void						sprites_cleanup(t_game *g, t_array *sprites);

// Utils
void						freenull(void *p);
void						toggle_bool(bool *flag);
bool						key_should_repeat(int key);
bool						movement_key(int key);
bool						line_is_whitespace(char *l);

// Parse
int							parse_direction(char *dir, t_txtres_sides *side);
bool						pos_is_parseable(char *field);

#endif