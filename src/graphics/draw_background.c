#include "cubed.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.ceiling_color);
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.floor_color);
			y++;
		}
		x++;
	}
}
