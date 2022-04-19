/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:20:02 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 17:25:24 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//checks if types were parsed correctly
bool	checktypes(t_data *data)
{
	if (data->level.no_texture_path == NULL)
		return (true);
	if (data->level.we_texture_path == NULL)
		return (true);
	if (data->level.ea_texture_path == NULL)
		return (true);
	if (data->level.so_texture_path == NULL)
		return (true);
	return (false);
}

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
