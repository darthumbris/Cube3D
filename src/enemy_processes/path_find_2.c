/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 10:59:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 12:25:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_obstacle(char c)
{
	return (is_wall_kind_tile(c) || c == ' ');
}

static void	change_frame(t_sprite *enemy)
{
	enemy->en_dat.counter++;
	if (enemy->en_dat.counter > 50)
		enemy->en_dat.counter = 0;
	if (enemy->en_dat.counter % 7 == 0)
		enemy->en_dat.frame++;
	if ((enemy->kind == DOG && enemy->en_dat.frame > 3) || \
	(enemy->kind == GUARD && enemy->en_dat.frame > 4))
		enemy->en_dat.frame = 0;
}

void	pathfind_in_direction(t_data *data, t_sprite *enemy)
{
	const int		dir = enemy->en_dat.path_dir;
	t_vector_double	temp_pos;
	t_vector_double	collision;

	temp_pos.y = enemy->map_pos.y;
	temp_pos.x = enemy->map_pos.x;
	if (dir == 1 || dir == 2 || dir == 5 || dir == 10)
		set_new_y_pos(&temp_pos, &collision, enemy, -1);
	else if (dir == 3 || dir == 4 || dir == 6 || dir == 9)
		set_new_y_pos(&temp_pos, &collision, enemy, +1);
	if (dir == 2 || dir == 4 || dir == 7 || dir == 12)
		set_new_x_pos(&temp_pos, &collision, enemy, +1);
	else if (dir == 1 || dir == 3 || dir == 8 || dir == 11)
		set_new_x_pos(&temp_pos, &collision, enemy, -1);
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map[(int)(collision.y)][(int)(collision.x)]))
	{
		enemy->en_dat.path_dir = 0;
		return ;
	}
	change_frame(enemy);
	enemy->map_pos.x = temp_pos.x;
	enemy->map_pos.y = temp_pos.y;
}
