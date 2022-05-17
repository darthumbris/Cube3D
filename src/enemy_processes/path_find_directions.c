/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_directions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 12:47:07 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 12:48:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	new_pos_further(t_vector_double temp_pos, t_vector_double cam_pos, \
			t_vector_double map_pos)
{
	return (sprite_dist(temp_pos, cam_pos) > sprite_dist(map_pos, cam_pos));
}

static int	check_south_north(t_data *data, t_sprite *enemy, int dir_to_p)
{
	int					cardinal_dir;
	t_vector_double		temp_pos;
	t_vector_double		collision;

	cardinal_dir = 1;
	set_new_x_pos(&temp_pos, &collision, enemy, 0);
	set_new_y_pos(&temp_pos, &collision, enemy, dir_to_p);
	if (new_pos_further(temp_pos, data->cam.pos, enemy->map_pos))
	{
		set_new_y_pos(&temp_pos, &collision, enemy, -dir_to_p);
		cardinal_dir = 2;
	}
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map[(int)(collision.y)][(int)(collision.x)]))
		return (0);
	return (cardinal_dir);
}

static int	check_east_west(t_data *data, t_sprite *enemy, int dir_to_p)
{
	int					cardinal_dir;
	t_vector_double		temp_pos;
	t_vector_double		collision;

	cardinal_dir = 3;
	set_new_x_pos(&temp_pos, &collision, enemy, dir_to_p);
	set_new_y_pos(&temp_pos, &collision, enemy, 0);
	if (new_pos_further(temp_pos, data->cam.pos, enemy->map_pos))
	{
		set_new_x_pos(&temp_pos, &collision, enemy, -dir_to_p);
		cardinal_dir = 4;
	}
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map[(int)(collision.y)][(int)(collision.x)]))
		return (0);
	return (cardinal_dir);
}

int	try_cardinal(t_data *data, t_sprite *enemy, int cardinal, int dir_to_p)
{
	if (cardinal == 0)
		return (check_south_north(data, enemy, dir_to_p));
	else
		return (check_east_west(data, enemy, dir_to_p));
}

int	try_diagonals(t_data *data, t_sprite *enemy)
{
	const int		rand_dir = rand() % 4;
	t_vector_double	temp_pos;
	t_vector_double	collision;

	if (rand_dir == 0 || rand_dir == 1)
		set_new_y_pos(&temp_pos, &collision, enemy, -1);
	else
		set_new_y_pos(&temp_pos, &collision, enemy, +1);
	if (rand_dir == 1 || rand_dir == 3)
		set_new_x_pos(&temp_pos, &collision, enemy, +1);
	else
		set_new_x_pos(&temp_pos, &collision, enemy, -1);
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map[(int)(collision.y)][(int)(collision.x)]))
		return (0);
	return (rand_dir + 1);
}
