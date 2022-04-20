/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:25:55 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 16:47:50 by shoogenb      ########   odam.nl         */
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

# define SCREEN_HEIGHT	1080
# define SCREEN_WIDTH	1440
# define MOVE_SPEED		5
# define ROTATE_SPEED	4
# define FOV			70
# define RENDER_DIST	5

typedef struct s_vector_double
{
	double	x;
	double	y;
}				t_vector_double;

typedef struct s_vector_int
{
	int	x;
	int	y;
}				t_vector_int;

/* 
 * Player position useful for collision checking and
 * maybe for enemies etc.
 */
typedef struct s_player
{
	t_vector_double	pos;
}			t_player;

typedef union u_lodtex
{
	mlx_texture_t	*texarr[6];
	struct {
		mlx_texture_t	*no_texture;
		mlx_texture_t	*ea_texture;
		mlx_texture_t	*so_texture;
		mlx_texture_t	*we_texture;
		mlx_texture_t	*fl_texture;
		mlx_texture_t	*ce_texture;
	};
}	t_lodtex;

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
	t_lodtex		tex;
}			t_mlx;

typedef enum e_textures
{
	WEST = 0,
	EAST = 1,
	NORTH = 2,
	SOUTH = 3,
	FLOOR = 4,
	CEILING = 5
}	t_textures;

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
	char			**map;
	int				map_w;
	int				map_h;
	char			*no_texture_path;
	char			*we_texture_path;
	char			*so_texture_path;
	char			*ea_texture_path;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
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
	t_player			player;
	t_raycaster			caster;
	t_floor_raycaster	floor;
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

/**
 * @brief does all the error checking for the map
 * 
 * @param upmap unparsed map
 * @param data
 * @return char** 
 */
char	**parse_map(char **upmap, t_data *data);

/**
 * @brief function to init the mlx handle and load all the textures
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool	init_mlx(t_data *data);

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

void	draw_transparency(t_data *data, int x);

void	draw_walls(t_data *data);

void	draw_floor(t_data *data);

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

bool	mapjmptable(char *line, t_data *data);
bool	checkmap(char *map);
char	**readmap(int fd, char **temp);
bool	checktypes(t_data *data);
bool	validchar(char c);
bool	validchar_space(char c);
bool	verifyzero(char **upmap, int i, int j, t_data *data);

/*
	Jump table functions to store values in struct
*/
void	no_store(char *line, t_data *data);
void	so_store(char *line, t_data *data);
void	we_store(char *line, t_data *data);
void	ea_store(char *line, t_data *data);
void	f_store(char *line, t_data *data);
void	c_store(char *line, t_data *data);

typedef void	(*t_func)(char *line, t_data *data);

typedef struct s_values
{
	char	*str;
	t_func	storemapval;
}	t_values;

#endif