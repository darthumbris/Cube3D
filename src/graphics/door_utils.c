/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:13:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 15:10:08 by shoogenb      ########   odam.nl         */
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

int	get_distance(t_vector_int door_pos, t_vector_double player)
{
	const int	diffx = door_pos.x - (int)player.x;
	const int	diffy = door_pos.y - (int)player.y;

	return (diffx * diffx + diffy * diffy);
}

bool	is_nearby_door(t_data *data)
{
	int				i;
	t_vector_int	door_pos;

	i = 0;
	while (i < data->level.door_count)
	{
		if (data->doors[i].state == CLOSED)
		{
			door_pos.x = data->doors[i].x;
			door_pos.y = data->doors[i].y;
			if (get_distance(door_pos, data->cam.pos) < 4)
			{
				data->doors[i].state = OPENING;
				return (true);
			}
		}
		i++;
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
	return (false);
}