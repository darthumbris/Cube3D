/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:20:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/26 16:16:57 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//checks if types were parsed correctly
bool	checktypes(t_data *data)
{
	int	i;

	i = 0;
	if (data->bonus)
	{
		while (i <= DOG_SPRITE)
		{
			if (data->level.paths.path[i] == NULL)
				return (true);
			i++;
		}
	}
	else
	{
		while (i <= SOUTH)
		{
			if (data->level.paths.path[i] == NULL)
				return (true);
			i++;
		}
	}
	return (false);
}

//jump table for storing config settings
bool	mapjmptable(char *line, t_data *data)
{
	int						i;
	static const t_values	jmpt[] = {
	{.str = "NO", .kind = NORTH},
	{.str = "SO", .kind = SOUTH},
	{.str = "WE", .kind = WEST},
	{.str = "EA", .kind = EAST},
	{.str = "FL", .kind = FLOOR},
	{.str = "CL", .kind = CEILING},
	{.str = "DO", .kind = DOOR},
	{.str = "S0", .kind = SPRITE_0},
	{.str = "S1", .kind = SPRITE_1},
	{.str = "S2", .kind = SPRITE_2},
	{.str = "S3", .kind = SPRITE_3},
	{.str = "S4", .kind = SPRITE_4},
	{.str = "W1", .kind = WALL_1},
	{.str = "W2", .kind = WALL_2},
	{.str = "W3", .kind = WALL_3},
	{.str = "HI", .kind = HIDDEN_WALL},
	{.str = "DS", .kind = DOG_SPRITE},
	};

	i = 0;
	while ((i < (int)(sizeof(jmpt) / sizeof(t_values))))
	{
		if (ft_strncmp(line, jmpt[i].str, 2) == 0)
			return (store_path(line, data, jmpt[i].kind), true);
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
			while (*(map + 1) && *map != '\n')
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
		if (bread == -1)
			return (NULL);
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
