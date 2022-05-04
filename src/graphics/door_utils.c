/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:13:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/04 09:21:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
		if (data->level.doors[i][2] == 1)
		{
			door_pos.x = data->level.doors[i][1];
			door_pos.y = data->level.doors[i][0];
			if (get_distance(door_pos, data->cam.pos) < 5)
			{
				printf("opening normal door\n");
				data->level.doors[i][2] = 3;
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
		if (data->level.doors[i][2] == 3 && data->level.doors[i][0] == y && data->level.doors[i][1] == x)
			return (true);
		i++;
	}
	return (false);
}
