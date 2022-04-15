#include "cubed.h"

void	draw_transparency(t_data *data, int x)
{
	int		y;

	y = 0;
	while (y < data->caster.draw_start)
	{
		data->mlx.fg->pixels[((y * data->mlx.fg->width + x) * 4) + 3] = 0;
		y++;
	}
	y = data->caster.draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		data->mlx.fg->pixels[((y * data->mlx.fg->width + x) * 4) + 3] = 0;
		y++;
	}
}

static void	set_color(t_data *data, t_vector_uint	tex, int x, int y)
{
	int				pixel_pos;
	int				fg_pos;

	pixel_pos = (tex.y * TEXTURE_WIDTH + tex.x) * 4;
	fg_pos = (y * data->mlx.fg->width + x) * 4;
	ft_memcpy(data->mlx.fg->pixels + fg_pos, \
		data->mlx.tex[data->caster.side]->pixels + pixel_pos, 4);
}

void	draw_walls(t_data *data, int x)
{
	double			step;
	double			tex_pos;
	int				y;

	data->caster.tex.x = (int)(data->caster.wall_x * (double)(TEXTURE_WIDTH));
	if (data->caster.side < NORTH && data->caster.ray_dir.x > 0)
		data->caster.tex.x = TEXTURE_WIDTH - data->caster.tex.x - 1;
	else if (data->caster.side > EAST && data->caster.ray_dir.y < 0)
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
