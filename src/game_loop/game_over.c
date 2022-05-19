/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 12:38:58 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 12:41:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	game_over(t_data *data)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	data->player.end_time = timev.tv_sec;
	draw_score_screen(data);
	draw_kill_ratio(data);
	draw_treasure_ratio(data);
	draw_secrets_ratio(data);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.score_screen, 0, 0);
	data->player.game_over = true;
	printf("diff start and end time: %llu\n", data->player.end_time - data->player.start_time);
}
