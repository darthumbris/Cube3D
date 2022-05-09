/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doormap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 15:52:39 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 15:30:37 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_door_direction(t_data *data, int i, int j, int door)
{
	if (i > 0 && is_wall_tile(data->level.map[i - 1][j]))
		data->doors[door].direction = EAST_WEST;
	else
		data->doors[door].direction = NORTH_SOUTH;
}

void	init_doors(t_data *data)
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
				set_door_direction(data, i, j, door_count);
				door_count++;
			}
			j++;
		}
		i++;
	}
}

static void	set_secret_direction(t_data *data, int i, int j, int door)
{
	const char	c = data->level.map[i][j];

	if (c == '<' || c == '{')
		data->secrets[door].direction = S_WEST;
	else if (c == '^')
		data->secrets[door].direction = S_NORTH;
	else if (c == '_')
		data->secrets[door].direction = S_SOUTH;
	else
		data->secrets[door].direction = S_EAST;
}

void	init_secrets(t_data *data)
{
	int	i;
	int	j;
	int	secrets;

	i = 0;
	secrets = 0;
	while (data->level.map[i])
	{
		j = 0;
		while (data->level.map[i][j])
		{
			if (is_secret_tile(data->level.map[i][j]))
			{
				data->secrets[secrets].x = j;
				data->secrets[secrets].y = i;
				data->secrets[secrets].type = data->level.map[i][j];
				data->secrets[secrets].state = CLOSED;
				data->secrets[secrets].s_timer = 0.0;
				set_secret_direction(data, i, j, secrets);
				secrets++;
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
	data->secrets = ft_calloc(sizeof(t_secrets), data->level.secret_count);
	if (data->secrets == NULL)
		return (false);
	return (true);
}
