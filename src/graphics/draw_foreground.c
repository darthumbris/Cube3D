#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < data->caster.draw_start)
	{
		mlx_put_pixel(data->mlx.fg, x, y, TRANSPARENT);
		y++;
	}
	y = data->caster.draw_end;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(data->mlx.fg, x, y, TRANSPARENT);
		y++;
	}
}

static unsigned int	get_color(t_data *data, t_vector_uint	tex)
{
	unsigned int	color;
	uint8_t			*pixels;
	int				pixel_pos;

	if (data->caster.side == NORTH)
		pixels = data->mlx.no_texture->pixels;
	else if (data->caster.side == WEST)
		pixels = data->mlx.we_texture->pixels;
	else if (data->caster.side == EAST)
		pixels = data->mlx.ea_texture->pixels;
	else
		pixels = data->mlx.so_texture->pixels;
	pixel_pos = (tex.y * TEXTURE_WIDTH + tex.x) * 4;
	color = (pixels[pixel_pos]) << 24 | (pixels[pixel_pos + 1]) << 16 | \
		(pixels[pixel_pos + 2]) << 8 | (pixels[pixel_pos + 3]);
	return (color);
}

void	draw_walls(t_data *data, int x)
{
	unsigned int	color;
	double			step;
	double			tex_pos;
	int				y;

	data->caster.tex.x = (int)(data->caster.wall_x * (double)(TEXTURE_WIDTH));
	if (data->caster.side < NORTH && data->caster.ray_dir.x > 0)
		data->caster.tex.x = TEXTURE_WIDTH - data->caster.tex.x - 1;
	if (data->caster.side > EAST && data->caster.ray_dir.y < 0)
		data->caster.tex.x = TEXTURE_WIDTH - data->caster.tex.x - 1;
	step = 1.0 * TEXTURE_HEIGHT / data->caster.line_height;
	tex_pos = (data->caster.draw_start - SCREEN_HEIGHT / 2 + \
		data->caster.line_height / 2) * step;
	y = data->caster.draw_start;
	while (y <= data->caster.draw_end)
	{
		data->caster.tex.y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		color = get_color(data, data->caster.tex);
		mlx_put_pixel(data->mlx.fg, x, y, color);
		y++;
	}
}
