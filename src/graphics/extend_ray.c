/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extend_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 15:51:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 16:05:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_door_segments(t_data *data, t_raycaster *r, t_intersect *door)
{
	if (r->door->direction == NORTH_SOUTH)
	{
		set_segment(&door->s1.p_0, r->map_pos.x, r->map_pos.y);
		set_segment(&door->s1.p_1, r->map_pos.x, r->map_pos.y + 1);
		set_segment(&door->s2.p_0, r->map_pos.x + 1, r->map_pos.y);
		set_segment(&door->s2.p_1, r->map_pos.x + 1, r->map_pos.y + 1);
		set_segment(&door->s3.p_0, r->map_pos.x + 1 - r->door->s_timer, \
			r->map_pos.y + 0.5);
		set_segment(&door->s3.p_1, r->map_pos.x + 1, r->map_pos.y + 0.5);
	}
	else
	{
		set_segment(&door->s1.p_0, r->map_pos.x, r->map_pos.y);
		set_segment(&door->s1.p_1, r->map_pos.x + 1, r->map_pos.y);
		set_segment(&door->s2.p_0, r->map_pos.x, r->map_pos.y + 1);
		set_segment(&door->s2.p_1, r->map_pos.x + 1, r->map_pos.y + 1);
		set_segment(&door->s3.p_0, r->map_pos.x + 0.5, \
			r->map_pos.y + 1 - r->door->s_timer);
		set_segment(&door->s3.p_1, r->map_pos.x + 0.5, r->map_pos.y + 1);
	}
	set_segment(&door->ray.p_0, data->cam.pos.x, data->cam.pos.y);
	set_segment(&door->ray.p_1, data->cam.pos.x + r->ray_dir.x, \
		data->cam.pos.y + r->ray_dir.y);
}

void	set_new_map_pos(t_vector_double *map, t_vector_double ray, \
	t_vector_double rd)
{
	if (ray.x > 0)
		map->x = rd.x;
	else
		map->x = rd.x - 1;
	if (ray.y > 0)
		map->y = rd.y;
	else
		map->y = rd.y - 1;
}

void	change_side(t_raycaster *ray)
{
	if (ray->door->direction == NORTH_SOUTH)
	{
		if (ray->door_hit == 2)
			ray->side = 1;
		else
			ray->side = 0;
	}
	else if (ray->door->direction == EAST_WEST)
	{
		if (ray->door_hit != 2)
			ray->side = 1;
		else
			ray->side = 0;
	}
}

static bool	door_hit(t_raycaster *r, t_intersect *seg)
{
	t_vector_double	rd;

	segment_to_line(&seg->ray, &seg->l1);
	segment_to_line(&seg->s3, &seg->l2);
	if (do_lines_intersect(&seg->l1, &seg->l2, &rd) && ((r->door->direction == \
	NORTH_SOUTH && rd.x >= seg->s3.p_0.x && rd.x <= seg->s3.p_1.x) || (r->door->\
	direction == EAST_WEST && rd.y >= seg->s3.p_0.y && rd.y <= seg->s3.p_1.y)))
		r->door_hit = 2;
	segment_to_line(&seg->s1, &seg->l2);
	if (!r->door_hit && do_lines_intersect(&seg->l1, &seg->l2, &rd) && \
	((r->door->direction == NORTH_SOUTH && rd.y >= seg->s1.p_0.y && rd.y \
	<= seg->s1.p_1.y) || (r->door->direction == EAST_WEST && rd.x >= \
	seg->s1.p_0.x && rd.x <= seg->s1.p_1.x)))
		r->door_hit = 1;
	segment_to_line(&seg->s2, &seg->l2);
	if (!r->door_hit && do_lines_intersect(&seg->l1, &seg->l2, &rd) && ((\
	r->door->direction == NORTH_SOUTH && rd.y >= seg->s2.p_0.y && rd.y \
	<= seg->s2.p_1.y) || (r->door->direction == EAST_WEST && rd.x >= \
	seg->s2.p_0.x && rd.x <= seg->s2.p_1.x)))
		r->door_hit = 1;
	if (!r->door_hit)
		return (false);
	set_new_map_pos(&r->map_pos, r->ray_dir, rd);
	change_side(r);
	return (true);
}

void	extend_ray(t_data *data, t_raycaster *ray)
{
	if (data->level.map[(int)ray->map_pos.y][(int)ray->map_pos.x] == 'D')
	{
		ray->door = get_door_struct
			(data, (t_vector_int){ray->map_pos.x, ray->map_pos.y});
		init_door_segments(data, ray, &ray->dcas);
		if (door_hit(ray, &ray->dcas))
			return ;
	}
	else if (data->level.map[(int)ray->map_pos.y][(int)ray->map_pos.x] == 'h' \
		|| data->level.map[(int)ray->map_pos.y][(int)ray->map_pos.x] == 'H')
	{
		printf("secret door ray here\n");
	}
	ray->hit = false;
}
