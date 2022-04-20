/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_foreground.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:06 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 14:37:59 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	data->caster.tex_y = (data->caster.draw_start - data->cam.pitch - \
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
