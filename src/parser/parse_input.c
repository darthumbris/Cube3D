/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 15:08:57 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

//jump table for storing config settings
bool	mapjmptable(char *line, t_data *data)
{
	int						i;
	static const t_values	jmpt[] = {
	{.str = "NO", .storemapval = no_store},
	{.str = "SO", .storemapval = so_store},
	{.str = "WE", .storemapval = we_store},
	{.str = "EA", .storemapval = ea_store},
	{.str = "F ", .storemapval = f_store},
	{.str = "C ", .storemapval = c_store}
	};

	i = 0;
	while ((i < (int)(sizeof(jmpt) / sizeof(t_values))))
	{
		if (ft_strncmp(line, jmpt[i].str, 2) == 0)
			return (jmpt[i].storemapval(line, data), true);
		i++;
	}
	return (false);
}

//checks for double newlines in map
bool	checkmap(char *map)
{
	if (!map)
		return (true);
	while (*map)
	{
		if (*map == 'F' || *map == 'C')
			while (*map != '\n')
				map++;
		if (ft_isdigit(*map) && *(map + 1) == '\n' && *(map + 2) == '\n')
			return (true);
		map++;
	}
	return (false);
}

//reads in the entire map, copied this from my fdf
char	**readmap(int fd, char **temp)
{
	char	buf[10001];
	char	*map;
	int		bread;

	bread = 1;
	map = NULL;
	if (fd == -1)
		return (NULL);
	while (bread > 0)
	{
		bread = read(fd, buf, 10000);
		buf[bread] = 0;
		if (bread == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	if (checkmap(map))
		return (NULL);
	temp = ft_split(map, '\n');
	free(map);
	return (temp);
}

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
	data->cam.plane.x = tan(PI * FOV) * -data->cam.dir.y;
	if (c == 'W')
		data->cam.dir.x = -1.0;
	else if (c == 'E')
		data->cam.dir.x = +1.0;
	data->cam.plane.y = tan(PI * FOV) * data->cam.dir.x;
}

bool	parse_input(char **argv, t_data *data)
{
	char	**upmap; //unparsed map, free later
	int		fd;
	int		i;

	i = 1;
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
	for (int i = 0; data->level.map[i]; i++)
		printf("%s\n", data->level.map[i]);
	data->caster.framedone = true;
	printf("-------------------------------------\n");
	printf("%s\n", data->level.no_texture_path);
	printf("%s\n", data->level.so_texture_path);
	printf("%s\n", data->level.we_texture_path);
	printf("%s\n", data->level.ea_texture_path);
	printf("%x\n", data->level.floor_color);
	printf("%x\n", data->level.ceiling_color);
	printf("%f-%f\n", data->player.pos.x, data->player.pos.y);


	return (true);
}
