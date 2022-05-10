/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/06 17:40:48 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	door_check(t_data *data, t_vector_int g_pos)
{
	return (is_door_tile(data->level.map[g_pos.y][g_pos.x]) && \
			!is_door_open(data, g_pos.y, g_pos.x));
}

void	set_val(t_vector_int *delta, t_vector_int *sign, \
				t_vector_int pc_pos, t_vector_int g_pos)
{
	delta->x = abs(pc_pos.x - g_pos.x);
	delta->y = abs(pc_pos.y - g_pos.y);
	if (pc_pos.x > g_pos.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (pc_pos.y > g_pos.y)
		sign->y = 1;
	else
		sign->y = -1;
}

bool	view_not_blocked(t_data *data, t_vector_int pc_pos, t_vector_int g_pos)
{
	t_vector_int	sign;
	t_vector_int	delta;
	int				err;

	set_val(&delta, &sign, pc_pos, g_pos);
	err = 2 * (delta.y - delta.x);
	while (1)
	{
		if (is_wall_tile(data->level.map[g_pos.y][g_pos.x]) || \
			door_check(data, g_pos))
			return (false);
		if (g_pos.x == pc_pos.x && g_pos.y == pc_pos.y)
			return (true);
		if (err >= 0)
		{
			g_pos.y += sign.y;
			err = err - 2 * delta.x;
		}
		if (err < 0)
		{
			g_pos.x += sign.x;
			err = err + 2 * delta.y;
		}
	}	
}

void	path_find(t_data *data)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (lst->sprite_data.kind == GUARD && lst->sprite_data.dist > 10 && \
			lst->sprite_data.dist < RENDER_DIST_S && view_not_blocked(data, \
			(t_vector_int){.x = data->cam.pos.x, .y = data->cam.pos.y}, \
			(t_vector_int){.x = lst->sprite_data.map_pos.x, .y = lst->sprite_data.map_pos.y}))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				lst->sprite_data.map_pos.x += lst->sprite_data.map_pos.x < data->cam.pos.x ? 0.01 : -0.01;
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				lst->sprite_data.map_pos.y += lst->sprite_data.map_pos.y < data->cam.pos.y ? 0.01 : -0.01;
		}
		if (lst->sprite_data.kind == DOG && lst->sprite_data.dist > 1  && \
			lst->sprite_data.dist < RENDER_DIST_S && view_not_blocked(data, \
			(t_vector_int){.x = data->cam.pos.x, .y = data->cam.pos.y}, \
			(t_vector_int){.x = lst->sprite_data.map_pos.x, .y = lst->sprite_data.map_pos.y}))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				lst->sprite_data.map_pos.x += lst->sprite_data.map_pos.x < data->cam.pos.x ? 0.02 : -0.02;
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				lst->sprite_data.map_pos.y += lst->sprite_data.map_pos.y < data->cam.pos.y ? 0.02 : -0.02;
		}
		lst = lst->next;
	}
}
