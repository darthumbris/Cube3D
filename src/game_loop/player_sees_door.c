/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_sees_door.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 14:48:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 16:13:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_player_facing_door(t_data *data, int x, int y)
{
	const double	angle = get_angle_of_attack((t_vector_double) \
		{x, y}, data->cam.pos, data->cam.dir);

	return (angle < (M_PI_2 - M_PI_8) || \
		(2 * M_PI - angle) < (M_PI_2 - M_PI_8));
}

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
				is_player_facing_door(data, j, i) && \
				get_distance(j, i, data->cam.pos) < 4)
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
