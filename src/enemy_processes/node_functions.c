/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 16:17:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 16:29:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	delete_node(t_node **begin_list, t_node *node)
{
	t_node	*prev;
	t_node	*last;

	prev = NULL;
	last = *begin_list;
	while (last)
	{
		if (last == node)
		{
			if (prev == NULL)
				*begin_list = last->next;
			else
				prev->next = last->next;
			break ;
		}
		prev = last;
		last = prev->next;
	}
}

void	add_node_to_front(t_node **begin_list, t_node *node)
{
	node->next = *begin_list;
	*begin_list = node;
}

t_node	*make_node_lst(t_node *parent, t_vector_int start_pos, \
				t_vector_int end_pos)
{
	t_node			*element;
	t_vector_int	square;

	element = malloc(sizeof(t_node));
	if (!element)
		return (NULL);
	element->pos = start_pos;
	element->parent = parent;
	element->next = NULL;
	square.x = end_pos.x - start_pos.x;
	square.y = end_pos.y - start_pos.y;
	element->tile_dist = (square.x * square.x + square.y * square.y);
}

int	node_path_size(t_node *end)
{
	int	i;

	i = 0;
	while (end)
	{
		++i;
		end = end->parent;
	}
	return (i);
}

void	clear_list(t_astar_path *astar, t_node *a, t_node *b, t_node *goal)
{
	t_node	*t;
	int		i;

	while (a)
	{
		t = a->next;
		free(a);
		a = t;
	}
	while (b)
	{
		t = b->next;
		free(b);
		b = t;
	}
	i = 0;
	while (astar->closed_map[i])
		free(astar->closed_map[i++]);
	free(astar->closed_map);
	free(goal);
}
