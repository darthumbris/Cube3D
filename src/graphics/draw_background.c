/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/13 09:51:35 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mlx.mlx_handle->height / 2)
	{
		x = 0;
		while (x < data->mlx.mlx_handle->width)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.ceiling_color);
			x++;
		}
	}
	while (y < data->mlx.mlx_handle->height)
	{
		x = 0;
		while (x < data->mlx.mlx_handle->width)
		{
			mlx_put_pixel(data->mlx.bg, x, y, data->level.floor_color);
			x++;
		}
	}
}
