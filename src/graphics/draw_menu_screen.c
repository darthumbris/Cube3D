/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_menu_screen.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 14:28:15 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/30 15:49:31 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_menu_border(t_data *data, int max)
{
	t_vector_int	pos;
	uint8_t			*menu;

	pos.x = -1;
	while (++pos.x < data->hud.border_width)
	{
		pos.y = data->hud.pos_hud.y - 1;
		menu = data->mlx.fg->pixels + (max + pos.x * 4);
		while (++pos.y < data->mlx.mlx_handle->height)
		{
			*(uint32_t *)menu = MENU_BORDER_COLOR;
			menu -= data->floor.width4;
		}
	}
	pos.x = data->mlx.mlx_handle->width - data->hud.border_width - 2;
	while (++pos.x < data->mlx.mlx_handle->width)
	{
		pos.y = data->hud.pos_hud.y - 1;
		menu = data->mlx.fg->pixels + (max + pos.x * 4);
		while (++pos.y < data->mlx.mlx_handle->height)
		{
			*(uint32_t *)menu = MENU_BORDER_COLOR;
			menu -= data->floor.width4;
		}
	}
}

void	draw_cursor(t_data *data, t_vector_int pos)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*score;
	uint8_t			*pixels;

	pixel.x = -1;
	pixels = data->mlx.cursor->pixels;
	while (++pixel.x < data->hud.scale * data->mlx.cursor->width)
	{
		tex.x = pixel.x * data->hud.inv_scale;
		score = data->mlx.fg->pixels + (((pixel.x + pos.x) * 4) + \
			(pos.y) * \
			data->floor.width4);
		pixel.y = SCORE_NBR_SIZE * data->hud.scale;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			data->color = (*(uint32_t *)(pixels + ((tex.y * \
				data->mlx.cursor->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)score = data->color;
			score -= data->floor.width4;
		}
	}
}

void	draw_menu_screen(t_data *data, mlx_texture_t *texture)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];

	pos.x = data->hud.border_width - 1;
	pixs[0] = texture->pixels;
	while (++pos.x < data->mlx.mlx_handle->width - data->hud.border_width)
	{
		tex.x = (pos.x - data->hud.border_width) * data->hud.inv_scale;
		pixs[1] = data->mlx.fg->pixels + (data->hud.max_height * \
			data->floor.width4 + pos.x * 4);
		pos.y = data->hud.pos_hud.y - 1;
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
	draw_menu_border(data, data->hud.max_height * data->floor.width4);
}
