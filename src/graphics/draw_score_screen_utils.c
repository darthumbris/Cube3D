/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_score_screen_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 12:25:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 12:31:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_kill_ratio(t_data *data)
{
	int				kill_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	kill_ratio = (int)(100 * (data->player.enemies_killed / \
				(double)data->level.enemies_count));
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (KILL_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	kill_ratio = 123;
	if (kill_ratio > 99)
		draw_single_nbr_score(data, kill_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (kill_ratio > 9)
		draw_single_nbr_score(data, kill_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, kill_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
}

void	draw_treasure_ratio(t_data *data)
{
	int				treasure_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	treasure_ratio = (int)(100 * (data->player.treasure_found / \
				(double)data->level.treasure_count));
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (TREASURE_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	treasure_ratio = 123;
	if (treasure_ratio > 99)
		draw_single_nbr_score(data, treasure_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (treasure_ratio > 9)
		draw_single_nbr_score(data, treasure_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, treasure_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
}

void	draw_secrets_ratio(t_data *data)
{
	int				secrets_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	secrets_ratio = (int)(100 * (data->player.secrets_found / \
				(double)data->level.secret_count));
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (SECRET_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	secrets_ratio = 123;
	if (secrets_ratio > 99)
		draw_single_nbr_score(data, secrets_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (secrets_ratio > 9)
		draw_single_nbr_score(data, secrets_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, secrets_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
}

void	draw_time(t_data *data)
{
	int				secrets_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	secrets_ratio = (int)(100 * (data->player.secrets_found / \
				(double)data->level.secret_count));
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (SECRET_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	secrets_ratio = 123;
	if (secrets_ratio > 99)
		draw_single_nbr_score(data, secrets_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (secrets_ratio > 9)
		draw_single_nbr_score(data, secrets_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, secrets_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
}
