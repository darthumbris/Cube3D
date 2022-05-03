/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 15:47:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_single_nbr(t_data *data, int nbr, int x_pos)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*hud;
	uint8_t			*pixels;

	pixel.x = 0;
	pixels = data->mlx.tex.texarr[HUD_NUMBERS]->pixels;
	while (++pixel.x < data->hud.max_size_numbers)
	{
		tex.x = pixel.x * data->hud.inv_scale + ((nbr % 10) * 8);
		hud = data->mlx.hud->pixels + (((pixel.x + x_pos) * 4) + \
			(data->mlx.mlx_handle->height - data->hud.max_size_numbers) * \
			data->floor.width4);
		pixel.y = data->hud.max_size_numbers * 2 - 1;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			*(uint32_t *)hud = (*(int *)(pixels + ((tex.y * \
				data->mlx.tex.texarr[HUD_NUMBERS]->width + tex.x) * 4)));
			hud -= data->floor.width4;
		}
	}
}

uint8_t	*get_face(t_data *data, int width)
{
	const int	face_dir = width * (rand() % 3);
	const int	face_health = ((99 - data->player.health) / 20) * (width + 1);

	return (data->mlx.tex.texarr[HUD_FACES]->pixels + \
		(face_health * data->mlx.tex.texarr[HUD_FACES]->width + face_dir) * 4);
}

void	draw_faces(t_data *data)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*pixels[2];

	pixel.x = -1;
	pixels[0] = get_face(data, data->mlx.tex.texarr[HUD_FACES]->width / 3);
	while (pixel.x++ < data->hud.max_size_faces)
	{
		tex.x = pixel.x * data->hud.inv_scale;
		pixels[1] = data->mlx.hud->pixels + (((pixel.x + data->hud.face_pos_x) \
			* 4) + (data->hud.max_height + 1 - data->hud.max_size_faces - 4 * \
			data->hud.scale) * data->floor.width4);
		pixel.y = 0;
		while (pixel.y++ < data->hud.max_size_faces)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			*(uint32_t *)pixels[1] = (*(int *)(pixels[0] + \
			((tex.y * data->mlx.tex.texarr[HUD_FACES]->width + tex.x) * 4)));
			pixels[1] += data->floor.width4;
		}
	}
}

void	draw_hud(t_data *data)
{
	t_vector_int	pos;
	t_vector_int	tex;
	uint8_t			*pixs[2];

	pos.x = -1;
	pixs[0] = data->mlx.tex.texarr[HUD_MAIN]->pixels;
	while (++pos.x < data->mlx.mlx_handle->width)
	{
		tex.x = pos.x * data->hud.inv_scale;
		pixs[1] = data->mlx.hud->pixels + (data->hud.max_height * \
			data->floor.width4 + pos.x * 4);
		pos.y = data->hud.y_pos_hud - 1;
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
