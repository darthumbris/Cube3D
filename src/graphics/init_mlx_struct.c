#include "cubed.h"

static bool	init_textures(t_data *data)
{
	data->mlx.tex[NORTH] = mlx_load_png(data->level.no_texture_path);
	data->mlx.tex[EAST] = mlx_load_png(data->level.ea_texture_path);
	data->mlx.tex[SOUTH] = mlx_load_png(data->level.so_texture_path);
	data->mlx.tex[WEST] = mlx_load_png(data->level.we_texture_path);
	if (data->mlx.tex[NORTH] == NULL || data->mlx.tex[EAST] == NULL || \
		data->mlx.tex[SOUTH] == NULL || data->mlx.tex[WEST] == NULL)
		return (false);
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
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
