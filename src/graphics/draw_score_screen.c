/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_score_screen.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 10:34:22 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 17:04:09 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_colon(t_data *data, t_vector_int pos, \
								mlx_texture_t *nbr_tex)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*score;
	uint8_t			*pixels;

	pixel.x = -1;
	pixels = nbr_tex->pixels;
	while (++pixel.x < data->hud.max_size_score_nbrs)
	{
		tex.x = pixel.x * data->hud.inv_scale + COLON_POS_X;
		score = data->mlx.score_screen->pixels + (((pixel.x + pos.x) * 4) + \
			(data->mlx.mlx_handle->height - pos.y) * \
			data->floor.width4);
		pixel.y = SCORE_NBR_SIZE * data->hud.scale + 12;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			data->color = (*(int *)(pixels + ((tex.y * \
				nbr_tex->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)score = data->color;
			score -= data->floor.width4;
		}
	}
}

void	draw_percentage(t_data *data, t_vector_int pos, \
								mlx_texture_t *nbr_tex)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*score;
	uint8_t			*pixels;

	pixel.x = -1;
	pixels = nbr_tex->pixels;
	while (++pixel.x < data->hud.max_size_score_nbrs + (2 * data->hud.scale))
	{
		tex.x = pixel.x * data->hud.inv_scale + PERCENTAGE_POS_X;
		score = data->mlx.score_screen->pixels + (((pixel.x + pos.x) * 4) + \
			(data->mlx.mlx_handle->height - pos.y) * \
			data->floor.width4);
		pixel.y = SCORE_NBR_SIZE * data->hud.scale + 12;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			data->color = (*(int *)(pixels + ((tex.y * \
				nbr_tex->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)score = data->color;
			score -= data->floor.width4;
		}
	}
}

void	draw_single_nbr_score(t_data *data, int nbr, t_vector_int pos, \
								mlx_texture_t *nbr_tex)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*score;
	uint8_t			*pixels;

	pixel.x = -1;
	pixels = nbr_tex->pixels;
	while (++pixel.x < data->hud.max_size_score_nbrs)
	{
		tex.x = pixel.x * data->hud.inv_scale + ((nbr % 10) * SCORE_NBR_SIZE);
		score = data->mlx.score_screen->pixels + (((pixel.x + pos.x) * 4) + \
			(data->mlx.mlx_handle->height - pos.y) * \
			data->floor.width4);
		pixel.y = SCORE_NBR_SIZE * data->hud.scale + 12;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			data->color = (*(int *)(pixels + ((tex.y * \
				nbr_tex->width + tex.x) * 4)));
			if (data->color)
				*(uint32_t *)score = data->color;
			score -= data->floor.width4;
		}
	}
}

void	draw_score_screen(t_data *data, mlx_texture_t *texture)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];

	pos.x = data->hud.border_width - 1;
	pixs[0] = texture->pixels;
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
