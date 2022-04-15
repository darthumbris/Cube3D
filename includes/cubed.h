/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:25:55 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/15 12:15:51 by shoogenb      ########   odam.nl         */
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

# define SCREEN_HEIGHT	720
# define SCREEN_WIDTH	1280
# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64
# define MOVE_SPEED		5
# define ROTATE_SPEED	20
# define FOV			90
# define TRANSPARENT	0x00000000

typedef struct s_vector_uint
{
	unsigned int	x;
	unsigned int	y;
}				t_vector_uint;

typedef struct s_vector_double
{
	double	x;
	double	y;
}				t_vector_double;

/* 
 * Player position useful for collision checking and
 * maybe for enemies etc.
 */
typedef struct s_player
{
	t_vector_double	pos;
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
	mlx_texture_t	*no_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*ea_texture;
}			t_mlx;

typedef enum e_textures
{
	WEST = 0,
	EAST = 1,
	NORTH = 2,
	SOUTH = 3
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
	t_vector_uint	map_pos;
	t_vector_double	ray_pos;
	t_vector_double	ray_dir;
	t_vector_double	side_dist;
	t_vector_double	delta_dist;
	double			perp_wall_dist;
	t_vector_uint	step;
	int				side;
	int				line_height;
	double			wall_x;
	double			camera_x;
	int				draw_start;
	int				draw_end;
	t_vector_uint	tex;
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
	t_mlx			mlx;
	t_level			level;
	t_camera		cam;
	t_player		player;
	t_raycaster		caster;
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

void	draw_walls(t_data *data, int x);

/**
 * @brief This is the function where all the drawcalls and movement is called
 * 
 * @param data 
 */
void	game_loop(void *data);

void	key_handler(struct mlx_key_data keys, void *param);

// utility functions //

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