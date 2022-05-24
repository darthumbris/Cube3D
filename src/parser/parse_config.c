/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_config.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 10:51:03 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/24 16:11:38 by shoogenb      ########   odam.nl         */
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

static void	set_dat(t_data *data, int i, char **config, char ***config_data)
{
	config_data[i] = ft_split(config[i], ',');
	data->config.dat[i].key = ft_strdup(config_data[i][0]);
	data->config.dat[i].value = config_data[i][1][0];
	data->config.dat[i].kind = i;
	if (config_data[i][2] && config_data[i][3])
	{
		data->config.dat[i].transp_begin.x = ft_atoi(config_data[i][3]);
		data->config.dat[i].transp_begin.y = ft_atoi(config_data[i][4]);
		data->config.dat[i].transp_end.x = ft_atoi(config_data[i][5]);
		data->config.dat[i].transp_end.y = ft_atoi(config_data[i][6]);
	}
	arr_cleanup(config_data[i]);
}

static bool	set_config_data(t_data *data, char **config)
{
	int		size;
	int		i;
	char	***config_data;

	size = get_size_config(config);
	data->config.dat = ft_calloc(sizeof(t_config_data), size);
	config_data = ft_calloc(sizeof(char **), size + 1);
	if (data->config.dat == NULL || config_data == NULL)
		return (error_msg("Malloc failure"));
	config_data[size] = NULL;
	data->config.size = size;
	data->config.size_temp = size;
	i = 0;
	while (i < size)
	{
		set_dat(data, i, config, config_data);
		i++;
	}
	free(config_data);
	arr_cleanup(config);
	return (true);
}

bool	parse_config(t_data *data)
{
	char	buf[10001];
	char	*config;
	int		bytes_read;
	int		fd;
	char	**config_split;

	bytes_read = 1;
	config = NULL;
	fd = open("config/wolfenstein_map_config.txt", O_RDONLY);
	if (fd == -1)
		return (error_msg("Failed to open config file"));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (error_msg("Failed to read config file"));
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		config = ft_strjoin(config, buf);
	}
	config_split = ft_split(config, '\n');
	free(config);
	return (set_config_data(data, config_split));
}
