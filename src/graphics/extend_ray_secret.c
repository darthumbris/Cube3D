/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extend_ray_secret.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 12:20:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 12:24:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init_secret_segments(t_data *data, t_raycaster *r, \
			t_intersect *door, t_vector_double map)
{
	if (r->secret->direction == S_NORTH)
	{
		set_segment(&door->s1.p_0, map.x, map.y + 1 - r->secret->s_timer);
		set_segment(&door->s1.p_1, map.x + 1, map.y + 1 - r->secret->s_timer);
	}
	else if (r->secret->direction == S_SOUTH)
	{
		set_segment(&door->s1.p_0, map.x, map.y + r->secret->s_timer);
		set_segment(&door->s1.p_1, map.x + 1, map.y + r->secret->s_timer);
	}
	else if (r->secret->direction == S_EAST)
	{
		set_segment(&door->s1.p_0, map.x + r->secret->s_timer, map.y);
		set_segment(&door->s1.p_1, map.x + r->secret->s_timer, map.y + 1);
	}
	else if (r->secret->direction == S_WEST)
	{
		set_segment(&door->s1.p_0, map.x + 1 - r->secret->s_timer, map.y);
		set_segment(&door->s1.p_1, map.x + 1 - r->secret->s_timer, map.y + 1);
	}
	set_segment(&door->ray.p_0, data->cam.pos.x, data->cam.pos.y);
	set_segment(&door->ray.p_1, data->cam.pos.x + r->ray_dir.x, \
		data->cam.pos.y + r->ray_dir.y);
}

bool	secret_hit(t_data *dat, t_intersect *seg)
{
	t_vector_double	res;

	segment_to_line(&seg->ray, &seg->l1);
	segment_to_line(&seg->s1, &seg->l2);
	if (do_lines_intersect(&seg->l1, &seg->l2, &res) && \
		(((dat->caster.secret->direction == S_SOUTH || \
			dat->caster.secret->direction == S_NORTH) && \
		res.x >= seg->s1.p_0.x && res.x <= seg->s1.p_1.x) || \
		(((dat->caster.secret->direction == S_EAST || \
			dat->caster.secret->direction == S_WEST)) && \
		res.y >= seg->s1.p_0.y && res.y <= seg->s1.p_1.y)))
	{
		dat->caster.secret_hit = 1;
		set_new_map_pos(&dat->caster.map_pos, dat->caster.ray_dir, res);
		if (dat->caster.secret->direction == S_SOUTH || \
			dat->caster.secret->direction == S_NORTH)
			dat->caster.side = 1;
		else
			dat->caster.side = 0;
		return (true);
	}
	return (false);
}
