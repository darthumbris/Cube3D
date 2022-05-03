/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 11:00:37 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 16:01:09 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO:hardcoded values for minimap
void	init_hud(t_data *data)
{
	data->mlx.hud = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.hud_scale = (SCREEN_WIDTH / \
		data->mlx.tex.texarr[HUD_MAIN]->width);
	data->mlx.inv_hud_scale = 1.0 / data->mlx.hud_scale;
	data->mlx.minimap = mlx_new_image(data->mlx.mlx_handle, \
		MINIMAP_WIDTH * data->mlx.hud_scale, MINIMAP_HEIGHT * \
		data->mlx.hud_scale);
	ft_memset(data->mlx.minimap->pixels, 255, \
		data->mlx.minimap->width * data->mlx.minimap->height * sizeof(int));
	data->mlx.minimap_scale = \
		((float)data->mlx.minimap->height / (float)data->mlx.minimap->width);
	data->mlx.minimap_zoom = 10;
	data->delay = 0;
}

void	draw_score(t_data *data, int nbr)
{
	if (nbr > 9999)
		draw_single_nbr(data, nbr / 10000, SCORE_DIGIT_0_POS * \
		data->mlx.hud_scale);
	if (nbr > 999)
		draw_single_nbr(data, nbr / 1000, SCORE_DIGIT_1_POS * \
		data->mlx.hud_scale);
	if (nbr > 99)
		draw_single_nbr(data, nbr / 100, SCORE_DIGIT_2_POS * \
		data->mlx.hud_scale);
	if (nbr > 9)
		draw_single_nbr(data, nbr / 10, SCORE_DIGIT_3_POS * \
		data->mlx.hud_scale);
	draw_single_nbr(data, nbr, SCORE_DIGIT_4_POS * data->mlx.hud_scale);
}

void	draw_numbers(t_data *data)
{
	draw_single_nbr(data, data->level.level_number, LEVEL_DIGIT_POS * \
		data->mlx.hud_scale);
	draw_score(data, data->player.score);
	draw_single_nbr(data, data->player.lives, LIVES_DIGIT_POS * \
		data->mlx.hud_scale);
	if (data->player.health > 99)
		draw_single_nbr(data, data->player.health / 100, \
		HEALTH_DIGIT_0_POS * data->mlx.hud_scale);
	if (data->player.health > 9)
		draw_single_nbr(data, data->player.health / 10, \
		HEALTH_DIGIT_1_POS * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.health, HEALTH_DIGIT_2_POS * \
		data->mlx.hud_scale);
	if (data->player.ammo > 9)
		draw_single_nbr(data, data->player.ammo / 10, \
		AMMO_DIGIT_0_POS * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.ammo, AMMO_DIGIT_1_POS * \
		data->mlx.hud_scale);
}
