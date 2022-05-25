/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_functions2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 10:38:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/25 10:38:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	cleanup_soundtrack(t_data *data)
{
	int	i;

	i = 0;
	ma_sound_group_uninit(&data->sound.music_g);
	ma_sound_group_uninit(&data->sound.sfx_g);
	while (i < data->sound.length)
	{
		ma_sound_uninit(data->sound.soundtrack[i]);
		free(data->sound.soundtrack[i]);
		i++;
	}
	free(data->sound.soundtrack);
	ma_engine_uninit(&data->sound.engine);
}
