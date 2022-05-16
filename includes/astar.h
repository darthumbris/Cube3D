/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   astar.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 16:19:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 16:45:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_H
# define ASTAR_H

# define NEIGHBOURS 4

# include "vectors.h"

typedef struct s_node	t_node;

struct s_node
{
	t_vector_int	pos;
	t_node			*parent;
	int				tile_dist;
	t_node			*next;
};

typedef struct s_astar_path
{
	t_node			*list_open;
	t_node			*list_closed;
	t_node			*goal;
	t_vector_int	start_pos;
	t_vector_int	end_pos;
	char			**closed_map;
}				t_astar_path;

char	**get_closed_map(int map_w, int map_h);
t_node	*make_node_lst(t_node *parent, t_vector_int start_pos, \
				t_vector_int end_pos);
void	delete_node(t_node **begin_list, t_node *node);
void	add_node_to_front(t_node **begin_list, t_node *node);
int		node_path_size(t_node *end);
void	clear_list(t_astar_path *astar, t_node *a, t_node *b, t_node *goal);
int		get_shifted_dist(t_vector_double start, t_vector_int end);

#endif