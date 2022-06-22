/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_enemy_collision.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 15:58:03 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:10:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_enemy_kind(int kind)
{
	return (kind == GUARD || kind == DOG);
}

bool	is_guard(int kind)
{
	return (kind == GUARD);
}

bool	is_dog(int kind)
{
	return (kind == DOG);
}

bool	is_enemy_movable(int state)
{
	return (state == STAND || state == CHASE || state == PATROL);
}

bool	is_enemy_collision(t_data *data, t_vector_double new_pos)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) && \
			(is_enemy_movable(lst->sprite_data.en_dat.state) || \
			lst->sprite_data.en_dat.state == ATTACK) && \
			sprite_dist(lst->sprite_data.map_pos, new_pos) < 0.0)
			return (true);
		lst = lst->next;
	}
	return (false);
}
