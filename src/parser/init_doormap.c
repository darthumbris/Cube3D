/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doormap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 15:52:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 09:59:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
				data->doors[door_count].closing_timer = 0.0;
				if (i > 0 && is_wall_tile(data->level.map[i - 1][j]))
					data->doors[door_count].direction = EAST_WEST;
				else
					data->doors[door_count].direction = NORTH_SOUTH;
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
