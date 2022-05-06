/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 10:16:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 15:13:22 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include "unistd.h"
# include <math.h>
# include "sprites.h"
# include <stdio.h>

# define SCREEN_HEIGHT	480
# define SCREEN_WIDTH	720
# define MOVE_SPEED		5
# define ROTATE_SPEED	4
# define FOV			70
# define RENDER_DIST_S	150
# define RENDER_DIST_W	50

# define VIEW_LINE_COLOUR 0xD7FFFFFF
# define WALL_COLOUR 0xD8D8FCFF
# define BORDER_COLOR	4282400768

//FIXED VALUES DONT CHANGE
# define MINIMAP_WIDTH		61
# define MINIMAP_HEIGHT		31
# define SCORE_DIGIT_0_POS	55
# define SCORE_DIGIT_1_POS	63
# define SCORE_DIGIT_2_POS	71
# define SCORE_DIGIT_3_POS	79
# define SCORE_DIGIT_4_POS	87
# define LEVEL_DIGIT_POS	24
# define LIVES_DIGIT_POS	112
# define HEALTH_DIGIT_0_POS	168
# define HEALTH_DIGIT_1_POS	176
# define HEALTH_DIGIT_2_POS	184
# define AMMO_DIGIT_0_POS	216
# define AMMO_DIGIT_1_POS	224
# define FACES_POS			134
# define MINIMAP_POS		71

typedef struct s_player
{
	int		health;
	int		score;
	int		ammo;
	int		weapon;
	int		lives;
}			t_player;

/**
 * @brief Struct for all the mlx data
 * 
 * @param mlx_handle mlx handle for the window and everything to do with mlx
 * @param bg background image (used for floor and ceiling)
 * @param fg foreground image (used for drawing the walls)
 * @param texture the mlx texture data.
 */
typedef struct s_mlx
{
	mlx_t			*mlx_handle;
	mlx_image_t		*bg;
	mlx_image_t		*fg;
	mlx_image_t		*hud;
	mlx_image_t		*minimap;
	t_lodtex		tex;
	mlx_texture_t	*numbers;
	mlx_texture_t	*faces;
	mlx_texture_t	*hud_texture;
	double			minimap_scale;
	double			hud_scale;
	int				minimap_zoom;

}			t_mlx;

/**
 * @brief Struct for all the level data
 * 
 * @param map stores the map. (without the texture path and colour data) [x][y]
 * @param map_w total width of the map
 * @param map_h total height of the map
 * @param texture_path string of the path where texture is stored.
 * @param color color for the floor or ceiling stored in RGBA format.
 * 
 */
typedef struct s_level
{
	char			**unparsed;
	char			**map;
	int				**doors;
	int				door_count;
	int				map_w;
	int				map_h;
	t_tex_path		paths;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	unsigned int	number_of_sprites;
	unsigned int	level_number;
}	t_level;

/**
 * Struct for the camera of the player.
 * @param pos camera position.
 * @param dir direction camera points to.
 * @param plane plane of camera.
 */
typedef struct s_camera
{
	t_vector_double	pos;
	t_vector_double	dir;
	t_vector_double	plane;
	int				pitch;
}			t_camera;

typedef struct s_floor_raycaster
{
	t_vector_double	ray_dir0;
	t_vector_double	ray_dir1;
	t_vector_double	pos_d;
	t_vector_int	pos_int;
	t_vector_int	tex;
	t_vector_double	step;
	int				pos_y;
	double			pos_z;
	double			row_dist;
	double			inverse_width;
	int				halve_height;
	int				halve_width;
	int				width4;
	int				x4;
	int				color_pos;
}			t_floor_raycaster;

/**
 * Struct for the raycaster
 * @param hit if the raycaster has hit something.
 * @param map_pos where in the map the raycaster is. Uses camera pos.
 * @param ray_dir direction of the ray. depended on dir camera and plane camera.
 * @param side_dist length of ray from current position to next side.
 * @param delta_dist length of ray from one side to next side 
 * (x side to next x side or y side to next y side)
 * @param perp_wall_dist perpendicular distance to side.
 * @param step direction to step in (+1 or -1) for the ray.
 * @param side what side of the wall was hit (north west south or east).
 */
typedef struct s_raycaster
{
	bool			hit;
	bool			framedone;
	t_vector_int	map_pos;
	t_vector_double	ray_pos;
	t_vector_double	ray_dir;
	t_vector_double	side_dist;
	t_vector_double	delta_dist;
	double			perp_wall_dist;
	t_vector_int	step;
	int				side;
	int				line_height;
	double			wall_x;
	double			camera_x;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			tex_y;
	int				ray_dist;
}			t_raycaster;

typedef struct s_config_data
{
	char			*key;
	char			value;
	int				kind;
	t_vector_int	transp_begin;
	t_vector_int	transp_end;
}			t_config_data;

typedef struct s_config
{
	int				size;
	t_config_data	*dat;
}			t_config;

typedef struct s_hud
{
	t_vector_int	pos_hud;
	int				max_height;
	int				max_width;
	double			inv_scale;
	int				scale;
	int				max_size_faces;
	int				max_size_numbers;
	int				face_pos_x;
	int				border_width;
	t_vector_int	pos_map;
}	t_hud;

enum e_doors
{
	DOOR_CLOSED = 1,
	DOOR_OPENING = 2,
	DOOR_OPEN = 3,
	HIDDEN_CLOSED = 4,
	HIDDEN_OPENING = 5,
	HIDDEN_OPEN = 6,
	HIDDEN_2_CLOSED = 7,
	HIDDEN_2_OPENING = 8,
	HIDDEN_2_OPEN = 9
};

/**
 * @brief Main struct for cubed
 * 
 * @param player player struct with player pos. 
 * (and maybe later extra stuff like hp).
 * 
 */
typedef struct s_data
{
	t_mlx				mlx;
	t_level				level;
	t_camera			cam;
	t_raycaster			caster;
	t_floor_raycaster	floor;
	t_sprite_raycaster	spr_cast;
	t_sprite			*sprite;
	t_sprite_lst		*sprite_lst;
	bool				bonus;
	int					number_of_textures;
	t_player			player;
	bool				update_hud;
	t_config			config;
	bool				floor_ceiling;
	uint32_t			delay;
	uint32_t			color;
	t_hud				hud;
}				t_data;

/**
 * @brief function to parse the input and then the map data.
 * Populates the data.level and data.player structs
 * 
 * @param argv 
 * @param data the function will store its result in the data struct
 * @return true if everything is correct.
 * @return false 
 */
bool	parse_input(char **argv, t_data *data);

bool	parse_config(t_data *data);

/**
 * @brief does all the error checking for the map
 * 
 * @param upmap unparsed map
 * @param data
 * @return char** 
 */
char	**parse_map(char **upmap, t_data *data);

bool	check_needed_textures_loaded(t_data *data);

/**
 * @brief function to init the mlx handle and load all the textures
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool	init_mlx(t_data *data);

bool	init_door_map(t_data *data);

void	set_door_map(t_data *data);

bool	is_nearby_door(t_data *data);
bool	is_door_open(t_data *data, int y, int x);

/**
 * @brief Main function to handle the raycasting part for cubed
 * 
 * @param data 
 */
void	raycaster(t_data *data);

void	check_wall_collision(t_data *data);
void	set_caster_variables(t_data *data, int x);
void	set_step_direction(t_data *data);
void	calculate_perpendicular_wall_distance(t_data *data);
void	set_draw_values(t_data *data);

/**
 * @brief Simple function that fills half the screen with the ceiling color
 * and the other half with the floor color.
 * 
 * @param data 
 */
void	draw_background(t_data *data);

void	draw_floor_ceiling(t_data *data, int x);

void	draw_walls(t_data *data);

void	draw_transparency(t_data *data, int x);

void	draw_sprites(t_data *data);

void	draw_hud(t_data *data);
void	draw_single_nbr(t_data *data, int nbr, int x_pos);
void	draw_numbers(t_data *data);
void	draw_faces(t_data *data);
void	draw_minimap(t_data *data);

//draws a square, specifically for the minimap
bool	draw_square(t_data *data, t_vector_int rec, \
t_vector_int wh, unsigned int c);

/**
 * @brief This is the function where all the drawcalls and movement is called
 * 
 * @param data 
 */
void	game_loop(void *data);

/**
 * @brief leftkey / rightkey movement
 * 
 * @param data 
 * @param dir 
 */
void	change_camera_angle(t_data *data, double dir);

/**
 * @brief wasd movement
 * 
 * @param data 
 * @param dir 
 * @param strafe 
 */
void	move_camera_pos(t_data *data, int dir, bool strafe);

void	key_handler(struct mlx_key_data keys, void *param);
void	mouse_events(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param);
void	cursor_movement(double xpos, double ypos, void *param);

// utility functions //

char	**readmap(int fd, char **temp);

bool	mapjmptable(char *line, t_data *data);
bool	checkmap(char *map);
bool	sprite_check(char c);
bool	playerposcheck(char c);
bool	checktypes(t_data *data);
bool	validchar(char c);
bool	validchar_space(char c);
bool	is_player_tile(char c);
bool	is_sprite_tile(char c);
bool	is_wall_tile(char c);
bool	is_empty_tile(char c);
bool	is_door_tile(char c);
bool	is_finish_tile(char c);
bool	is_nonblocking_kind(int kind);
bool	verifyzero(char **upmap, int i, int j, t_data *data);

int		get_sprite_kind(char c, t_data *data);

void	store_path(char *line, t_data *data, int kind);
void	color_store(char *line, t_data *data, int kind);

typedef void	(*t_func)(char *line, t_data *data, int kind);

void	set_sprite_positions(char **map, t_data *data);
void	sort_sprites(t_data *data, t_sprite_lst **begin);
void	init_hud(t_data *data);

#endif