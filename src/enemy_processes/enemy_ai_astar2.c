/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_astar2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 16:22:38 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 16:40:09 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

char	**get_closed_map(int map_w, int map_h)
{
	char	**closed_map;
	int		i;

	closed_map = ft_calloc(sizeof(char *), map_h);
	i = 0;
	while (i < map_h)
		closed_map[i++] = ft_calloc(sizeof(char), map_w);
	return (closed_map);
}

static t_vector_int	get_neighbour(int dir, t_vector_int pos)
{
	if (dir == 0)
		pos.x++;
	else if (dir == 1)
		pos.x--;
	else if (dir == 2)
		pos.y++;
	else if (dir == 3)
		pos.y--;
	return (pos);
}

void	add_neighbours_to_list(t_astar_path *astar, t_node *node, t_data *data)
{
	int				i;
	t_vector_int	pos;
	t_node			*next;

	while (node)
	{
		next = node->next;
		delete_node(&astar->list_open, node);
		add_node_to_front(&astar->list_closed, node);
		i = 0;
		while (i < NEIGHBOURS)
		{
			pos = get_neighbour(i++, node->pos);
			if (is_valid_pos(data, pos))
			{
				astar->goal = add_node(astar, node, pos);
				if (astar->goal)
					return ;
			}
		}
		node = node->next;
	}
}

t_vector_int	*make_path(t_node *end)
{
	int				size;
	t_vector_int	*path;

	size = node_path_size(end);
	if (!end || size == 0)
		return (NULL);
	path = malloc(sizeof(t_vector_int) * (size + 1));
	if (!path)
		return (NULL);
	path[size].x = -999;
	path[size].y = -999;
	while (end)
	{
		path[--size] = end->pos;
		end = end->parent;
	}
	return (path);
}

int	get_shifted_dist(t_vector_double start, t_vector_int end)
{
	start.x -= end.x + 0.5;
	start.y -= end.y + 0.5;
	return (end.x * end.x + end.y * end.y);
}
