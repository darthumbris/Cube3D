/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/20 09:42:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_out_of_bounds(t_vector_double new_pos, t_data *data)
{
	return (new_pos.x < 0 || new_pos.x > data->level.map_w || \
		new_pos.y < 0 || new_pos.y > data->level.map_h);
}

void	set_new_y_pos(t_vector_double *temp_pos, t_vector_double *collision, \
						t_sprite *enemy, int dir)
{
	temp_pos->y = enemy->map_pos.y + dir * enemy->en_dat.speed;
	collision->y = enemy->map_pos.y + dir * enemy->en_dat.speed + dir * 0.3;
}

void	set_new_x_pos(t_vector_double *temp_pos, t_vector_double *collision, \
						t_sprite *enemy, int dir)
{
	temp_pos->x = enemy->map_pos.x + dir * enemy->en_dat.speed;
	collision->x = enemy->map_pos.x + dir * enemy->en_dat.speed + dir * 0.3;
}

static void	set_state(t_sprite *enemy, t_data *data, int kind)
{
	if (enemy->en_dat.player_detected && \
		((is_dog(kind) && enemy->dist < 2) || \
		(is_guard(kind) && enemy->dist < 100)))
	{
		if (enemy->en_dat.last_attack % 2 == 0 && is_guard(kind))
			pathfind_to_player(data, enemy);
		enemy->en_dat.last_attack++;
		if (enemy->en_dat.last_attack > 50)
			enemy->en_dat.last_attack = 0;
		if (enemy->en_dat.last_attack % 45 == 0 && is_guard(kind))
			attack_player(enemy, data);
		else if (enemy->en_dat.last_attack % 30 == 0)
			attack_player(enemy, data);
	}
	else if (is_guard(kind) && enemy->dist < 300)
		pathfind_to_player(data, enemy);
	else if (enemy->dist < 250)
		pathind_dog(data, enemy);
}

void	path_find(t_data *data, t_sprite *enemy)
{
	static int		delay = 0;

	if (enemy->en_dat.state == PATROLLING && \
		enemy->dist < 400)
		patrol_routine(data, enemy);
	if (delay % 5 == 0 && (enemy->en_dat.state == ALIVE || \
		enemy->en_dat.state == PATROLLING))
		check_for_player(data, enemy);
	else if (enemy->en_dat.state == TRACKING)
	{
		track_player(data, enemy);
		set_state(enemy, data, enemy->kind);
	}
	delay++;
	if (delay > 50)
		delay = 0;
}
