/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 12:38:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/20 11:15:31 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_score_elements(t_data *data)
{
	struct timeval	timev;
	int				time[2];
	int				time_played;

	gettimeofday(&timev, NULL);
	data->player.end_time = timev.tv_sec;
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
	if (data->player.lives == 0 && data->player.health == 0)
		data->player.bonus_score = 0;
	draw_bonus_score(data);
}

void	game_over(t_data *data)
{
	data->player.bonus_score = 0;
	if (data->player.lives >= 0 && data->player.health > 0)
		draw_score_screen(data, data->mlx.tex.texarr[SCORE_SCREEN]);
	else
		draw_score_screen(data, data->mlx.tex.texarr[GAME_OVER]);
	draw_score_elements(data);
	//mlx_image_to_window(data->mlx.mlx_handle, data->mlx.score_screen, 0, 0);
	data->player.game_over = true;
}
