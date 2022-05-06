/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extend_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 15:51:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 17:30:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	change_side(t_raycaster *ray)
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

static void	init_secret_segments(t_data *data, t_raycaster *r, \
			t_intersect *door, t_vector_double map)
{
	if (r->door->direction == NORTH)
	{
		set_segment(&door->s1.p_0, map.x, map.y + 1 - r->secret->s_timer);
		set_segment(&door->s1.p_1, map.x + 1, map.y + 1 - r->secret->s_timer);
	}
	else if (r->door->direction == SOUTH)
	{
		set_segment(&door->s1.p_0, map.x, map.y + r->secret->s_timer);
		set_segment(&door->s1.p_1, map.x + 1, map.y + r->secret->s_timer);
	}
	else if (r->door->direction == EAST)
	{
		set_segment(&door->s1.p_0, map.x + r->secret->s_timer, map.y);
		set_segment(&door->s1.p_1, map.x + r->secret->s_timer, map.y + 1);
	}
	else if (r->door->direction == WEST)
	{
		set_segment(&door->s1.p_0, map.x + 1 - r->secret->s_timer, map.y);
		set_segment(&door->s1.p_1, map.x + 1 - r->secret->s_timer, map.y + 1);
	}
	set_segment(&door->ray.p_0, data->cam.pos.x, data->cam.pos.y);
	set_segment(&door->ray.p_1, data->cam.pos.x + r->ray_dir.x, \
		data->cam.pos.y + r->ray_dir.y);
}

static bool	secret_hit(t_data *dat, t_intersect *seg)
{
	t_vector_double	res;

	segment_to_line(&seg->ray, &seg->l1);
	segment_to_line(&seg->s1, &seg->l2);
	if (do_lines_intersect(&seg->l1, &seg->l2, &res) && \
		(((dat->caster.secret->direction == SOUTH || \
			dat->caster.secret->direction == NORTH) && \
		res.x >= seg->s1.p_0.x && res.x <= seg->s1.p_1.x) || \
		(((dat->caster.secret->direction == EAST || \
			dat->caster.secret->direction == WEST)) && \
		res.y >= seg->s1.p_0.y && res.y <= seg->s1.p_1.y)))
	{
		dat->caster.secret_hit = 1;
		set_new_map_pos(&dat->caster.map_pos, dat->caster.ray_dir, res);
		if (dat->caster.secret->direction == SOUTH || \
			dat->caster.secret->direction == NORTH)
			dat->caster.side = 1;
		else
			dat->caster.side = 0;
		printf("dir: %d\n", dat->caster.secret->direction);
		return (true);
	}
	return (false);
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
		ray->secret = get_door_struct(data, \
		(t_vector_int){ray->map_pos.x, ray->map_pos.y});
		init_secret_segments(data, &data->caster, &data->caster.dcas, data->caster.map_pos);
		if (secret_hit(data, &data->caster.dcas))
			return ;
	}
	ray->hit = false;
}
