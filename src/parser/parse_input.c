/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/13 15:10:09 by pvan-dij      ########   odam.nl         */
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

char	**readmap(int fd, char **temp)
{
	char	buf[1000001];
	char	*map;
	int		bread;

	bread = 1;
	map = NULL;
	if (fd == -1)
		return (NULL);
	while (bread > 0)
	{
		bread = read(fd, buf, 1000000);
		buf[bread] = 0;
		if (bread == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	temp = ft_split(map, '\n');
	free(map);
	return (temp);
}

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
	//check bad path/floor-colours
}

bool	parse_input(char **argv, t_data *data)
{
	int		fd;
	int		i;
	char	**upmap; //unparsed map

	i = 1;
	upmap = NULL;
	fd = open(argv[1], O_RDONLY);
	upmap = readmap(fd, upmap);
	if (!upmap)
		return (false);
	close(fd);
	if	(parse_types(upmap, data) == false)
		return (false);

	for (int i = 0; upmap[i]; i++)
		printf("%s\n", upmap[i]);

	data->level.no_texture_path = strdup("assets/wood.png");
	if (data->level.no_texture_path == NULL)
		return (false);
	return (true);
}
