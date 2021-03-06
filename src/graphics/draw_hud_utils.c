/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 11:00:37 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 11:40:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_border(t_data *data, int max)
{
	t_vector_int	pos;
	uint8_t			*hud;

	pos.x = -1;
	while (++pos.x < data->hud.border_width)
	{
		pos.y = data->hud.pos_hud.y - 1;
		hud = data->mlx.hud->pixels + (max + pos.x * 4);
		while (++pos.y < data->mlx.mlx_handle->height)
		{
			*(uint32_t *)hud = BORDER_COLOR;
			hud -= data->floor.width4;
		}
	}
	pos.x = data->mlx.mlx_handle->width - data->hud.border_width - 2;
	while (++pos.x < data->mlx.mlx_handle->width)
	{
		pos.y = data->hud.pos_hud.y - 1;
		hud = data->mlx.hud->pixels + (max + pos.x * 4);
		while (++pos.y < data->mlx.mlx_handle->height)
		{
			*(uint32_t *)hud = BORDER_COLOR;
			hud -= data->floor.width4;
		}
	}
}

static void	init_minimap(t_data *data)
{
	data->mlx.minimap = mlx_new_image(data->mlx.mlx_handle, \
		MINIMAP_WIDTH * data->hud.scale, MINIMAP_HEIGHT * \
		data->hud.scale);
	ft_memset(data->mlx.minimap->pixels, 0, \
		data->mlx.minimap->width * data->mlx.minimap->height * sizeof(int));
	data->hud.pos_map.x = data->mlx.minimap->width + \
				data->mlx.mlx_handle->width \
				- data->mlx.minimap->width - MINIMAP_POS * \
				data->hud.scale - data->hud.border_width;
	data->hud.pos_map.y = data->mlx.mlx_handle->height - \
						data->mlx.minimap->height - 1 - \
						data->hud.scale * 4;
	data->mlx.minimap_zoom = 8;
	data->mlx.minimap_scale = \
		((float)data->mlx.minimap->height / (float)data->mlx.minimap->width);
	data->mlx.hud_scale = \
	(double)data->mlx.hud->height / (double)data->mlx.hud->width;
}

void	init_hud(t_data *data)
{
	data->mlx.hud = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.score_screen = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->hud.scale = (SCREEN_WIDTH / \
		(double)data->mlx.tex.texarr[HUD_MAIN]->width);
	data->hud.inv_scale = 1.0 / data->hud.scale;
	data->delay = 0;
	data->hud.max_height = data->mlx.mlx_handle->height - 1;
	data->hud.pos_hud.y = data->mlx.mlx_handle->height - \
			data->mlx.tex.texarr[HUD_MAIN]->height * data->hud.scale;
	data->hud.max_width = data->mlx.tex.texarr[HUD_MAIN]->width;
	data->hud.border_width = (data->mlx.mlx_handle->width - \
					data->hud.max_width * data->hud.scale) / 2;
	data->hud.max_size_faces = data->hud.scale * \
		(data->mlx.tex.texarr[HUD_FACES]->width / 3);
	data->hud.face_pos_x = FACES_POS * data->hud.scale + data->hud.border_width;
	data->hud.max_size_numbers = data->hud.scale * \
		(data->mlx.tex.texarr[HUD_NUMBERS]->width / 10);
	data->hud.max_size_score_nbrs = data->hud.scale * \
		(data->mlx.tex.texarr[SCORE_NUMBERS]->width / 12);
	init_minimap(data);
	draw_border(data, data->hud.max_height * data->floor.width4);
}

void	draw_score(t_data *data, int nbr)
{
	if (nbr > 9999)
		draw_single_nbr(data, nbr / 10000, SCORE_DIGIT_0_POS * \
		data->hud.scale + data->hud.border_width);
	if (nbr > 999)
		draw_single_nbr(data, nbr / 1000, SCORE_DIGIT_1_POS * \
		data->hud.scale + data->hud.border_width);
	if (nbr > 99)
		draw_single_nbr(data, nbr / 100, SCORE_DIGIT_2_POS * \
		data->hud.scale + data->hud.border_width);
	if (nbr > 9)
		draw_single_nbr(data, nbr / 10, SCORE_DIGIT_3_POS * \
		data->hud.scale);
	draw_single_nbr(data, nbr, SCORE_DIGIT_4_POS * \
		data->hud.scale + data->hud.border_width);
}

void	draw_numbers(t_data *data)
{
	draw_single_nbr(data, data->level.level_number, LEVEL_DIGIT_POS * \
		data->hud.scale + data->hud.border_width);
	draw_score(data, data->player.score);
	draw_single_nbr(data, data->player.lives, LIVES_DIGIT_POS * \
		data->hud.scale + data->hud.border_width);
	if (data->player.health > 99)
		draw_single_nbr(data, data->player.health / 100, \
		HEALTH_DIGIT_0_POS * data->hud.scale + data->hud.border_width);
	if (data->player.health > 9)
		draw_single_nbr(data, data->player.health / 10, \
		HEALTH_DIGIT_1_POS * data->hud.scale + data->hud.border_width);
	draw_single_nbr(data, data->player.health, HEALTH_DIGIT_2_POS * \
		data->hud.scale + data->hud.border_width);
	if (data->player.ammo > 9)
		draw_single_nbr(data, data->player.ammo / 10, \
		AMMO_DIGIT_0_POS * data->hud.scale + data->hud.border_width);
	draw_single_nbr(data, data->player.ammo, AMMO_DIGIT_1_POS * \
		data->hud.scale + data->hud.border_width);
}
