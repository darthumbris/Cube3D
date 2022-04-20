/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 15:25:28 by shoogenb      ########   odam.nl         */
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
