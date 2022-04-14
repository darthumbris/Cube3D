/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/14 14:07:16 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

typedef void	(*t_func)(char *line, t_data *data);

typedef struct s_values
{
	char	*str;
	t_func	storemapval;
}	t_values;

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

t_vector_double	getplayerpos(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				map[i][j] = '0';
				return ((t_vector_double){.x = j, .y = i});
			}	
			j++;
		}
		i++;
	}
	return ((t_vector_double){.x = -1, .y = -1});
}

bool	parse_input(char **argv, t_data *data)
{
	int		fd;
	int		i;
	char	**upmap; //unparsed map

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
	if (!data->level.map || \
		data->player.pos.x == -1 || data->player.pos.y == -1)
	{
		printf("not valid\n");
		exit(1);
	}
	for (int i = 0; data->level.map[i]; i++)
		printf("%s\n", data->level.map[i]);
	printf("-------------------------------------\n");
	printf("%s\n", data->level.no_texture_path);
	printf("%s\n", data->level.so_texture_path);
	printf("%s\n", data->level.we_texture_path);
	printf("%s\n", data->level.ea_texture_path);
	printf("%d\n", data->level.floor_color);
	printf("%d\n", data->level.ceiling_color);
	printf("%f-%f\n", data->player.pos.x, data->player.pos.y);


	data->level.no_texture_path = strdup("assets/wood.png");
	if (data->level.no_texture_path == NULL)
		return (false);
	return (true);
}


//typedef union u_IVec2
//{
//	struct
//	{
//		int32_t	x;
//		int32_t	y;
//	};
//	int32_t	raw[2];
//}	t_IVec2;