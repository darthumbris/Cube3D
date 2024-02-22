/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 15:48:51 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/15 16:33:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	door_check(t_data *data, t_vector_double pos)
{
	return (is_door_tile(data->level.map_planes[(int)pos.y][(int)pos.x][0]) && \
			!is_door_open(data, (int)pos.y, (int)pos.x));
}

// void	set_val(t_vector_int *delta, t_vector_int *sign, 
// 				t_vector_int pc_pos, t_vector_int g_pos)
// {
// 	delta->x = abs(pc_pos.x - g_pos.x);
// 	delta->y = abs(pc_pos.y - g_pos.y);
// 	if (pc_pos.x > g_pos.x)
// 		sign->x = 1;
// 	else
// 		sign->x = -1;
// 	if (pc_pos.y > g_pos.y)
// 		sign->y = 1;
// 	else
// 		sign->y = -1;
// }

// bool	view_not_blocked(t_data *data, t_vector_int pc_pos, t_vector_int g_pos)
// {
// 	t_vector_int	sign;
// 	t_vector_int	delta;
// 	int				err;

// 	set_val(&delta, &sign, pc_pos, g_pos);
// 	err = 2 * (delta.y - delta.x);
// 	while (1)
// 	{
// 		if (is_wall_tile(data->level.map[g_pos.y][g_pos.x]) || 
// 			door_check(data, g_pos))
// 			return (false);
// 		if (g_pos.x == pc_pos.x && g_pos.y == pc_pos.y)
// 			return (true);
// 		if (err >= 0)
// 		{
// 			g_pos.y += sign.y;
// 			err = err - 2 * delta.x;
// 		}
// 		if (err < 0)
// 		{
// 			g_pos.x += sign.x;
// 			err = err + 2 * delta.y;
// 		}
// 	}	
// }
