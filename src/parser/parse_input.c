/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 16:54:24 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

//loops through the 6 configs
bool	parse_types(char **upmap, t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (mapjmptable(upmap[i], data) == false)
			return (false);
		i++;
	}
	return (true);
}

//name
t_vector_double	getplayerpos(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'W' || map[i][j] == 'E')
				return ((t_vector_double){.x = j, .y = i});
			j++;
		}
		i++;
	}
	return ((t_vector_double){.x = -1, .y = -1});
}

void	setplayerdir(char **map, t_vector_double pos, t_data *data)
{
	char	c;

	if (!map || !*map)
		return ;
	c = map[(int)pos.y][(int)pos.x];
	map[(int)pos.y][(int)pos.x] = '0';
	if (c == 'N')
		data->cam.dir.y = -1.0;
	else if (c == 'S')
		data->cam.dir.y = +1.0;
	data->cam.plane.x = tan(M_PI_2 * FOV / 180.0) * -data->cam.dir.y;
	if (c == 'W')
		data->cam.dir.x = -1.0;
	else if (c == 'E')
		data->cam.dir.x = +1.0;
	data->cam.plane.y = tan(M_PI_2 * FOV / 180.0) * data->cam.dir.x;
}

bool	parse_input(char **argv, t_data *data)
{
	char	**upmap; //unparsed map, free later
	int		fd;

	upmap = NULL;
	if (ft_strlen(argv[1]) < 4 || \
		ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
		return (false);
	fd = open(argv[1], O_RDONLY);
	upmap = readmap(fd, upmap);
	close(fd);
	if (!upmap || parse_types(upmap, data) == false)
		return (false);
	data->level.map = parse_map(upmap, data);
	data->player.pos = getplayerpos(data->level.map);
	setplayerdir(data->level.map, data->player.pos, data);
	if (!data->level.map || \
		data->player.pos.x == -1 || data->player.pos.y == -1)
	{
		printf("not valid\n");
		exit(1);
	}
	return (true);
}
