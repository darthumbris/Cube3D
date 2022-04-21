/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/21 16:26:15 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#include "stdio.h"
#include <math.h>

void	draw_background(t_data *data)
{
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.bg, 0, 0);
}

//just scale image to fit into window and then rotate when the camera is turned
