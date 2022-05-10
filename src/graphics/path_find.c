/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/10 16:07:24 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	conditions(t_data *data, t_sprite_lst *lst, \
int dist, t_sprite_enum kind)
{
	return (lst->sprite_data.kind == kind && lst->sprite_data.dist > dist && \
			lst->sprite_data.dist < RENDER_DIST_S && view_not_blocked(data, \
			(t_vector_int){.x = data->cam.pos.x, .y = data->cam.pos.y}, \
			(t_vector_int){.x = lst->sprite_data.map_pos.x, \
			.y = lst->sprite_data.map_pos.y}));
}

static void	move_x(t_data *data, t_sprite_lst *lst, double speed)
{
	if (lst->sprite_data.map_pos.x < data->cam.pos.x)
		lst->sprite_data.map_pos.x += speed;
	else
		lst->sprite_data.map_pos.x -= speed;
}

static void	move_y(t_data *data, t_sprite_lst *lst, double speed)
{
	if (lst->sprite_data.map_pos.y < data->cam.pos.y)
		lst->sprite_data.map_pos.y += speed;
	else
		lst->sprite_data.map_pos.y -= speed;
}

void	path_find(t_data *data)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	while (lst)
	{
		if (conditions(data, lst, 10, GUARD))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				move_x(data, lst, 0.02);
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				move_y(data, lst, 0.02);
		}
		if (conditions(data, lst, 1, DOG))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				move_x(data, lst, 0.04);
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				move_y(data, lst, 0.04);
		}
		lst = lst->next;
	}
}
