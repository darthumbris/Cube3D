/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_objects.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:25:12 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 14:01:27 by shoogenb      ########   odam.nl         */
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
		if (is_nearby_door(data))
			data->doors[i].state = OPEN;
		else
			data->doors[i].state = CLOSING;
	}
}

void	update_doors(t_data *data, int i)
{
	while (i < data->level.door_count)
	{
		if (data->doors[i].state == CLOSING)
		{
			data->doors[i].s_timer += data->mlx.mlx_handle->delta_time;
			if (data->doors[i].s_timer >= 1.0)
			{
				data->doors[i].s_timer = 1.0;
				data->doors[i].state = CLOSED;
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
		i++;
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

void	update_objects(t_data *data)
{
	update_doors(data, 0);
	update_secret_walls(data);
	update_items(data);
}
