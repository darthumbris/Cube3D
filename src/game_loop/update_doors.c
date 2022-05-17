/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_doors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:51:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 15:53:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	attempt_close_door(t_data *data, int i)
{
	if (data->doors[i].closing_timer < 5.0)
		data->doors[i].closing_timer += data->mlx.mlx_handle->delta_time;
	if (data->doors[i].closing_timer >= 5.0)
	{
		data->doors[i].state = CLOSED;
		if (get_distance((t_vector_int) \
		{data->doors[i].x, data->doors[i].y}, data->cam.pos) < 1)
			data->doors[i].state = OPEN;
		else
			data->doors[i].state = CLOSING;
	}
}

static void	check_perma_closed(t_data *data, int i)
{
	if (is_finish_tile(data->level.map[(int)data->cam.pos.y] \
		[(int)data->cam.pos.x]))
		data->doors[i].state = PERMA_CLOSED;
}

static void	try_close_door(t_data *data, int i)
{
	data->doors[i].s_timer = 1.0;
	data->doors[i].state = CLOSED;
	ma_engine_play_sound(&data->sound.engine, \
		"./assets/wav_files/sounds/drstop.wav", &data->sound.sfx);
	check_perma_closed(data, i);
}

void	update_doors(t_data *data, int i)
{
	while (++i < data->level.door_count)
	{
		if (data->doors[i].state == CLOSING)
		{
			data->doors[i].s_timer += data->mlx.mlx_handle->delta_time;
			if (data->doors[i].s_timer >= 1.0)
				try_close_door(data, i);
		}
		if (data->doors[i].state == OPENING)
		{
			data->doors[i].s_timer -= data->mlx.mlx_handle->delta_time;
			if (data->doors[i].s_timer <= 0.0)
			{
				data->doors[i].s_timer = 0.0;
				data->doors[i].state = OPEN;
				data->doors[i].closing_timer = 0.0;
			}
		}
		else if (data->doors[i].state == OPEN)
			attempt_close_door(data, i);
	}
}
