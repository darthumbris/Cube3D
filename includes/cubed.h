#ifndef CUBED_H
# define CUBED_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>

# define SCREEN_HEIGHT	480
# define SCREEN_WIDTH	640
# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64
# define MOVE_SPEED		5
# define ROTATE_SPEED	3
# define FOV			90

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

typedef struct s_player
{
	t_vector_uint	pos;
}			t_player;

typedef struct s_mlx
{
	mlx_t			*mlx_handle;
	mlx_image_t		*bg;
	mlx_image_t		*fg;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*ea_texture;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}			t_mlx;

typedef struct s_level
{
	char			**map;
	t_player		player;
	unsigned int	map_w;
	unsigned int	map_h;
}				t_level;

typedef struct s_camera
{
	t_vector_double	pos;
	t_vector_double	dir;
	t_vector_double	plane;
}			t_camera;

typedef struct s_data
{
	t_mlx			mlx;
	t_level			level;
	t_camera		cam;
}				t_data;

#endif