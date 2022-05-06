/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extend_ray_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 15:26:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 16:15:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static double	determinant(double a, double b, double c, double d)
{
	return (a * d - b * c);
}

void	set_segment(t_vector_double *p, double x, double y)
{
	p->x = x;
	p->y = y;
}

bool	do_lines_intersect(t_line *m, t_line *n, t_vector_double *result)
{
	double		zn;
	double		inv_zn;

	zn = determinant(m->a, m->b, n->a, n->b);
	if (fabs(zn) < 2.2204460492503131e-16)
		return (false);
	inv_zn = 1.0 / zn;
	result->x = -determinant(m->c, m->b, n->c, n->b) * inv_zn;
	result->y = -determinant(m->a, m->c, n->a, n->c) * inv_zn;
	return (true);
}

void	segment_to_line(t_segment *segm, t_line *line)
{
	line->a = segm->p_0.y - segm->p_1.y;
	line->b = segm->p_1.x - segm->p_0.x;
	line->c = segm->p_0.x * segm->p_1.y - segm->p_1.x * segm->p_0.y;
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
