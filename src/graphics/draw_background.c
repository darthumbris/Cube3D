#include "cubed.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->mlx.mlx_handle->width)
	{
		y = 0;
		while (y < data->mlx.mlx_handle->height / 2)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.ceiling_color);
			y++;
		}
		while (y < data->mlx.mlx_handle->height)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.floor_color);
			y++;
		}
		x++;
	}
}
