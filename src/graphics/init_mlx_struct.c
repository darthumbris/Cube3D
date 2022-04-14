#include "cubed.h"
#include <string.h>

const char	*g_map[15] = {
	"000000001111111111111111111111111",
	"000000001000000000110000000000001",
	"000000001011000001110000000000001",
	"000000001001000000000000000000001",
	"111111111011000001110000000000001",
	"100000000011000001110111111111111",
	"111101111111110111000000100010000",
	"111101111111110111010100100010000",
	"110000001101010111000000100010000",
	"100000000000000011000000100010000",
	"100000000000000011010100100010000",
	"110000011101010111110111100011100",
	"111101110111010101011110100010000",
	"111111110111111101111111111110000",
	NULL};

static bool	init_textures(t_data *data)
{
	data->mlx.no_texture = mlx_load_png("assets/greystone.png");
	if (data->mlx.no_texture == NULL)
		return (false);
	data->mlx.ea_texture = mlx_load_png("assets/redbrick.png");
	data->mlx.so_texture = mlx_load_png("assets/greystone.png");
	data->mlx.we_texture = mlx_load_png("assets/purplestone.png");
	data->level.ceiling_color = 0xE11E00FF;
	data->level.floor_color = 0xDC6400FF;
	data->level.map = malloc(sizeof(char *) * 15);
	for (int i = 0; i < 13; i++)
		data->level.map[i] = strdup(g_map[i]);
	data->level.map[14] = NULL;
	data->player.pos.x = 4.0;
	data->player.pos.y = 10.0;
	data->level.map_h = 14;
	data->level.map_w = 34;
	data->cam.pos.x = 4;
	data->cam.pos.y = 10;
	data->cam.dir.x = -1.0;
	data->cam.dir.y = 0;
	data->cam.plane.x = 0.0;
	data->cam.plane.y = 0.66;
	data->caster.map_pos.x = 4;
	data->caster.map_pos.y = 10;
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
