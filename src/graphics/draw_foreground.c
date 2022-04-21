/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_foreground.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/21 09:53:16 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_draw_variables(t_data *data, int y)
{
	data->floor.pos_y = y - data->floor.halve_height;
	data->floor.row_dist = data->floor.pos_z / data->floor.pos_y;
	data->floor.step.x = (data->floor.row_dist * \
		(data->floor.ray_dir1.x - data->floor.ray_dir0.x)) * \
		data->floor.inverse_width;
	data->floor.step.y = data->floor.row_dist * \
		(data->floor.ray_dir1.y - data->floor.ray_dir0.y) * \
		data->floor.inverse_width;
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
	data->floor.tex.x = (int)(data->mlx.tex.no_texture->width * \
	(data->floor.pos_d.x - (int)data->floor.pos_d.x)) & \
		(data->mlx.tex.no_texture->width -1);
	data->floor.tex.y = (int)(data->mlx.tex.no_texture->height * \
	(data->floor.pos_d.y - (int)data->floor.pos_d.y)) & \
		(data->mlx.tex.no_texture->height -1);
}

void	draw_floor_ceiling(t_data *data, int x)
{
	int				y;
	uint8_t			*floor;
	uint8_t			*ceiling;
	uint8_t			*bg_up;
	uint8_t			*bg_down;

	floor = data->mlx.tex.texarr[3]->pixels;
	ceiling = data->mlx.tex.texarr[2]->pixels;
	y = data->caster.draw_end;
	bg_up = data->mlx.fg->pixels + data->floor.x4 + (y * data->floor.width4);
	bg_down = data->mlx.fg->pixels + ((data->mlx.mlx_handle->height - y - 1) * \
		data->floor.width4 + data->floor.x4);
	while (y < data->mlx.mlx_handle->height)
	{
		set_draw_variables(data, y);
		set_new_pos(data, x);
		set_tex(data);
		data->floor.color_pos = (data->floor.tex.y * \
			data->mlx.tex.no_texture->width + data->floor.tex.x) * 4;
		*(uint32_t *)bg_up = (*(int *)(floor + data->floor.color_pos));
		*(uint32_t *)bg_down = (*(int *)(ceiling + data->floor.color_pos));
		bg_up += data->floor.width4;
		bg_down -= data->floor.width4;
		y++;
	}
}

void	draw_walls(t_data *data)
{
	int				y;
	uint8_t			*pixels;
	uint8_t			*fg;
	const double	step = (data->mlx.tex.texarr \
		[data->caster.side]->height / (double)data->caster.line_height);

	y = data->caster.draw_start;
	data->caster.tex_x = (int)(data->caster.wall_x * \
		(double)(data->mlx.tex.texarr[data->caster.side]->width - 1));
	data->caster.tex_y = (y - data->floor.halve_height + \
		(data->caster.line_height >> 1)) * step;
	pixels = data->mlx.tex.texarr[data->caster.side]->pixels;
	fg = data->mlx.fg->pixels + ((y * data->floor.width4) + data->floor.x4);
	while (y < data->caster.draw_end)
	{
		*(uint32_t *)fg = (*(int *)(pixels + (((int)data->caster.tex_y * data->\
		mlx.tex.texarr[data->caster.side]->width + data->caster.tex_x) << 2)));
		fg += data->floor.width4;
		data->caster.tex_y += step;
		y++;
	}
}
