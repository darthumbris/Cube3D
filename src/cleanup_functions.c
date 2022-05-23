/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 12:32:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/23 13:47:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	arr_cleanup(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	cleanup_config(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.size)
	{
		free(data->config.dat[i].key);
		i++;
	}
	free(data->config.dat);
}

void	cleanup_data(t_data *data)
{
	if (data->bonus)
	{
		clear_sprite_lst(&data->sprite_lst);
		if (data->doors)
			free(data->doors);
		if (data->secrets)
			free(data->secrets);
	}
	arr_cleanup(data->level.unparsed);
	arr_cleanup(data->level.map);
	if (data->config.dat)
		cleanup_config(data);
}
