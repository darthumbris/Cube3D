/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_0.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 12:08:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 15:24:13 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_vector_double	get_closest_line_point(t_line *line, double x0, double y0)
{
	t_vector_double	res;

	res.x = (line->b * (line->b * x0 - line->a * y0) - line->a * line->c) / \
		(line->a * line->a + line->b * line->b);
	res.y = (line->a * (-line->b * x0 + line->a * y0) - line->b * line->c) / \
		(line->a * line->a + line->b * line->b);
	return (res);
}

bool	player_oustide_viewing_cone(t_data *data, t_sprite *enemy)
{
	t_vector_double	intersect;
	t_vector_double	shifted_pos;
	double			max_view_fov;
	double			view_fov;

	if (enemy->en_dat.player_detected)
		rotate_enemy(data, enemy);
	data->caster.dcas.ray.p_0.x = enemy->map_pos.x;
	data->caster.dcas.ray.p_0.y = enemy->map_pos.y;
	data->caster.dcas.ray.p_1.x = enemy->map_pos.x + enemy->en_dat.dir.x;
	data->caster.dcas.ray.p_1.y = enemy->map_pos.y + enemy->en_dat.dir.y;
	segment_to_line(&data->caster.dcas.ray, &data->caster.dcas.l1);
	intersect = get_closest_line_point(&data->caster.dcas.l1, data->cam.pos.x, data->cam.pos.y);
	if (enemy->en_dat.dir.x * (intersect.x - enemy->map_pos.x) + \
		enemy->en_dat.dir.y * (intersect.y - enemy->map_pos.y) < 0)
		return (true);
	shifted_pos.x = enemy->map_pos.x - 0.5;
	shifted_pos.y = enemy->map_pos.y - 0.5;
	max_view_fov = sqrt(pow(enemy->map_pos.x - intersect.x, 2) + pow(enemy->map_pos.y - intersect.y, 2));
	view_fov = \
		sqrt(pow(intersect.x - data->cam.pos.x, 2) + pow(intersect.y - data->cam.pos.y, 2));
	return (view_fov > max_view_fov || !is_target_visible(data->cam.pos, shifted_pos, enemy->en_dat.dir, data) || \
		enemy->dist > ENEMY_RANGE);
}

void	rotate_enemy(t_data *data, t_sprite *enemy)
{
	enemy->en_dat.dir.x = (data->cam.pos.x - enemy->map_pos.x) / enemy->dist;
	enemy->en_dat.dir.y = (data->cam.pos.y - enemy->map_pos.y) / enemy->dist;
}

void	check_for_player(t_data *data, t_sprite *enemy)
{
	double	volume;

	if (player_oustide_viewing_cone(data, enemy))
		return ;
	if (enemy->en_dat.state == ATTACKING)
	{
		enemy->en_dat.state = TRACKING;
		return ;
	}
	enemy->en_dat.state = TRACKING;
	//printf("set state to tracking\n");
	volume = 100.0 - sqrt(enemy->dist) * 3.0;
	if (volume < 0)
		volume = 0;
	//play sound at cetain volume
	if (!enemy->en_dat.played_sound && enemy->kind == GUARD)
		ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/grdsit2.wav", &data->sound.sfx);
	else if (!enemy->en_dat.played_sound && enemy->kind == DOG)
		ma_engine_play_sound(&data->sound.engine, "./assets/wav_files/sounds/dogsit.wav", &data->sound.sfx);
}

void	alert_neighbouring_enemies(t_data *data, t_sprite *enemy)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind))
		{
			if (sqrt(pow(lst->sprite_data.map_pos.x - enemy->map_pos.x, 2) + \
				pow(lst->sprite_data.map_pos.y - enemy->map_pos.y, 2)) \
				<= ENEMY_WARN_DIST)
				track_player(data, &lst->sprite_data);
		}
		lst = lst->next;
	}
}

void	track_player(t_data *data, t_sprite *enemy)
{
	if (enemy->en_dat.player_detected == false)
	{
		enemy->en_dat.player_detected = true;
		alert_neighbouring_enemies(data, enemy);
	}
}
