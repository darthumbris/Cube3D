/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/23 13:54:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

//loops through the configs
bool	parse_types(char **upmap, t_data *data)
{
	int	i;

	i = 0;
	if (data->bonus)
	{
		while (upmap[i] && i < data->number_of_textures + 2 \
		&& upmap[i][0] != ' ' && !ft_isdigit(upmap[i][0]))
		{
			if (mapjmptable(upmap[i], data) == false)
				return (error_msg("Map is misconfigured"));
			i++;
		}
	}
	else
	{
		while (upmap[i] && i <= SOUTH + 2)
		{
			if (mapjmptable(upmap[i], data) == false)
				return (error_msg("Map is misconfigured"));
			i++;
		}
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
			if (is_player_tile(map[i][j]))
				return ((t_vector_double){.x = j + 0.5, .y = i + 0.5});
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
	data->cam.dir.x = 0;
	data->cam.dir.y = 0;
	if (c == 'N')
		data->cam.dir.y = -1.0;
	else if (c == 'S')
		data->cam.dir.y = +1.0;
	else if (c == 'W')
		data->cam.dir.x = -1.0;
	else
		data->cam.dir.x = +1.0;
	data->cam.plane.x = tan(M_PI_2 * FOV / 180.0) * -data->cam.dir.y;
	data->cam.plane.y = tan(M_PI_2 * FOV / 180.0) * data->cam.dir.x;
}

static void	make_square_map(t_data *data, char **upmap)
{
	int			i;
	const int	h = data->level.map_h;
	const int	w = data->level.map_w;

	i = 0;
	if (!upmap)
		return ;
	data->level.map = (char **)malloc(sizeof(char *) * (h + 1));
	data->level.wall_map = (int **)malloc(sizeof(int *) * (h + 1));
	if (!data->level.map || !data->level.wall_map)
		exit(1);
	while (*upmap)
	{
		data->level.map[i] = malloc(sizeof(char) * (w + 1));
		data->level.wall_map[i] = ft_calloc(sizeof(int), (w + 1));
		if (!data->level.map[i] || !data->level.wall_map[i])
			exit(1);
		ft_memset(data->level.map[i], 32, w);
		data->level.map[i][w] = 0;
		ft_memcpy(data->level.map[i], *upmap, ft_strlen(*upmap));
		upmap++;
		i++;
	}
	data->level.map[i] = NULL;
	data->level.wall_map[i] = NULL;
}

bool	parse_input(char **argv, t_data *data)
{
	char	**upmap;
	int		fd;

	upmap = NULL;
	if (ft_strlen(argv[1]) < 4 || \
		ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
		return (error_msg("Incorrect map file type"));
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 10), "_bonus.cub", 10) == 0)
		data->bonus = true;
	fd = open(argv[1], O_RDONLY);
	upmap = readmap(fd, upmap);
	data->level.unparsed = upmap;
	close(fd);
	if (!upmap || parse_types(upmap, data) == false || checktypes(data))
		return (false);
	make_square_map(data, parse_map(upmap, data));
	data->cam.pos = getplayerpos(data->level.map);
	if (!data->level.map || \
		data->cam.pos.x == -1 || data->cam.pos.y == -1)
		return (false);
	setplayerdir(data->level.map, data->cam.pos, data);
	set_sprite_positions(data->level.map, data);
	return (true);
}
