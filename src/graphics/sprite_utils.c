/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: y: shoogenb <shoogenb@student.codam.nl>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:51:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/20 10:42:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_sprite_kind(char c, t_data *data)
{
	int	i;

	if (is_guard_tile(c))
		return (GUARD);
	else if (is_dog_tile(c))
		return (DOG);
	i = 0;
	if (data->bonus && data->config.size > 5)
		i = 4;
	while (i < data->config.size)
	{
		if (c == data->config.dat[i].value)
			return (i);
		i++;
	}
	return (0);
}

double	sprite_dist(t_vector_double start, t_vector_double end)
{
	end.x -= start.x;
	end.y -= start.y;
	return (end.x * end.x + end.y * end.y);
}

//optimize by swapping pointers instead of data
static void	swap_sprite(t_sprite_lst *lst, t_sprite_lst *lst2)
{
	t_sprite	temp;

	temp = lst->sprite_data;
	lst->sprite_data = lst2->sprite_data;
	lst2->sprite_data = temp;
}

static void	sort_only_valid(t_sprite_lst **current, t_sprite_lst **begin, \
							t_vector_double pos)
{
	double			dist1;
	double			dist2;

	dist1 = sprite_dist((*current)->sprite_data.map_pos, pos);
	dist2 = sprite_dist((*current)->next->sprite_data.map_pos, pos);
	if (dist1 < dist2)
	{
		swap_sprite(*current, (*current)->next);
		(*current)->sprite_data.dist = dist2;
		(*current)->next->sprite_data.dist = dist1;
		(*current) = *begin;
	}
	else
	{
		(*current)->sprite_data.dist = dist1;
		(*current)->next->sprite_data.dist = dist2;
	}
}

void	sort_sprites(t_data *data, t_sprite_lst **begin)
{
	t_sprite_lst	*current;

	current = *begin;
	while (current && current->next)
	{
		if (current->sprite_data.kind)
			sort_only_valid(&current, begin, data->cam.pos);
		current = current->next;
	}
}
