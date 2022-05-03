/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 11:00:37 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 12:04:17 by shoogenb      ########   odam.nl         */
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
		60 * data->mlx.hud_scale, 31 * data->mlx.hud_scale);
	ft_memset(data->mlx.minimap->pixels, 255, \
		data->mlx.minimap->width * data->mlx.minimap->height * sizeof(int));
	data->delay = 0;
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
