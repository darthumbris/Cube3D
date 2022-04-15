#include "cubed.h"

static bool	init_textures(t_data *data)
{
	data->mlx.no_texture = mlx_load_png(data->level.no_texture_path);
	data->mlx.ea_texture = mlx_load_png(data->level.ea_texture_path);
	data->mlx.so_texture = mlx_load_png(data->level.so_texture_path);
	data->mlx.we_texture = mlx_load_png(data->level.we_texture_path);
	if (data->mlx.no_texture == NULL || data->mlx.ea_texture == NULL || \
		data->mlx.so_texture == NULL || data->mlx.we_texture == NULL)
		return (false);
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
	ft_bzero(data->keyque, 6);
	return (true);
}

bool	init_mlx(t_data *data)
{
	data->mlx.mlx_handle = mlx_init
		(SCREEN_WIDTH, SCREEN_HEIGHT, "cube3D", false);
	if (data->mlx.mlx_handle == NULL)
		return (false);
	data->mlx.bg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.bg == NULL)
		return (false);
	data->mlx.fg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.fg == NULL)
		return (false);
	return (init_textures(data));
}
