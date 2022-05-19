/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_secrets.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:25:12 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 14:41:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
			data->secrets[i].s_timer += data->mlx.mlx_handle->delta_time * 0.5;
			if (data->secrets[i].s_timer >= 2.0)
			{
				data->secrets[i].s_timer = 2.0;
				set_new_secret_pos(data, i);
				data->secrets[i].state = OPEN;
				play_sound_vol(data, "./assets/wav_files/sounds/walstop.wav", \
				sprite_dist(data->cam.pos, \
				(t_vector_double){data->secrets[i].x, data->secrets[i].y}));
			}
		}
		i++;
	}
}
