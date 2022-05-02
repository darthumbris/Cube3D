/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/02 10:21:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#include "stdio.h"
#include <math.h>

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

//just scale image to fit into window and then rotate when the camera is turned
