/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_0.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 12:08:29 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 14:27:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_vector_double	get_closest_line_point(t_line *line, \
			t_vector_double pos)
{
	t_vector_double	res;

	res.x = (line->b * (line->b * pos.x - line->a * pos.y) - \
		line->a * line->c) / (line->a * line->a + line->b * line->b);
	res.y = (line->a * (-line->b * pos.x + line->a * pos.y) - \
		line->b * line->c) / (line->a * line->a + line->b * line->b);
	return (res);
}

bool	is_vision_blocked(t_vector_double player_pos, \
	t_sprite *enemy, t_data *data)
{
	t_vector_double	ray;
	t_vector_double	dir;
	double			dist;
	char			c;

	ray = enemy->map_pos;
	dir.x = (player_pos.x - enemy->map_pos.x) / enemy->dist;
	dir.y = (player_pos.y - enemy->map_pos.y) / enemy->dist;
	dist = 0;
	while (dist < enemy->dist)
	{
		ray.x = enemy->map_pos.x + dist * dir.x;
		ray.y = enemy->map_pos.y + dist * dir.y;
		c = data->level.map[(int)ray.y][(int)ray.x];
		if (is_wall_tile(c) || door_check(data, ray))
			return (true);
		dist += 0.5;
	}
	return (false);
}

bool	player_oustide_viewing_cone(t_data *data, t_sprite *enemy)
{
	t_vector_double	intersect;
	double			max_view_fov;
	double			view_fov;

	if (enemy->en_dat.player_detected)
		rotate_enemy(data, enemy);
	data->caster.dcas.ray.p_0.x = enemy->map_pos.x;
	data->caster.dcas.ray.p_0.y = enemy->map_pos.y;
	data->caster.dcas.ray.p_1.x = enemy->map_pos.x + enemy->en_dat.dir.x;
	data->caster.dcas.ray.p_1.y = enemy->map_pos.y + enemy->en_dat.dir.y;
	segment_to_line(&data->caster.dcas.ray, &data->caster.dcas.l1);
	intersect = get_closest_line_point(&data->caster.dcas.l1, data->cam.pos);
	if (enemy->en_dat.dir.x * (intersect.x - enemy->map_pos.x) + \
		enemy->en_dat.dir.y * (intersect.y - enemy->map_pos.y) < 0)
		return (true);
	max_view_fov = sqrt(pow(enemy->map_pos.x - intersect.x, 2) + \
					pow(enemy->map_pos.y - intersect.y, 2));
	view_fov = sqrt(pow(intersect.x - data->cam.pos.x, 2) + \
				pow(intersect.y - data->cam.pos.y, 2));
	return (view_fov > max_view_fov || is_vision_blocked
		(data->cam.pos, enemy, data) || \
		enemy->dist > ENEMY_RANGE);
}

void	rotate_enemy(t_data *data, t_sprite *enemy)
{
	enemy->en_dat.dir.x = (data->cam.pos.x - enemy->map_pos.x) / enemy->dist;
	enemy->en_dat.dir.y = (data->cam.pos.y - enemy->map_pos.y) / enemy->dist;
}

//TODO make the sound play at certain volume
void	check_for_player(t_data *data, t_sprite *enemy)
{
	if (player_oustide_viewing_cone(data, enemy))
		return ;
	if (enemy->en_dat.state == ATTACKING)
	{
		enemy->en_dat.state = TRACKING;
		return ;
	}
	enemy->en_dat.state = TRACKING;
	if (!enemy->en_dat.played_sound && enemy->kind == GUARD)
		play_sound_vol(data, "./assets/wav_files/sounds/grdsit2.wav", \
			enemy->dist);
	else if (!enemy->en_dat.played_sound && enemy->kind == DOG)
		play_sound_vol(data, "./assets/wav_files/sounds/dogsit.wav", \
			enemy->dist);
}
