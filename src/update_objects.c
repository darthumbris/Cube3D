/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_objects.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:25:12 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 13:43:07 by pvan-dij      ########   odam.nl         */
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

void	update_doors(t_data *data, int i)
{
	while (++i < data->level.door_count)
	{
		if (data->doors[i].state == CLOSING)
		{
			data->doors[i].s_timer += data->mlx.mlx_handle->delta_time;
			if (data->doors[i].s_timer >= 1.0)
			{
				data->doors[i].s_timer = 1.0;
				data->doors[i].state = CLOSED;
				ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/drstop.wav", &data->sound.sfx_g);
				check_perma_closed(data, i);
			}
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

static void	set_new_secret_pos(t_data *data, int i)
{
	const int	x = data->secrets[i].x;
	const int	y = data->secrets[i].y;

	if (data->secrets[i].direction == S_WEST)
	{
		if (data->secrets[i].type == '<')
			data->level.map[y][x - 2] = '8';
		else
			data->level.map[y][x - 2] = '2';
	}
	else if (data->secrets[i].direction == S_EAST)
	{
		data->level.map[y][x + 2] = '1';
	}
	else if (data->secrets[i].direction == S_NORTH)
	{
		data->level.map[y - 2][x] = '5';
	}
	else if (data->secrets[i].direction == S_SOUTH)
	{
		data->level.map[y + 2][x] = '2';
	}
	data->level.map[y][x] = '0';
	data->level.wall_map[y][x] = 0;
}

void	update_secret_walls(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->level.secret_count)
	{
		if ((is_secret_tile(data->secrets[i].type)) && \
			data->secrets[i].state == OPENING)
		{
			data->secrets[i].s_timer += data->mlx.mlx_handle->delta_time;
			if (data->secrets[i].s_timer >= 2.0)
			{
				data->secrets[i].s_timer = 2.0;
				set_new_secret_pos(data, i);
				data->secrets[i].state = OPEN;
			}
		}
		i++;
	}
}
