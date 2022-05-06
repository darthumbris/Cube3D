/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:51:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 15:45:24 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

double	sprite_dist(t_vector_double start, t_vector_double end)
{
	end.x -= start.x;
	end.y -= start.y;
	return (end.x * end.x + end.y * end.y);
}

static void	swap_sprite(t_sprite_lst **prev, t_sprite_lst *last)
{
	t_sprite_lst	*temp;

	temp = *prev;
	*prev = last->next;
	temp->next = last->next->next;
	(*prev)->next = temp;
}

void	sort_sprites(t_data *data, t_sprite_lst **begin)
{
	t_sprite_lst	*last;
	t_sprite_lst	*prev;
	double			dist1;
	double			dist2;

	prev = NULL;
	last = *begin;
	while (last && last->next)
	{
		dist1 = sprite_dist(last->sprite_data.map_pos, data->cam.pos);
		dist2 = sprite_dist(last->next->sprite_data.map_pos, data->cam.pos);
		if (dist1 < dist2)
		{
			if (prev == NULL)
				swap_sprite(begin, last);
			else
				swap_sprite(&(prev->next), last);
			last = *begin;
			last->sprite_data.dist = dist1;
			prev = NULL;
		}
		else
		{
			prev = last;
			last = last->next;
			last->sprite_data.dist = dist2;
		}
	}
}
