/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doormap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 15:52:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 17:24:44 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_secret_direction(t_data *data, int i, int j, int door)
{
	int			wall_hit_neg;
	int			wall_hit_pos;
	const int	temp_i = i;
	const int	temp_j = j;

	wall_hit_neg = 0;
	wall_hit_pos = 0;
	if (data->doors[door].direction == NORTH_SOUTH)
	{
		while (!is_wall_tile(data->level.map[i][j]) && i > 0)
		{
			i--;
			wall_hit_neg++;
		}
		i = temp_i;
		while (!is_wall_tile(data->level.map[i][j]) && i < data->level.map_h)
		{
			i++;
			wall_hit_pos++;
		}
		if (wall_hit_neg > wall_hit_pos)
			data->doors[door].direction = SOUTH;
		else
			data->doors[door].direction = NORTH;
	}
	else
	{
		while (!is_wall_tile(data->level.map[i][j]) && j > 0)
		{
			j--;
			wall_hit_neg++;
		}
		j = temp_j;
		while (!is_wall_tile(data->level.map[i][j]) && j < data->level.map_w)
		{
			j++;
			wall_hit_pos++;
		}
		if (wall_hit_neg > wall_hit_pos)
			data->doors[door].direction = EAST;
		else
			data->doors[door].direction = WEST;
	}
}

static void	set_door_direction(t_data *data, int i, int j, int door)
{
	if (i > 0 && is_wall_tile(data->level.map[i - 1][j]))
		data->doors[door].direction = EAST_WEST;
	else
		data->doors[door].direction = NORTH_SOUTH;
}

static void	set_direction(t_data *data, int i, int j, int door)
{
	set_door_direction(data, i, j, door);
	if (data->level.map[i][j] == 'h' || data->level.map[i][j] == 'H')
	{
		set_secret_direction(data, i, j, door);
		data->doors[door].s_timer = 0.0;
	}
}

void	set_door_map(t_data *data)
{
	int	i;
	int	j;
	int	door_count;

	i = 0;
	door_count = 0;
	while (data->level.map[i])
	{
		j = 0;
		while (data->level.map[i][j])
		{
			if (is_door_tile(data->level.map[i][j]))
			{
				data->doors[door_count].x = j;
				data->doors[door_count].y = i;
				data->doors[door_count].type = data->level.map[i][j];
				data->doors[door_count].state = CLOSED;
				data->doors[door_count].s_timer = 1.0;
				set_direction(data, i, j, door_count);
				door_count++;
			}
			j++;
		}
		i++;
	}
}

bool	init_door_map(t_data *data)
{
	data->doors = ft_calloc(sizeof(t_doors), data->level.door_count);
	if (data->doors == NULL)
		return (false);
	return (true);
}
