/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_enemy_collision.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 15:58:03 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 16:08:00 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_enemy_kind(int kind)
{
	return (kind == GUARD || kind == DOG);
}

bool	is_enemy_collision(t_data *data, t_vector_double new_pos)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) && \
			lst->sprite_data.state == ALIVE && \
			sprite_dist(lst->sprite_data.map_pos, new_pos) < 1.0)
			return (true);
		lst = lst->next;
	}
	return (false);
}