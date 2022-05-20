/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sound.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 13:47:57 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/20 12:12:31 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	play_sound(t_data *data, int type)
{
	data->sound.cur = type;
	ma_sound_start(data->sound.soundtrack[type]);
}

void	soundtrack(t_data *data)
{
	if (ma_sound_at_end(data->sound.soundtrack[data->sound.cur]))
	{
		if (data->sound.cur == data->sound.length - 1)
			play_sound(data, 0);
		else
			play_sound(data, data->sound.cur + 1);
	}
	if (ma_sound_at_end(&data->sound.sfx_g))
		ma_sound_set_volume(&data->sound.sfx_g, 1.0);
}

static char	**read_sound_config(void)
{
	char	buf[10001];
	char	*config;
	int		bytes_read;
	int		fd;
	char	**config_split;

	bytes_read = 1;
	config = NULL;
	fd = open("config/sound_config.txt", O_RDONLY);
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
		config = ft_strjoin(config, buf);
	}
	config_split = ft_split(config, '\n');
	free(config);
	return (config_split);
}

static bool	store_sound(t_data *data, char *path, int i)
{
	data->sound.soundtrack[i] = malloc(sizeof(ma_sound));
	if (!data->sound.soundtrack[i] || \
	ma_sound_init_from_file(&data->sound.engine, path, 0, \
	&data->sound.music_g, NULL, data->sound.soundtrack[i]) != MA_SUCCESS)
		return (false);
	return (true);
}

bool	sound_init(t_data *data)
{
	char	**config;
	int		i;

	if (ma_engine_init(NULL, &data->sound.engine) != MA_SUCCESS || \
	ma_sound_group_init(&data->sound.engine, 0, NULL, &data->sound.music_g) \
	!= MA_SUCCESS || ma_sound_group_init(&data->sound.engine, 0, \
	NULL, &data->sound.sfx_g) != MA_SUCCESS)
		return (false);
	i = 0;
	config = read_sound_config();
	while (config[i] && ft_strncmp(config[i], "---", 3) != 0)
		i++;
	data->sound.soundtrack = malloc(sizeof(ma_sound *) * (i + 1));
	if (!data->sound.soundtrack)
		return (false);
	data->sound.length = i;
	i = 0;
	while (config[i] && ft_strncmp(config[i], "---", 3) != 0)
	{
		if (!store_sound(data, config[i], i))
			return (false);
		i++;
	}
	arr_cleanup(config);
	return (true);
}
