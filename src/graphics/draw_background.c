#include "cubed.h"

unsigned int	get_pixel(mlx_texture_t *data, int x, int y)
{
	return (*(unsigned int*)\
		(data->pixels + ((y * data->width + x) * (data->bytes_per_pixel))));
}

void draw_skybox(t_data *data)
{
	t_vector_uint p;
	t_vector_uint of;
	mlx_texture_t *temp;

	temp = mlx_load_png("assets/stars.png");
	p.x = -1;
	while (++p.x < SCREEN_WIDTH)
	{
		p.y = -1;
		of.x = ((double)p.x / SCREEN_HEIGHT / 2) * temp->width;
		while (++p.y < SCREEN_HEIGHT)
		{
			of.y = ((double)p.y / SCREEN_HEIGHT / 2) * temp->height;
			mlx_put_pixel(data->mlx.bg, p.x, p.y, get_pixel(temp, of.x, of.y));
		}
	}
}


void	draw_background(t_data *data)
{
	draw_skybox(data);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		//for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
		//	mlx_put_pixel(data->mlx.bg, x, y, data->level.ceiling_color);
		for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
			mlx_put_pixel(data->mlx.bg, x, y, data->level.floor_color);
	}
}

