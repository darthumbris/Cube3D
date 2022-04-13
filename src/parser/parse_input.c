/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 14:15:21 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/13 15:44:14 by pvan-dij      ########   odam.nl         */
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
}

bool	parse_input(char **argv, t_data *data)
{
	int		fd;
	int		i;
	char	**upmap; //unparsed map

	i = 1;
	upmap = NULL;
	if (ft_strlen(argv[1]) < 4 || \
		ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4) != 0)
		return (false);
	fd = open(argv[1], O_RDONLY);
	upmap = readmap(fd, upmap);
	if (!upmap)
		return (false);
	close(fd);
	if (parse_types(upmap, data) == false)
		return (false);

	for (int i = 0; upmap[i]; i++)
		printf("%s\n", upmap[i]);
	printf("-------------------------------------\n");
	printf("%s\n", data->level.no_texture_path);
	printf("%s\n", data->level.so_texture_path);
	printf("%s\n", data->level.we_texture_path);
	printf("%s\n", data->level.ea_texture_path);
	printf("%d\n", data->level.floor_color);
	printf("%d\n", data->level.ceiling_color);

	data->level.no_texture_path = strdup("assets/wood.png");
	if (data->level.no_texture_path == NULL)
		return (false);
	return (true);
}
