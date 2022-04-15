#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int		y;
	uint8_t	*pixel;

	y = 0;
	while (y < data->caster.draw_start)
	{
		pixel = &data->mlx.fg->pixels[(y * data->mlx.fg->width + x) * 4];
		ft_bzero(pixel, 4);
		y++;
	}
	y = data->caster.draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		pixel = &data->mlx.fg->pixels[(y * data->mlx.fg->width + x) * 4];
		ft_bzero(pixel, 4);
		y++;
	}
}

static void	set_color(t_data *data, t_vector_uint	tex, int x, int y)
{
	uint8_t			*pixels;
	int				pixel_pos;
	int				fg_pos;

	if (data->caster.side == NORTH)
		pixels = data->mlx.no_texture->pixels;
	else if (data->caster.side == WEST)
		pixels = data->mlx.we_texture->pixels;
	else if (data->caster.side == EAST)
		pixels = data->mlx.ea_texture->pixels;
	else
		pixels = data->mlx.so_texture->pixels;
	pixel_pos = (tex.y * TEXTURE_WIDTH + tex.x) * 4;
	fg_pos = (y * data->mlx.fg->width + x) * 4;
	data->mlx.fg->pixels[fg_pos] = pixels[pixel_pos];
	data->mlx.fg->pixels[fg_pos + 1] = pixels[pixel_pos + 1];
	data->mlx.fg->pixels[fg_pos + 2] = pixels[pixel_pos + 2];
	data->mlx.fg->pixels[fg_pos + 3] = pixels[pixel_pos + 3];
}

void	draw_walls(t_data *data, int x)
{
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
		set_color(data, data->caster.tex, x, y);
		y++;
	}
}