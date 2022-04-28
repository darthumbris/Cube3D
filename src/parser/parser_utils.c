/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:20:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/28 15:14:45 by shoogenb      ########   odam.nl         */
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
		while (i <= data->number_of_textures)
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
	{.str = "NO", .kind = NORTH, store_path},
	{.str = "SO", .kind = SOUTH, store_path},
	{.str = "WE", .kind = WEST, store_path},
	{.str = "EA", .kind = EAST, store_path},
	{.str = "FL", .kind = FLOOR, store_path},
	{.str = "CL", .kind = CEILING, store_path},
	{.str = "W1", .kind = WALL_1, store_path},
	{.str = "W2", .kind = WALL_2, store_path},
	{.str = "W3", .kind = WALL_3, store_path},
	{.str = "W4", .kind = WALL_4, store_path},
	{.str = "W5", .kind = WALL_5, store_path},
	{.str = "W6", .kind = WALL_6, store_path},
	{.str = "W7", .kind = WALL_7, store_path},
	{.str = "W8", .kind = WALL_8, store_path},
	{.str = "W9", .kind = WALL_9, store_path},
	{.str = "S0", .kind = SPRITE_0, store_path},
	{.str = "S1", .kind = SPRITE_1, store_path},
	{.str = "S2", .kind = SPRITE_2, store_path},
	{.str = "S3", .kind = SPRITE_3, store_path},
	{.str = "S4", .kind = SPRITE_4, store_path},
	{.str = "S5", .kind = SPRITE_5, store_path},
	{.str = "S6", .kind = SPRITE_6, store_path},
	{.str = "S7", .kind = SPRITE_7, store_path},
	{.str = "S8", .kind = SPRITE_8, store_path},
	{.str = "S9", .kind = SPRITE_9, store_path},
	{.str = "SA", .kind = SPRITE_10, store_path},
	{.str = "SB", .kind = SPRITE_11, store_path},
	{.str = "SC", .kind = SPRITE_12, store_path},
	{.str = "SD", .kind = SPRITE_13, store_path},
	{.str = "SE", .kind = SPRITE_14, store_path},
	{.str = "SF", .kind = SPRITE_15, store_path},
	{.str = "SG", .kind = SPRITE_16, store_path},
	{.str = "SH", .kind = SPRITE_17, store_path},
	{.str = "SI", .kind = SPRITE_18, store_path},
	{.str = "SJ", .kind = SPRITE_19, store_path},
	{.str = "SK", .kind = SPRITE_20, store_path},
	{.str = "F ", .kind = 0, color_store},
	{.str = "C ", .kind = 1, color_store},
	{.str = "I0", .kind = ITEM_0, store_path},
	{.str = "I1", .kind = ITEM_1, store_path},
	{.str = "I2", .kind = ITEM_2, store_path},
	{.str = "I3", .kind = ITEM_3, store_path},
	{.str = "I4", .kind = ITEM_4, store_path},
	{.str = "I5", .kind = ITEM_5, store_path},
	{.str = "I6", .kind = ITEM_6, store_path},
	{.str = "I7", .kind = ITEM_7, store_path},
	{.str = "I8", .kind = ITEM_8, store_path},
	};

	i = 0;
	while ((i < (int)(sizeof(jmpt) / sizeof(t_values))))
	{
		if (ft_strncmp(line, jmpt[i].str, 2) == 0)
			return (jmpt[i].storemapval(line, data, jmpt[i].kind), true);
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
