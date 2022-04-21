/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_lst_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 12:51:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/21 12:57:26 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_sprite_lst	*new_sprite(t_sprite data)
{
	t_sprite_lst	*new;

	new = malloc(sizeof(t_sprite_lst));
	if (!new)
		return (NULL);
	new->sprite_data = data;
	new->next = NULL;
	return (new);
}

t_sprite_lst	*add_sprite(t_sprite_lst **begin, t_sprite data)
{
	t_sprite_lst	*first;

	first = new_sprite(data);
	if (!first)
		return (NULL);
	first->next = *begin;
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
