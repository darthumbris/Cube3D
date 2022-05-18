/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_sees_door.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 14:48:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 17:11:16 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_closed(int state)
{
	return (state == CLOSED);
}

bool	is_player_facing_door(t_data *data, int x, int y, int dist)
{
	double	angle;

	if (dist > 4)
		return (false);
	angle = get_angle_of_attack((t_vector_double) \
		{x, y}, data->cam.pos, data->cam.dir);
	if (dist < 4 && (angle < (M_PI_2 - M_PI_8) || \
		(2 * M_PI - angle) < (M_PI_2 - M_PI_8)))
		return (true);
	else if (dist < 2 && angle < M_PI_2)
		return (true);
	return (false);
}

//TODO also check if the door correspond with the elevator door is
// perma closed
bool	is_nearby_elevator(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->level.map_h)
	{
		j = 0;
		while (j < data->level.map_w)
		{
			if (is_finish_tile(data->level.map[i][j]) && \
				is_player_facing_door(data, j, i, \
				get_distance(j, i, data->cam.pos)))
			{
				data->mlx.tex.texarr[FINISH_WALL] = \
					data->mlx.tex.texarr[ELEVATOR_UP];
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}
