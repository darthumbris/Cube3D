#include "cubed.h"

void	draw_background(t_data *data)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
			mlx_put_pixel(data->mlx.bg, x, y, data->level.ceiling_color);
		for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
			mlx_put_pixel(data->mlx.bg, x, y, data->level.floor_color);
	}
}