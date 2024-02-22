/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_editor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 14:55:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 11:39:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

uint8_t	***create_map_planes(t_data *data)
{
	uint8_t	***map;
	int		i;
	int		j;

	i = 0;
	map = ft_calloc(sizeof(uint8_t **), data->level.map_h);
	while (i < data->level.map_h)
	{
		map[i] = ft_calloc(sizeof(uint8_t *), data->level.map_w);
		j = 0;
		while (j < data->level.map_w)
		{
			map[i][j] = ft_calloc(sizeof(uint8_t), 3);
			j++;
		}
		i++;
	}
	return (map);
}

void	fill_map(t_data *data)
{
	int				i;
	int				plane;
	t_vector_int	pos;	
	char			**map_tiles;
	char			***cords;

	map_tiles = ft_split(data->level.tempthing[2], ',');
	i = 0;
	while (map_tiles[i])
		i++;
	cords = ft_calloc(sizeof(char **), i + 1);
	i = 0;
	while (map_tiles[i])
	{
		cords[i] = ft_split(map_tiles[i], ' ');
		pos.x = ft_atoi(cords[i][1]);
		pos.y = ft_atoi(cords[i][0]);
		plane = ft_atoi(cords[i][2]);
		if (ft_atoi(cords[i][3]) != 0)
			data->level.map_planes[pos.y][pos.x][plane] = ft_atoi(cords[i][3]);
		i++;
	}
}

char	**readnewmap(int fd, char **temp)
{
	char	buf[10001];
	char	*map;
	int		bytes_read;

	bytes_read = 1;
	map = NULL;
	if (fd == -1)
		return (map_error_msg("Failed to open map"));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (map_error_msg("Failed to read from map"));
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	temp = ft_split(map, '\n');
	free(map);
	return (temp);
}

//test function
//TODO remove test function
void	print_map(t_data *data)
{
	int	i;
	int	k;
	int	j;

	k = -1;
	while (++k < 3)
	{
		i = -1;
		while (++i < data->level.map_h)
		{
			j = -1;
			while (++j < data->level.map_w)
				printf("%d ", data->level.map_planes[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
}

void	load_map(t_data *data)
{
	int		i;
	int		fd;
	char	**temp;

	temp = NULL;
	fd = open("./saves/test1.cub", O_RDONLY);
	data->level.tempthing = readnewmap(fd, temp);
	data->level.map_w = ft_atoi(data->level.tempthing[0]);
	i = 0;
	while (data->level.tempthing[0][i] && data->level.tempthing[0][i] != ' ')
		i++;
	data->level.map_h = ft_atoi(data->level.tempthing[0] + i);
	data->level.grid_size = ft_atoi(data->level.tempthing[1]);
	data->level.map_planes = create_map_planes(data);
	fill_map(data);
	print_map(data);
	if (init_level(data) == false)
	{
		printf("Error in loading map\n");
		exit(1);
	}
	//TODO before starting this loop init player and level etc. and destroy images?
	mlx_key_hook(data->mlx.mlx_handle, key_handler, data);
	mlx_loop_hook(data->mlx.mlx_handle, game_loop, data);
}
