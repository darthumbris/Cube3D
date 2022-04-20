/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_background.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 20:22:07 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

#include "stdio.h"
#include <math.h>

void	draw_background(t_data *data)
{
	int x;
	int y;
	uint8_t	*dst;
	uint8_t	*pix;
	t_vector_double bg;

	y = 0;
	dst = data->mlx.bg->pixels;
	pix = data->mlx.tex.ce_texture->pixels;
	bg.x = 0.5 + atan(data->cam.dir.x)/(M_PI*2);
    bg.y = 0.5 - asin(data->cam.dir.y)/M_PI;
	int offset = (int)((bg.y * data->mlx.tex.ce_texture->height) * data->mlx.tex.ce_texture->width) + (int)(bg.x * data->mlx.tex.ce_texture->width);
	printf("%d\n", offset);
	while (y < data->mlx.mlx_handle->height)
	{
		x = 0;
		while (x < data->mlx.mlx_handle->width)
		{
			*dst = *(pix + offset + 0);
			*(dst + 1) = *(pix + offset + 1);
			*(dst + 2) = *(pix + offset + 2);
			*(dst + 3) = 0xFF;
			dst += 4;
			pix += 4;
			x++;
		}
		y++;
	}
}

