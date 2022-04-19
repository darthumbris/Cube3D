#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int			y;
	uint8_t		*dst;

	y = 0;
	dst = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->caster.draw_start)
	{
		*(unsigned int *)dst = 0;
		dst += data->mlx.mlx_handle->width * 4;
		y++;
	}
	y = data->caster.draw_end + 1;
	dst = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->mlx.mlx_handle->height)
	{
		*(unsigned int *)dst = 0;
		dst += data->mlx.mlx_handle->width * 4;
		y++;
	}
}

void	draw_walls(t_data *data, int x)
{
	const int		side = data->caster.side;
	double			step;
	double			tex_pos;
	int				y;
	uint8_t			*pixels;
	uint8_t			*dst;

	data->caster.tex.x = (int)(data->caster.wall_x * (double)(data->mlx.tex.texarr[side]->width - 1));
	if ((data->caster.side < NORTH && data->caster.ray_dir.x > 0) || \
		(data->caster.side > EAST && data->caster.ray_dir.y < 0))
		data->caster.tex.x = data->mlx.tex.texarr[side]->width - data->caster.tex.x - 1;
	step = (data->mlx.tex.texarr[side]->height / (double)data->caster.line_height);
	tex_pos = (data->caster.draw_start - data->mlx.mlx_handle->height / 2 + \
		data->caster.line_height / 2) * step;
	y = data->caster.draw_start;
	pixels = data->mlx.tex.texarr[side]->pixels;
	dst = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->caster.draw_end)
	{
		*(unsigned int *)dst = (*(int *)(pixels + \
			((int)tex_pos * data->mlx.tex.texarr[side]->width + data->caster.tex.x) * 4));
		dst += data->mlx.mlx_handle->width * 4;
		tex_pos += step;
		y++;
	}
}
