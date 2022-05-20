/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_lst_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 12:51:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/20 12:36:27 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_sprite_lst	*add_ammo_to_lst(t_sprite_lst **begin, t_sprite data)
{
	t_sprite_lst	*first;

	first = new_sprite(data);
	if (!first)
		return (NULL);
	first->sprite_data.kind = 49;
	first->sprite_data.transp_begin.x = 56;
	first->sprite_data.transp_begin.y = 0;
	first->sprite_data.transp_end.x = 72;
	first->sprite_data.transp_end.y = 108;
	first->sprite_data.dropped = true;
	first->sprite_data.map_pos.x += .1;
	first->sprite_data.map_pos.y += .1;
	first->next = *begin;
	(*begin)->prev = first;
	first->prev = NULL;
	*begin = first;
	return (first);
}

t_sprite_lst	*new_sprite(t_sprite data)
{
	t_sprite_lst	*new;

	new = malloc(sizeof(t_sprite_lst));
	if (!new)
		return (NULL);
	new->sprite_data = data;
	new->sprite_data.dropped = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sprite_lst	*add_sprite(t_sprite_lst **begin, t_sprite data)
{
	t_sprite_lst	*first;

	first = new_sprite(data);
	if (!first)
		return (NULL);
	first->next = *begin;
	(*begin)->prev = first;
	first->prev = NULL;
	*begin = first;
	return (first);
}

void	clear_sprite_lst(t_sprite_lst **begin)
{
	t_sprite_lst	*first;
	t_sprite_lst	*next;

	first = *begin;
	while (first)
	{
		next = first->next;
		free(first);
		first = next;
	}
	*begin = NULL;
}
