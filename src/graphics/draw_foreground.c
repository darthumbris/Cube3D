/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_foreground.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 14:44:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_draw_variables(t_data *data, int y)
{
	data->floor.pos_y = y - data->mlx.mlx_handle->height / 2;
	data->floor.row_dist = data->floor.pos_z / data->floor.pos_y;
	data->floor.step.x = data->floor.row_dist * \
		(data->floor.ray_dir1.x - data->floor.ray_dir0.x) / \
		data->mlx.mlx_handle->width;
	data->floor.step.y = data->floor.row_dist * \
		(data->floor.ray_dir1.y - data->floor.ray_dir0.y) / \
		data->mlx.mlx_handle->width;
}

static void	set_new_pos(t_data *data, int x)
{
	data->floor.pos_d.x = (data->cam.pos.x + data->floor.row_dist * \
		data->floor.ray_dir0.x) + (data->floor.step.x * x);
	data->floor.pos_d.y = (data->cam.pos.y + data->floor.row_dist * \
		data->floor.ray_dir0.y) + (data->floor.step.y * x);
}

static void	set_tex(t_data *data)
{
	data->floor.tex.x = (int)(data->mlx.tex.no_texture->width * (data->floor.pos_d.x - (int)data->floor.pos_d.x)) & (data->mlx.tex.no_texture->width -1);
	data->floor.tex.y = (int)(data->mlx.tex.no_texture->height * (data->floor.pos_d.y - (int)data->floor.pos_d.y)) & (data->mlx.tex.no_texture->height -1);
}

void	draw_transparency(t_data *data, int x)
{
	int				y;
	uint8_t			*fg;
	uint8_t			*floor;
	uint8_t			*ceiling;
	uint8_t			*bg;
	int				simple;

	y = 0;
	bg = data->mlx.fg->pixels;
	floor = data->mlx.tex.texarr[3]->pixels;
	ceiling = data->mlx.tex.texarr[2]->pixels;
	simple = (data->mlx.fg->width + x) * 4;
	while (y < data->caster.draw_start)
	{
		set_draw_variables(data, y);
		set_new_pos(data, x);
		set_tex(data);
		*(uint32_t *)(bg + ((y * data->mlx.fg->width + x) * 4)) = (*(int *)(floor + (data->floor.tex.y * data->\
			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
		*(uint32_t *)(bg + (((data->mlx.mlx_handle->height - y - 1) * data->mlx.fg->width + x) * 4)) = (*(int *)(ceiling + (data->floor.tex.y * data->\
			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
		y++;
	}
	y = data->caster.draw_end + 1;
	fg = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->mlx.mlx_handle->height)
	{
		set_draw_variables(data, y);
		set_new_pos(data, x);
		set_tex(data);
		*(uint32_t *)(bg + ((y * data->mlx.fg->width + x) * 4)) = (*(int *)(floor + (data->floor.tex.y * data->\
			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
		*(uint32_t *)(bg + (((data->mlx.mlx_handle->height - y - 1) * data->mlx.fg->width + x) * 4)) = (*(int *)(ceiling + (data->floor.tex.y * data->\
			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
		y++;
	}
}

void	draw_walls(t_data *data, int x)
{
	int				y;
	uint8_t			*pixels;
	uint8_t			*dst;
	const double	step = (data->mlx.tex.texarr \
		[data->caster.side]->height / (double)data->caster.line_height);

	data->caster.tex_x = (int)(data->caster.wall_x * \
		(double)(data->mlx.tex.texarr[data->caster.side]->width - 1));
	if ((data->caster.side < NORTH && data->caster.ray_dir.x > 0) || \
		(data->caster.side > EAST && data->caster.ray_dir.y < 0))
		data->caster.tex_x = data->mlx.tex.texarr \
			[data->caster.side]->width - data->caster.tex_x - 1;
	data->caster.tex_y = (data->caster.draw_start - \
		data->mlx.mlx_handle->height / 2 + data->caster.line_height / 2) * step;
	y = data->caster.draw_start;
	pixels = data->mlx.tex.texarr[data->caster.side]->pixels;
	dst = data->mlx.fg->pixels + ((y * data->mlx.fg->width + x) * 4);
	while (y < data->caster.draw_end)
	{
		*(uint32_t *)dst = (*(int *)(pixels + ((int)data->caster.tex_y * data->\
		mlx.tex.texarr[data->caster.side]->width + data->caster.tex_x) * 4));
		dst += data->mlx.mlx_handle->width * 4;
		data->caster.tex_y += step;
		y++;
	}
}
