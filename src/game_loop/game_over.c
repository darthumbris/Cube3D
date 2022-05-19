/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 12:38:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 14:09:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	game_over(t_data *data)
{
	struct timeval	timev;
	int				time[2];
	int				time_played;

	data->player.bonus_score = 0;
	gettimeofday(&timev, NULL);
	data->player.end_time = timev.tv_sec;
	draw_score_screen(data);
	draw_kill_ratio(data);
	draw_treasure_ratio(data);
	draw_secrets_ratio(data);
	time_played = data->player.end_time - data->player.start_time;
	time[0] = time_played / 60;
	time[1] = time_played % 60;
	if (time_played < PAR_TIME)
	{
		data->player.bonus_score += ((PAR_TIME - time_played) / 2) * 1000;
		if (time_played % 2 == 1)
			data->player.bonus_score += 500;
	}
	draw_time(data, time);
	draw_bonus_score(data);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.score_screen, 0, 0);
	data->player.game_over = true;
}
