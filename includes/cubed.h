#ifndef CUBED_H
# define CUBED_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>

typedef struct s_vector
{
	unsigned int	x;
	unsigned int	y;
}				t_vector;

typedef struct s_player
{
	t_vector	pos;
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
	unsigned int	window_w;
	unsigned int	window_h;
}			t_mlx;

typedef struct s_level
{
	char			**map;
	t_player		player;
	unsigned int	map_w;
	unsigned int	map_h;
}				t_level;

typedef struct s_data
{
	t_mlx			mlx;
	t_level			level;
}				t_data;

#endif