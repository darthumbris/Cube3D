/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sound_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 14:39:52 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/18 14:43:05 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//play sound at specific volume, standard is 1.0
void	play_sound_vol(t_data *data, char *fpath, float vol)
{
	ma_sound_group_set_volume(&data->sound.sfx_g, vol);
	ma_engine_play_sound(&data->sound.engine, fpath, &data->sound.sfx_g);
	ma_sound_group_set_volume(&data->sound.sfx_g, 1.0);
}
