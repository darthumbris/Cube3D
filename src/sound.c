/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sound.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 13:47:57 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/17 14:23:55 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	play_sound(t_data *data, int type)
{
	data->sound.curr = type;
	ma_sound_start(&data->sound.soundtrack[type]);
}

void	soundtrack(t_data *data)
{
	if (ma_sound_at_end(&data->sound.soundtrack[data->sound.curr]))
	{
		if (data->sound.curr == SEARCHN)
			play_sound(data, CORNER);
		else if (data->sound.curr == CORNER)
			play_sound(data, WARMARCH);
		else if (data->sound.curr == WARMARCH)
			play_sound(data, SEARCHN);
	}
}
