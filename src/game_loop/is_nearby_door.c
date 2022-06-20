/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_nearby_door.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 14:11:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 11:55:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_closable(int state)
{
	return (state == OPENING || state == OPEN);
}

static bool	check_door(t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->level.door_count)
	{
		if (is_player_facing_door(data, \
			data->doors[i].x, data->doors[i].y, get_distance(data->doors[i].x, \
			data->doors[i].y, data->cam.pos)) && \
			(is_closed(data->doors[i].state) || \
			is_closable(data->doors[i].state)) && data->doors[i].delay == 0)
		{
			if (is_closed(data->doors[i].state))
				data->doors[i].state = OPENING;
			else if (is_closable(data->doors[i].state))
				data->doors[i].state = CLOSING;
			data->doors[i].delay = 30;
			play_sound_vol(data, "./assets/wav_files/sounds/dropen.wav", \
				sprite_dist(data->cam.pos, (t_vector_double){data->doors[i].x, \
				data->doors[i].y}));
			return (true);
		}
	}
	return (false);
}

static bool	check_secrets(t_data *data)
{
	int				i;

	i = -1;
	while (++i < data->level.secret_count)
	{
		if (data->secrets[i].state == CLOSED && get_distance(data->secrets[i].x \
			, data->secrets[i].y, data->cam.pos) < 4)
		{
			data->secrets[i].state = OPENING;
			play_sound_vol(data, "./assets/wav_files/sounds/walmov.wav", \
				sprite_dist(data->cam.pos, \
				(t_vector_double){data->secrets[i].x, data->secrets[i].y}));
			data->player.secrets_found++;
			return (true);
		}
	}
	return (false);
}

bool	is_nearby_door(t_data *data)
{
	return (check_door(data) || check_secrets(data));
}
