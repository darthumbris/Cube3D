/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/17 14:27:55 by shoogenb      ########   odam.nl         */
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
	collision->y = enemy->map_pos.y + dir * enemy->en_dat.speed + dir * 0.5;
}

void	set_new_x_pos(t_vector_double *temp_pos, t_vector_double *collision, \
						t_sprite *enemy, int dir)
{
	temp_pos->x = enemy->map_pos.x + dir * enemy->en_dat.speed;
	collision->x = enemy->map_pos.x + dir * enemy->en_dat.speed + dir * 0.5;
}

static void	set_state(t_sprite *enemy, t_data *data)
{
	if (enemy->en_dat.player_detected && \
		((enemy->kind == DOG && enemy->dist < 2) || \
		(enemy->kind == GUARD && enemy->dist < 100)) && \
		enemy->en_dat.state == TRACKING)
	{
		pathfind_to_player(data, enemy);
		if (enemy->en_dat.counter % 10 == 0)
			attack_player(enemy, data);
	}
	else
		pathfind_to_player(data, enemy);
}

//TODO optimize this and have enemies try to move closer
//TODO and also check the rotate thing
void	path_find(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) && \
			lst->sprite_data.en_dat.state == PATROLLING)
			patrol_routine(data, &lst->sprite_data);
		if (delay % 5 == 0 && is_enemy_kind(lst->sprite_data.kind) && \
			(lst->sprite_data.en_dat.state == ALIVE || \
			lst->sprite_data.en_dat.state == PATROLLING))
			check_for_player(data, &lst->sprite_data);
		else if (is_enemy_kind(lst->sprite_data.kind) && \
			lst->sprite_data.en_dat.state == TRACKING)
		{
			track_player(data, &lst->sprite_data);
			set_state(&lst->sprite_data, data);
		}
		lst = lst->next;
		delay++;
	}
	if (delay > 50)
		delay = 0;
}
