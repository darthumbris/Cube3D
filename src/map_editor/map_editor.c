/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_editor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 14:55:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/27 15:00:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

uint8_t	***create_map_planes(t_data *data)
{
	uint8_t	***map;
	int		i;
	int		j;

	i = 0;
	map = ft_calloc(sizeof(uint8_t **), data->level.map_h);
	while (i < data->level.map_h)
	{
		map[i] = ft_calloc(sizeof(uint8_t *), data->level.map_w);
		j = 0;
		while (j < data->level.map_w)
		{
			map[i][j] = ft_calloc(sizeof(uint8_t), 3);
			j++;
		}
		i++;
	}
	return (map);
}

void	fill_map(t_data *data)
{
	int				i;
	int				plane;
	t_vector_int	pos;	
	char			**map_tiles;
	char			***cords;

	map_tiles = ft_split(data->level.tempthing[3], ',');
	i = 0;
	while (map_tiles[i])
		i++;
	cords = ft_calloc(sizeof(char **), i + 1);
	i = 0;
	while (map_tiles[i])
	{
		cords[i] = ft_split(map_tiles[i], ' ');
		pos.x = ft_atoi(cords[i][0]);
		pos.y = ft_atoi(cords[i][1]);
		plane = ft_atoi(cords[i][2]);
		if (ft_atoi(cords[i][3]) != 0)
			data->level.map_planes[pos.y][pos.x][plane] = ft_atoi(cords[i][3]);
		else
			data->level.map_planes[pos.y][pos.x][plane] = 106;
		i++;
	}
}

void	load_map(t_data *data)
{
	int		i;
	int		fd;
	char	**temp = NULL;

	fd = open("./maps/new_map_format.cub", O_RDONLY);
	data->level.tempthing = readmap(fd, temp);
	data->level.map_w = ft_atoi(data->level.tempthing[0]);
	i = 0;
	while (data->level.tempthing[0][i] && data->level.tempthing[0][i] != ' ')
		i++;
	data->level.map_h = ft_atoi(data->level.tempthing[0] + i);
	data->level.grid_size = ft_atoi(data->level.tempthing[1]);
	data->level.texture_paths_file = ft_strdup(data->level.tempthing[2]);
	data->level.map_planes = create_map_planes(data);
	fill_map(data);
}
