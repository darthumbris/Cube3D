/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:20:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/18 15:46:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//checks if types were parsed correctly
bool	checktypes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->bonus)
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

static bool	bonus_paths(char *line, t_data *data)
{
	if (ft_strncmp(line, "HU", 2) == 0)
		return (store_path(line, data, HUD_MAIN), true);
	else if (ft_strncmp(line, "HN", 2) == 0)
		return (store_path(line, data, HUD_NUMBERS), true);
	else if (ft_strncmp(line, "FH", 2) == 0)
		return (store_path(line, data, HUD_FACES), true);
	else if (ft_strncmp(line, "DF", 2) == 0)
		return (store_path(line, data, DOOR_FRAME), true);
	else if (ft_strncmp(line, "TD", 2) == 0)
		return (store_path(line, data, SPRITESHEET_DOG), true);
	else if (ft_strncmp(line, "TG", 2) == 0)
		return (store_path(line, data, SPRITESHEET_GUARD), true);
	else if (ft_strncmp(line, "F2", 2) == 0)
		return (store_path(line, data, ELEVATOR_UP), true);
	return (bonus_weapons(line, data));
}

//jump table for storing config settings
bool	mapjmptable(char *line, t_data *data)
{
	int						i;

	i = 0;
	while (i < data->config.size)
	{
		if (ft_strncmp(line, data->config.dat[i].key, 2) == 0)
			return (store_path(line, data, i), true);
		i++;
	}
	if (ft_strncmp(line, "F ", 2) == 0)
		return (color_store(line, data, 0), true);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (color_store(line, data, 1), true);
	else
		return (bonus_paths(line, data));
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
	int		bytes_read;

	bytes_read = 1;
	map = NULL;
	if (fd == -1)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (NULL);
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	if (checkmap(map))
		return (NULL);
	temp = ft_split(map, '\n');
	free(map);
	return (temp);
}
