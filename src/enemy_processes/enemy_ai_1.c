/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 14:09:24 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 14:35:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	check_west_dir(char **map, int j, int i)
{
	int	end;

	if (j - 3 < 0)
		return (false);
	end = j - 3;
	while (j > end)
	{
		if (is_wall_tile(map[i][j]) || \
			is_door_tile(map[i][j]))
			return (false);
		j--;
	}
	return (true);
}

static bool	check_east_dir(char **map, int j, int i, int max_w)
{
	int	end;

	if (j + 3 >= max_w)
		return (false);
	end = j + 3;
	while (j < end)
	{
		if (is_wall_tile(map[i][j]) || \
			is_door_tile(map[i][j]))
			return (false);
		j++;
	}
	return (true);
}

static bool	check_north_dir(char **map, int j, int i)
{
	int	end;

	if (i - 3 < 0)
		return (false);
	end = i - 3;
	while (i > end)
	{
		if (is_wall_tile(map[i][j]) || \
			is_door_tile(map[i][j]))
			return (false);
		i--;
	}
	return (true);
}

static bool	check_south_dir(char **map, int j, int i, int max_h)
{
	int	end;

	if (i + 3 >= max_h)
		return (false);
	end = i + 3;
	while (i < end)
	{
		if (is_wall_tile(map[i][j]) || \
			is_door_tile(map[i][j]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_enemy_patrol(t_data *data, t_sprite *sprite)
{
	int	i;
	int	j;

	i = (int)sprite->map_pos.y;
	j = (int)sprite->map_pos.x;
	if (sprite->en_dat.dir.x == -1.0)
		return (check_west_dir(data->level.map, j, i));
	else if (sprite->en_dat.dir.x == 1.0)
		return (check_east_dir(data->level.map, j, i, data->level.map_w));
	else if (sprite->en_dat.dir.y == -1.0)
		return (check_north_dir(data->level.map, j, i));
	else
		return (check_south_dir(data->level.map, j, i, data->level.map_h));
}
