/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 16:13:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 16:49:13 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"



bool	is_nearby_door(t_data *data)
{
	int				i;
	t_vector_double	door_pos;

	i = 0;
	while (i < data->level.door_count)
	{
		if (data->level.doors[i][2] == 1)
		{
			door_pos.x = data->level.doors[i][0];
			door_pos.y = data->level.doors[i][1];
			printf("spritedist: %f\n", sprite_dist(data->cam.pos, door_pos));
			if (sprite_dist(data->cam.pos, door_pos) < 64)
			{
				printf("opening door\n");
				printf("door at: %d,%d\n", data->level.doors[i][0], data->level.doors[i][1]);
				printf("player at: %f,%f\n", data->cam.pos.x, data->cam.pos.y);
				printf("map: %d\n", data->level.map[31][50]);
				return (true);
			}
		}
		i++;
	}
	return (false);
}
