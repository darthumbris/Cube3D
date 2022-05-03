/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 11:53:43 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_single_nbr(t_data *data, int nbr, int x_pos)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*hud;
	uint8_t			*pixels;
	int				max;

	pixel.x = 0;
	pixels = data->mlx.tex.texarr[HUD_NUMBERS]->pixels;
	max = data->mlx.hud_scale * (data->mlx.tex.texarr[HUD_NUMBERS]->width / 10);
	while (pixel.x < max)
	{
		tex.x = pixel.x * data->mlx.inv_hud_scale + ((nbr % 10) * 8);
		hud = data->mlx.hud->pixels + (((pixel.x + x_pos) * 4) + \
			(data->mlx.mlx_handle->height - max) * data->floor.width4);
		pixel.y = max * 2 - 1;
		while (pixel.y > 0)
		{
			tex.y = pixel.y * data->mlx.inv_hud_scale;
			*(uint32_t *)hud = (*(int *)(pixels + \
			((tex.y * data->mlx.tex.texarr[HUD_NUMBERS]->width + tex.x) * 4)));
			hud -= data->floor.width4;
			pixel.y--;
		}
		pixel.x++;
	}
}

uint8_t	*get_face(t_data *data, int width)
{
	const int	face_dir = width * (rand() % 3);
	const int	face_health = ((99 - data->player.health) / 20) * (width + 1);

	return (data->mlx.tex.texarr[HUD_FACES]->pixels + \
		(face_health * data->mlx.tex.texarr[HUD_FACES]->width + face_dir) * 4);
}

//TODO make a random to choose between left/right/center face
void	draw_faces(t_data *data, int x_pos)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*pixels[2];
	const int		max = data->mlx.hud_scale * \
		(data->mlx.tex.texarr[HUD_FACES]->width / 3);

	pixel.x = 0;
	pixels[0] = get_face(data, data->mlx.tex.texarr[HUD_FACES]->width / 3);
	while (pixel.x < max)
	{
		tex.x = pixel.x * data->mlx.inv_hud_scale;
		pixels[1] = data->mlx.hud->pixels + (((pixel.x + x_pos) * 4) + \
			(data->mlx.mlx_handle->height - max - 4 * data->mlx.hud_scale) * \
			data->floor.width4);
		pixel.y = 0;
		while (pixel.y < max)
		{
			tex.y = pixel.y * data->mlx.inv_hud_scale;
			*(uint32_t *)pixels[1] = (*(int *)(pixels[0] + \
			((tex.y * data->mlx.tex.texarr[HUD_FACES]->width + tex.x) * 4)));
			pixels[1] += data->floor.width4;
			pixel.y++;
		}
		pixel.x++;
	}
}

/*
//TODO make this draw the hud to scale using the hud.png. 
	Also needs to be updated
//TODO the minimap can be put in the right corner of the hud
*/

void	draw_hud(t_data *data)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*pixels[2];
	const int		draw_start = data->mlx.mlx_handle->height - \
			data->mlx.tex.texarr[HUD_MAIN]->height * data->mlx.hud_scale;
	const int		draw_height = (data->mlx.mlx_handle->height - 1);

	pixel.x = -1;
	pixels[0] = data->mlx.tex.texarr[HUD_MAIN]->pixels;
	while (++pixel.x < data->mlx.mlx_handle->width)
	{
		tex.x = pixel.x * data->mlx.inv_hud_scale;
		pixels[1] = data->mlx.hud->pixels + (draw_height * \
			data->floor.width4 + pixel.x * 4);
		pixel.y = draw_start - 1;
		if (tex.x >= (int)data->mlx.tex.texarr[HUD_MAIN]->width)
			tex.x = data->mlx.tex.texarr[HUD_MAIN]->width - 1;
		while (++pixel.y < data->mlx.mlx_handle->height)
		{
			tex.y = (draw_height - pixel.y) * data->mlx.inv_hud_scale;
			*(uint32_t *)pixels[1] = (*(int *)(pixels[0] + \
			((tex.y * data->mlx.tex.texarr[HUD_MAIN]->width + tex.x) * 4)));
			pixels[1] -= data->floor.width4;
		}
	}
}
