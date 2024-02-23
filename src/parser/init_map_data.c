/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_map_data.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 13:52:07 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/30 15:12:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_size_config(char **config)
{
	int	size;

	size = 0;
	if (!config)
		return (-1);
	while (config[size])
		size++;
	return (size);
}

static bool	init_episodes(t_data *data, int i, char *ep_file)
{
	char	buf[10001];
	char	*episode;
	int		bytes_read;
	int		fd;

	bytes_read = 1;
	episode = NULL;
	printf("opening epfile: %s\n", ep_file);
	fd = open(ep_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("Failed to open episode file"));
	free(ep_file);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (error_msg("Failed to read episode file"));
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		episode = ft_strjoin(episode, buf);
	}
	data->eps.map_names[i] = ft_split(episode, '\n');
	free(episode);
	return (true);
}

static bool	init_map_names(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->eps.episode_cnt)
	{
		init_episodes(data, i, ft_strjoin_r("maps/", \
				data->eps.episode_names[i]));
		if (data->eps.map_names[i] == NULL)
			return (error_msg("Malloc failure"));
		i++;
	}
	return (true);
}

static bool	set_map_config_data(t_data *data)
{
	data->eps.episode_cnt = get_size_config(data->eps.episode_names);
	data->eps.eps_map_cnt = ft_calloc(sizeof(int), data->eps.episode_cnt);
	data->eps.map_names = ft_calloc(sizeof(char **), data->eps.episode_cnt + 1);
	if (data->eps.eps_map_cnt == NULL || data->eps.map_names == NULL)
		return (error_msg("Malloc failure"));
	return (init_map_names(data));
}

bool	init_map_data(t_data *data)
{
	char	buf[10001];
	char	*map_config;
	int		bytes_read;
	int		fd;

	bytes_read = 1;
	map_config = NULL;
	fd = open("maps/episodes.wf3", O_RDONLY);
	if (fd == -1)
		return (error_msg("Failed to open map config file"));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (error_msg("Failed to read map config file"));
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		map_config = ft_strjoin(map_config, buf);
	}
	data->eps.episode_names = ft_split(map_config, '\n');
	free(map_config);
	return (set_map_config_data(data));
}
