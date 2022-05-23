/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_score_screen_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 12:25:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/23 13:46:26 by shoogenb      ########   odam.nl         */
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
	if (kill_ratio < 0)
		kill_ratio = 0;
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (KILL_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	if (kill_ratio > 99)
		draw_single_nbr_score(data, kill_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (kill_ratio > 9)
		draw_single_nbr_score(data, kill_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, kill_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
	if (kill_ratio == 100)
		data->player.bonus_score += 10000;
}

void	draw_treasure_ratio(t_data *data)
{
	int				treasure_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	treasure_ratio = (int)(100 * (data->player.treasure_found / \
				(double)data->level.treasure_count));
	if (treasure_ratio < 0)
		treasure_ratio = 0;
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (TREASURE_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	if (treasure_ratio > 99)
		draw_single_nbr_score(data, treasure_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (treasure_ratio > 9)
		draw_single_nbr_score(data, treasure_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, treasure_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
	if (treasure_ratio == 100)
		data->player.bonus_score += 10000;
}

void	draw_secrets_ratio(t_data *data)
{
	int				secrets_ratio;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	secrets_ratio = (int)(100 * (data->player.secrets_found / \
				(double)data->level.secret_count));
	if (secrets_ratio < 0)
		secrets_ratio = 0;
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (SECRET_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	if (secrets_ratio > 99)
		draw_single_nbr_score(data, secrets_ratio / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (secrets_ratio > 9)
		draw_single_nbr_score(data, secrets_ratio / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, secrets_ratio, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_percentage(data, pos, score_nbr);
	if (secrets_ratio == 100)
		data->player.bonus_score += 10000;
}

void	draw_time(t_data *data, int time[2])
{
	t_vector_int	pos;
	int				par_y;
	mlx_texture_t	*score_nbr;

	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (TIME_POS_Y * data->hud.scale);
	par_y = data->mlx.mlx_handle->height - (PAR_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	draw_single_nbr_score(data, time[0] / 10, pos, score_nbr);
	draw_single_nbr_score(data, 0, (t_vector_int){pos.x, par_y}, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, 1, (t_vector_int){pos.x, par_y}, score_nbr);
	draw_single_nbr_score(data, time[0], pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_colon(data, pos, score_nbr);
	draw_colon(data, (t_vector_int){pos.x, par_y}, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, time[1] / 10, pos, score_nbr);
	draw_single_nbr_score(data, 3, (t_vector_int){pos.x, par_y}, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, time[1], pos, score_nbr);
	draw_single_nbr_score(data, 0, (t_vector_int){pos.x, par_y}, score_nbr);
}

void	draw_bonus_score(t_data *data)
{
	int				bonus;
	t_vector_int	pos;
	mlx_texture_t	*score_nbr;

	bonus = data->player.bonus_score;
	pos.x = NBR_STARTPOS_X * data->hud.scale + data->hud.border_width;
	pos.y = data->mlx.mlx_handle->height - (BONUS_POS_Y * data->hud.scale);
	score_nbr = data->mlx.tex.texarr[SCORE_NUMBERS];
	if (bonus > 9999)
		draw_single_nbr_score(data, bonus / 10000, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (bonus > 999)
		draw_single_nbr_score(data, bonus / 1000, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (bonus > 99)
		draw_single_nbr_score(data, bonus / 100, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	if (bonus > 9)
		draw_single_nbr_score(data, bonus / 10, pos, score_nbr);
	pos.x += 14 * data->hud.scale;
	draw_single_nbr_score(data, bonus, pos, score_nbr);
}
