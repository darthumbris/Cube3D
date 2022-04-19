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

uint8_t	*get_texture(t_data *data)
{
	if (data->caster.side == NORTH)
		return (data->mlx.no_texture->pixels);
	else if (data->caster.side == WEST)
		return (data->mlx.we_texture->pixels);
	else if (data->caster.side == EAST)
		return (data->mlx.ea_texture->pixels);
	return (data->mlx.so_texture->pixels);
}

void	draw_walls(t_data *data, int x)
{
	double			step;
	double			tex_pos;
	int				y;
	uint8_t			*pixels;
	uint8_t			*dst;

	data->caster.tex.x = (int)(data->caster.wall_x * (double)(TEXTURE_WIDTH));
	if ((data->caster.side < NORTH && data->caster.ray_dir.x > 0) || \
		(data->caster.side > EAST && data->caster.ray_dir.y < 0))
		data->caster.tex.x = TEXTURE_WIDTH - data->caster.tex.x - 1;
	step = 1.0 * TEXTURE_HEIGHT / data->caster.line_height;
	tex_pos = (data->caster.draw_start - data->mlx.mlx_handle->height / 2 + \
		data->caster.line_height / 2) * step;
	y = data->caster.draw_start;
	pixels = get_texture(data);
	dst = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y <= data->caster.draw_end)
	{
		*(unsigned int *)dst = (*(int *)(pixels + \
			(data->caster.tex.y * TEXTURE_WIDTH + data->caster.tex.x) * 4));
		dst += data->mlx.mlx_handle->width * 4;
		data->caster.tex.y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		y++;
	}
}
