/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_score_screen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 10:34:22 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 10:43:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_score_screen(t_data *data)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];

	pos.x = data->hud.border_width - 1;
	pixs[0] = data->mlx.tex.texarr[SCORE_SCREEN]->pixels;
	while (++pos.x < data->mlx.mlx_handle->width - data->hud.border_width)
	{
		tex.x = (pos.x - data->hud.border_width) * data->hud.inv_scale;
		pixs[1] = data->mlx.score_screen->pixels + (data->hud.max_height * \
			data->floor.width4 + pos.x * 4);
		pos.y = 0;
		if (tex.x >= data->hud.max_width)
			tex.x = data->hud.max_width - 1;
		while (++pos.y < data->mlx.mlx_handle->height)
		{
			tex.y = (data->hud.max_height - pos.y) * data->hud.inv_scale;
			data->color = (*(int *)(pixs[0] + \
				((tex.y * data->hud.max_width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)pixs[1] = data->color;
			pixs[1] -= data->floor.width4;
		}
	}
}
