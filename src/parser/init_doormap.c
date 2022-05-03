/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doormap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 15:52:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/03 16:40:32 by shoogenb      ########   odam.nl         */
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
				data->level.doors[door_count][0] = i;
				data->level.doors[door_count][1] = j;
				data->level.doors[door_count][2] = 1;
				door_count++;
			}
			j++;
		}
		i++;
	}
}

bool	init_door_map(t_data *data)
{
	int	i;

	data->level.doors = ft_calloc(sizeof(int *), data->level.door_count);
	if (data->level.doors == NULL)
		return (false);
	i = 0;
	while (i < data->level.door_count)
	{
		data->level.doors[i] = ft_calloc(sizeof(int), 4);
		if (data->level.doors[i] == NULL)
			return (false);
		i++;
	}
	return (true);
}
