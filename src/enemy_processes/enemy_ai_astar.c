/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_ai_astar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 12:58:24 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 16:51:21 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_valid_pos(t_data *data, t_vector_int	pos)
{
	char	c;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->level.map_w || \
		pos.y >= data->level.map_h)
		return (false);
	c = data->level.map[pos.y][pos.x];
	return ((!is_wall_tile(c) || is_door_tile(c)));
}

t_vector_int	*astar_path(t_data *data, t_vector_int start_pos, \
			t_vector_int end_pos, int max_checks)
{
	t_vector_int	*path;
	t_astar_path	astar;

	if (!is_valid_pos(data, start_pos) || !is_valid_pos(data, end_pos))
		return (NULL);
	astar.closed_map = get_closed_map(data->level.map_w, data->level.map_h);
	if (astar.closed_map == NULL)
		return (NULL);
	astar.start_pos = start_pos;
	astar.end_pos = end_pos;
	astar.list_open = make_node_lst(NULL, start_pos, end_pos);
	astar.list_closed = NULL;
	while (max_checks--)
	{
		if (!astar.list_open)
			break ;
		add_neighbours_to_list(&astar, astar.list_open, data);
		if (astar.goal)
			break ;
	}
	path = make_path(astar.goal);
	clear_node_list();
	return (path);
}

void	refresh_path(t_data *data, t_sprite *enemy, int max_checks)
{
	t_vector_int	start_pos;
	t_vector_int	end_pos;
	t_vector_int	*new_pos;

	start_pos.x = floor(enemy->map_pos.x);
	start_pos.y = floor(enemy->map_pos.y);
	end_pos.x = floor(data->cam.pos.x);
	end_pos.y = floor(data->cam.pos.y);
	new_pos = astar_path(data, start_pos, end_pos, max_checks);
	if (new_pos)
	{
		if (enemy->en_dat.path)
			free(enemy->en_dat.path);
		enemy->en_dat.path = new_pos;
		enemy->en_dat.path_index = 0;
	}
}

t_vector_double	get_next_move(t_data *data, t_sprite *enemy)
{
	t_vector_int	dest;
	t_vector_double	next;

	while (enemy->en_dat.path)
	{
		dest = enemy->en_dat.path[enemy->en_dat.path_index];
		if (dest.x == -999 && dest.y == -999)
		{
			free(enemy->en_dat.path);
			enemy->en_dat.path = NULL;
			enemy->en_dat.path_index = 0;
		}
		else if (get_shifted_dist(enemy->map_pos, dest) < 0.75 && \
				++(enemy->en_dat.path_index))
			continue ;
		next.x = dest.x + 0.5;
		next.y = dest.y + 0.5;
		return (next);
	}
	if (sprite_dist(data->cam.pos, enemy->map_pos) > 9)
	{
		next.x = enemy->map_pos.x;
		next.y = enemy->map_pos.y;
		return (next);
	}
	return (data->cam.pos);
}

void	pathfind_to_player(t_data *data, t_sprite *enemy)
{
	t_vector_double	next;
	t_vector_double	move;

	if (enemy->en_dat.move_counter % 1000 == 20)
		refresh_path(data, enemy, 350);
	else if (enemy->en_dat.move_counter % 70 == 0)
		refresh_path(data, enemy, 250);
	next = get_next_move(data, enemy);
	enemy->en_dat.move_counter++;
	move.x = (next.x - enemy->map_pos.x);
	move.y = (next.y - enemy->map_pos.y);
	enemy->map_pos.x = move.x;// needs a collide check
	enemy->map_pos.y = move.y; // needs a collide check!!!
}
