/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/12 15:30:07 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	conditions(t_data *data, t_sprite_lst *lst, \
int dist, t_sprite_enum kind)
{
	return (lst->sprite_data.kind == kind && lst->sprite_data.state == ALIVE && \
			lst->sprite_data.dist > dist && \
			lst->sprite_data.dist < RENDER_DIST_S && view_not_blocked(data, \
			(t_vector_int){.x = data->cam.pos.x, .y = data->cam.pos.y}, \
			(t_vector_int){.x = lst->sprite_data.map_pos.x, \
			.y = lst->sprite_data.map_pos.y}));
}

static void	move_x(t_data *data, t_sprite_lst *lst, double speed, int delay)
{
	const double	temp = lst->sprite_data.map_pos.x;

	if (lst->sprite_data.map_pos.x < data->cam.pos.x)
		lst->sprite_data.map_pos.x += speed;
	else
		lst->sprite_data.map_pos.x -= speed;
	if (is_wall_tile(data->level.map[(int)lst->sprite_data.map_pos.y] \
	[(int)lst->sprite_data.map_pos.x]))
		lst->sprite_data.map_pos.x = temp;
	if (lst->sprite_data.map_pos.x != temp && delay % 8 == 0)
		lst->sprite_data.frame++;
}

static void	move_y(t_data *data, t_sprite_lst *lst, double speed, int delay)
{
	const double	temp = lst->sprite_data.map_pos.y;

	if (lst->sprite_data.map_pos.y < data->cam.pos.y)
		lst->sprite_data.map_pos.y += speed;
	else
		lst->sprite_data.map_pos.y -= speed;
	if (is_wall_tile(data->level.map[(int)lst->sprite_data.map_pos.y] \
	[(int)lst->sprite_data.map_pos.x]))
		lst->sprite_data.map_pos.y = temp;
	if (lst->sprite_data.map_pos.y != temp && delay % 8 == 0)
		lst->sprite_data.frame++;
}

void	path_find(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if (conditions(data, lst, 10, GUARD))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				move_x(data, lst, 0.02, delay);
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				move_y(data, lst, 0.02, delay);
			if (lst->sprite_data.frame > 4)
				lst->sprite_data.frame = 0;
		}
		if (conditions(data, lst, 2, DOG))
		{
			if (fabs(lst->sprite_data.map_pos.x - data->cam.pos.x) > 0.05)
				move_x(data, lst, 0.05, delay);
			if (fabs(lst->sprite_data.map_pos.y - data->cam.pos.y) > 0.05)
				move_y(data, lst, 0.05, delay);
			if (lst->sprite_data.frame > 3)
				lst->sprite_data.frame = 0;
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
}
