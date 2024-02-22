/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   items_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 15:24:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/20 11:15:00 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	simple_heal_item(t_data *data, t_sprite_lst *item, int kind)
{
	if (kind == MEDKIT)
		data->player.health += 25;
	else if (kind == DOG_MEAL)
		data->player.health += 4;
	else if (kind == STIMULANT)
		data->player.health += 10;
	if (data->player.health > 100)
		data->player.health = 100;
	data->update_hud = true;
	item->sprite_data.kind = 0;
	if (kind == MEDKIT)
		ma_engine_play_sound(&data->sound.engine, \
		"./assets/wav_files/sounds/healup.wav", &data->sound.sfx_g);
	else
		ma_engine_play_sound(&data->sound.engine, \
		"./assets/wav_files/sounds/foodup.wav", &data->sound.sfx_g);
}
