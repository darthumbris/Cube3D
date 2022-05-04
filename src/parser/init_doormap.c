/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doormap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 15:52:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/04 09:20:28 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_door_type(char c)
{
	if (c == 'D')
		return (DOOR_CLOSED);
	else if (c == 'h')
		return (HIDDEN_CLOSED);
	else
		return (HIDDEN_2_CLOSED);
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
				data->level.doors[door_count][0] = i;
				data->level.doors[door_count][1] = j;
				data->level.doors[door_count][2] = get_door_type \
					(data->level.map[i][j]);
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
