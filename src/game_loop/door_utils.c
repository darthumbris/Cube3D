/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:13:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 16:11:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_doors	*get_door_struct(t_data *data, t_vector_int pos)
{
	int	i;

	i = 0;
	while (i < data->level.door_count)
	{
		if (data->doors[i].y == pos.y && \
			data->doors[i].x == pos.x)
			return (data->doors + i);
		i++;
	}
	return (NULL);
}

t_secrets	*get_secret(t_data *data, t_vector_int pos)
{
	int	i;

	i = 0;
	while (i < data->level.secret_count)
	{
		if (data->secrets[i].y == pos.y && \
			data->secrets[i].x == pos.x)
			return (data->secrets + i);
		i++;
	}
	return (NULL);
}

int	get_distance(t_vector_int door_pos, t_vector_double player)
{
	const int	diffx = door_pos.x - (int)player.x;
	const int	diffy = door_pos.y - (int)player.y;

	return (diffx * diffx + diffy * diffy);
}

bool	is_nearby_door(t_data *data)
{
	int				i;

	i = -1;
	while (i++ < data->level.door_count)
	{
		if (data->doors[i].state == CLOSED && get_distance((t_vector_int) \
		{data->doors[i].x, data->doors[i].y}, data->cam.pos) < 4)
		{
			data->doors[i].state = OPENING;
			ma_engine_play_sound(&data->sound.engine, \
			"./assets/wav_files/sounds/dropen.wav", &data->sound.sfx_g);
			return (true);
		}
	}
	i = -1;
	while (i++ < data->level.secret_count)
	{
		if (data->secrets[i].state == CLOSED && get_distance((t_vector_int) \
		{data->secrets[i].x, data->secrets[i].y}, data->cam.pos) < 4)
		{
			data->secrets[i].state = OPENING;
			return (true);
		}
	}
	return (false);
}

bool	is_door_open(t_data *data, int y, int x)
{
	int				i;

	i = 0;
	while (i < data->level.door_count)
	{
		if (data->doors[i].state == OPEN && data->doors[i].y == y && \
			data->doors[i].x == x)
			return (true);
		i++;
	}
	i = 0;
	while (i < data->level.secret_count)
	{
		if (data->secrets[i].state == OPEN && data->secrets[i].y == y && \
			data->secrets[i].x == x)
			return (true);
		i++;
	}
	return (false);
}