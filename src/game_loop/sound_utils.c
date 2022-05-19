/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sound_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 14:39:52 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/19 14:37:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//play sound at specific volume, standard is 1.0
void	play_sound_vol(t_data *data, char *fpath, double dist)
{
	double	volume;

	volume = 100.0 - sqrt(dist) * 4.0;
	volume /= 100;
	if (volume < 0)
		volume = 0;
	ma_sound_set_volume(&data->sound.sfx_g, (float)volume);
	ma_engine_play_sound(&data->sound.engine, fpath, &data->sound.sfx_g);
}
