/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/02 16:47:35 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO have check for png failing
void	init_hud(t_data *data)
{
	data->mlx.faces = mlx_load_png(data->level.paths.path[HUD_FACES]);
	data->mlx.hud_texture = mlx_load_png(data->level.paths.path[HUD_MAIN]);
	data->mlx.numbers = mlx_load_png(data->level.paths.path[HUD_NUMBERS]);
	data->mlx.hud = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.hud_scale = (SCREEN_WIDTH / data->mlx.hud_texture->width);
	data->mlx.inv_hud_scale = 1.0 / data->mlx.hud_scale;
	data->mlx.minimap = mlx_new_image(data->mlx.mlx_handle, 60 * data->mlx.hud_scale, 31 * data->mlx.hud_scale); //TODO:hardcoded values
	ft_memset(data->mlx.minimap->pixels, 255, data->mlx.minimap->width * data->mlx.minimap->height * sizeof(int));
}

void	draw_single_nbr(t_data *data, int nbr, int x_pos)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*hud;
	uint8_t			*pixels;
	int				max;

	pixel.x = 0;
	pixels = data->mlx.numbers->pixels;
	max = data->mlx.hud_scale * (data->mlx.numbers->width / 10);
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
				((tex.y * data->mlx.numbers->width + tex.x) * 4)));
			hud -= data->floor.width4;
			pixel.y--;
		}
		pixel.x++;
	}
}

void	draw_score(t_data *data, int nbr)
{
	if (nbr > 9999)
		draw_single_nbr(data, nbr / 10000, 55 * data->mlx.hud_scale);
	if (nbr > 999)
		draw_single_nbr(data, nbr / 1000, 63 * data->mlx.hud_scale);
	if (nbr > 99)
		draw_single_nbr(data, nbr / 100, 71 * data->mlx.hud_scale);
	if (nbr > 9)
		draw_single_nbr(data, nbr / 10, 79 * data->mlx.hud_scale);
	draw_single_nbr(data, nbr, 87 * data->mlx.hud_scale);
}

void	draw_numbers(t_data *data)
{
	draw_single_nbr(data, data->level.level_number, 24 * data->mlx.hud_scale);
	draw_score(data, data->player.score);
	draw_single_nbr(data, data->player.lives, 112 * data->mlx.hud_scale);
	if (data->player.health > 99)
		draw_single_nbr(data, data->player.health / 100, \
		168 * data->mlx.hud_scale);
	if (data->player.health > 9)
		draw_single_nbr(data, data->player.health / 10, \
		176 * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.health, 184 * data->mlx.hud_scale);
	if (data->player.ammo > 9)
		draw_single_nbr(data, data->player.ammo / 10, \
		216 * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.ammo, 224 * data->mlx.hud_scale);
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
			data->mlx.hud_texture->height * data->mlx.hud_scale;
	const int		draw_height = (data->mlx.mlx_handle->height - 1);

	pixel.x = -1;
	pixels[0] = data->mlx.hud_texture->pixels;
	while (++pixel.x < data->mlx.mlx_handle->width)
	{
		tex.x = pixel.x * data->mlx.inv_hud_scale;
		pixels[1] = data->mlx.hud->pixels + (draw_height * \
			data->floor.width4 + pixel.x * 4);
		pixel.y = draw_start - 1;
		if (tex.x >= (int)data->mlx.hud_texture->width)
			tex.x = data->mlx.hud_texture->width - 1;
		while (++pixel.y < data->mlx.mlx_handle->height)
		{
			tex.y = (draw_height - pixel.y) * data->mlx.inv_hud_scale;
			*(uint32_t *)pixels[1] = (*(int *)(pixels[0] + \
			((tex.y * data->mlx.hud_texture->width + tex.x) * 4)));
			pixels[1] -= data->floor.width4;
		}
	}
}
