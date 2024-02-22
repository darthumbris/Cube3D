/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_dog.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 11:38:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 16:34:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	try_diagonals_dog(t_data *data, t_sprite *dog, int dir)
{
	t_vector_double	temp_pos;
	t_vector_double	collision;

	if (dir == 0 || dir == 1)
		set_new_y_pos(&temp_pos, &collision, dog, -1);
	else
		set_new_y_pos(&temp_pos, &collision, dog, +1);
	if (dir == 1 || dir == 3)
		set_new_x_pos(&temp_pos, &collision, dog, +1);
	else
		set_new_x_pos(&temp_pos, &collision, dog, -1);
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map_planes[(int)(collision.y)][(int)(collision.x)][0]) || \
		sprite_dist(collision, data->cam.pos) > dog->dist)
		return (0);
	return (dir + 1);
}

static int	pathfind_cardinal_dog(t_data *data, t_sprite *dog, int dir)
{
	t_vector_double	temp_pos;
	t_vector_double	collision;

	if (dir == 0)
		set_new_y_pos(&temp_pos, &collision, dog, -1);
	if (dir == 1)
		set_new_y_pos(&temp_pos, &collision, dog, +1);
	if (dir == 2)
		set_new_x_pos(&temp_pos, &collision, dog, +1);
	else if (dir == 3)
		set_new_x_pos(&temp_pos, &collision, dog, -1);
	if (is_out_of_bounds(collision, data) || is_obstacle
		(data->level.map_planes[(int)(collision.y)][(int)(collision.x)][0]) || \
		sprite_dist(collision, data->cam.pos) > dog->dist)
		return (0);
	return (dir + 4);
}

static bool	is_current_path_to_player(t_data *data, t_sprite *dog)
{
	const int		dir = dog->en_dat.path_dir;
	t_vector_double	temp_pos;
	t_vector_double	collision;

	temp_pos.y = dog->map_pos.y;
	temp_pos.x = dog->map_pos.x;
	collision.y = dog->map_pos.y;
	collision.x = dog->map_pos.x;
	if (dir == 1 || dir == 2 || dir == 6 || dir == 9)
		set_new_y_pos(&temp_pos, &collision, dog, -1);
	else if (dir == 3 || dir == 4 || dir == 5 || dir == 10)
		set_new_y_pos(&temp_pos, &collision, dog, +1);
	if (dir == 2 || dir == 4 || dir == 7 || dir == 12)
		set_new_x_pos(&temp_pos, &collision, dog, +1);
	else if (dir == 1 || dir == 3 || dir == 8 || dir == 11)
		set_new_x_pos(&temp_pos, &collision, dog, -1);
	if (sprite_dist(collision, data->cam.pos) > dog->dist)
		return (false);
	return (true);
}

void	pathind_dog(t_data *data, t_sprite *dog)
{
	int	i;

	if (dog->en_dat.path_dir == 0)
	{
		i = 0;
		while (dog->en_dat.path_dir == 0 && i < 4)
			dog->en_dat.path_dir = try_diagonals_dog(data, dog, i++);
		if (dog->en_dat.path_dir == 0)
		{
			i = 0;
			while (dog->en_dat.path_dir == 0 && i < 4)
			{
				dog->en_dat.path_dir = pathfind_cardinal_dog(data, dog, i);
				if (dog->en_dat.path_dir)
					break ;
				i++;
			}
		}
	}
	if (dog->en_dat.path_dir && is_current_path_to_player(data, dog))
		pathfind_in_direction(data, dog);
	else
		dog->en_dat.path_dir = 0;
}
