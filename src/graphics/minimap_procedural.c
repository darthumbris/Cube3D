/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_procedural.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 14:55:45 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/12 14:59:20 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//checks if a wall tile is a corner
bool	check_corner(t_data *data, int y, int x)
{
	int					i;
	int					count;
	const t_vector_int	coords[4] = {\
	{.x = x - 1, .y = y}, \
	{.x = x + 1, .y = y}, \
	{.x = x, .y = y - 1}, \
	{.x = x, .y = y + 1}};

	i = 0;
	count = 0;
	while (i < 4)
	{
		if (!(coords[i].x < 0 || coords[i].x >= data->level.map_w || \
		coords[i].y < 0 || coords[i].y >= data->level.map_h) && \
		data->level.wall_map[coords[i].y][coords[i].x] == true)
			count++;
		i++;
	}
	return (count >= 2);
}

//loops through the map to fill corner tiles
void	fill_corners(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->level.map[i])
	{
		j = 0;
		while (j < data->level.map_w)
		{
			if (is_wall_tile(data->level.map[i][j]) && check_corner(data, i, j))
				data->level.wall_map[i][j] = true;
			j++;
		}
		i++;
	}
}

//checks if door is opening/open
bool	is_door_opening(t_data *data, int y, int x)
{
	int				i;

	i = 0;
	while (i < data->level.door_count)
	{
		if ((data->doors[i].state == OPENING || \
			data->doors[i].state == OPEN) && data->doors[i].y == y && \
			data->doors[i].x == x)
			return (true);
		i++;
	}
	i = 0;
	while (i < data->level.secret_count)
	{
		if ((data->secrets[i].state == OPENING || \
			data->secrets[i].state == OPEN) && data->secrets[i].y == y && \
			data->secrets[i].x == x)
			return (true);
		i++;
	}
	return (false);
}

//checks wall tiles with simple floodfill
void	check_for_walls(t_data *data, t_vector_int c)
{
	if (is_wall_tile(data->level.map[c.y][c.x]) || ((is_door_tile
	(data->level.map[c.y][c.x]) || is_secret_tile(data->level.map[c.y][c.x])) \
	&& !is_door_opening(data, c.y, c.x)))
		data->level.wall_map[c.y][c.x] = true;
	else if (data->level.wall_map[c.y][c.x] == 0)
	{
		data->level.wall_map[c.y][c.x] = 2;
		if (c.y - 1 > -1)
			check_for_walls(data, (t_vector_int){.x = c.x, .y = c.y - 1});
		if (c.y + 1 < data->level.map_h)
			check_for_walls(data, (t_vector_int){.x = c.x, .y = c.y + 1});
		if (c.x - 1 > -1)
			check_for_walls(data, (t_vector_int){.x = c.x - 1, .y = c.y});
		if (c.x + 1 < data->level.map_w)
			check_for_walls(data, (t_vector_int){.x = c.x + 1, .y = c.y});
	}
	if ((is_door_tile(data->level.map[c.y][c.x]) || is_secret_tile
		(data->level.map[c.y][c.x])) && is_door_opening(data, c.y, c.x))
		data->level.wall_map[c.y][c.x] = 2;
}

//removes previously checked tiles from wall map;
void	clean_wall_map(t_data *data)
{
	int	**map;
	int	i;
	int	j;

	i = 0;
	map = data->level.wall_map;
	while (map[i])
	{
		j = 0;
		while (j < data->level.map_w)
		{	
			if (map[i][j] == 2)
				map[i][j] = 0;
			j++;
		}
		i++;
	}

}
