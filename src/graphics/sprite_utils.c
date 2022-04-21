/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:51:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/21 13:54:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static double	sprite_dist(t_vector_double start, t_vector_double end)
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

	prev = NULL;
	last = *begin;
	while (last && last->next)
	{
		if (sprite_dist(data->cam.pos, last->sprite_data.map_pos) < \
			sprite_dist(data->cam.pos, last->next->sprite_data.map_pos))
		{
			if (!prev)
				swap_sprite(begin, last);
			else
				swap_sprite(&(prev->next), last);
			last = *begin;
			prev = NULL;
		}
		else
		{
			prev = last;
			last = last->next;
		}
	}
}

void	set_sprites(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->level.number_of_sprites)
	{
		data->spr_cast.sprite_order[i] = i;
		data->spr_cast.sprite_distance[i] = \
			((data->cam.pos.x - data->sprite[i].map_pos.x) * \
			(data->cam.pos.x - data->sprite[i].map_pos.x) + \
			(data->cam.pos.y - data->sprite[i].map_pos.y) * \
			(data->cam.pos.y - data->sprite[i].map_pos.y));
		i++;
	}
}
