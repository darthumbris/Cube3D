/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 14:34:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

// static void	set_new_pos(t_data *data, int x)
// {
// 	data->floor.pos_d.x = (data->cam.pos.x + data->floor.row_dist * \
// 		data->floor.ray_dir0.x) + (data->floor.step.x * x);
// 	data->floor.pos_d.y = (data->cam.pos.y + data->floor.row_dist * \
// 		data->floor.ray_dir0.y) + (data->floor.step.y * x);
// }

// #include <stdio.h>
// //put this in the draw walls part?
// void	draw_floor(t_data *data)
// {
// 	int				x;
// 	int				y;
// 	uint8_t			*bg;
// 	uint8_t			*floor;
// 	uint8_t			*ceiling;

// 	floor = data->mlx.tex.texarr[3]->pixels;
// 	ceiling = data->mlx.tex.texarr[2]->pixels;
// 	bg = data->mlx.fg->pixels;
// 	set_start_draw_variables(data);
// 	y = 0;
// 	while (y < data->mlx.mlx_handle->height)
// 	{
// 		set_draw_variables(data, y);
// 		x = 0;
// 		while (x < data->mlx.mlx_handle->width)
// 		{
// 			set_new_pos(data, x);
// 			//data->floor.pos_int.x = (int)data->floor.pos_d.x;
// 			//data->floor.pos_int.y = (int)data->floor.pos_d.y;
// 			data->floor.tex.x = (int)(data->mlx.tex.no_texture->width * (data->floor.pos_d.x - (int)data->floor.pos_d.x)) & (data->mlx.tex.no_texture->width -1);
// 			data->floor.tex.y = (int)(data->mlx.tex.no_texture->height * (data->floor.pos_d.y - (int)data->floor.pos_d.y)) & (data->mlx.tex.no_texture->height -1);
// 			*(uint32_t *)(bg + ((y * data->mlx.fg->width + x) * 4)) = (*(int *)(floor + (data->floor.tex.y * data->\
// 			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
// 			*(uint32_t *)(bg + (((data->mlx.mlx_handle->height - y - 1) * data->mlx.fg->width + x) * 4)) = (*(int *)(ceiling + (data->floor.tex.y * data->\
// 			mlx.tex.no_texture->width + data->floor.tex.x) * 4));
// 			x++;
// 		}
// 		y++;
// 	}
// }
