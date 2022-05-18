/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies_transparencies.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:56:52 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 13:31:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_vector_int	get_transp_y(t_sprite *sprt)
{
	t_vector_int	y;
	int				frame;

	frame = sprt->en_dat.frame;
	if (sprt->kind == GUARD)
	{
		if (sprt->en_dat.state >= HURT)
			frame = 5;
		else if (sprt->en_dat.state == ATTACKING)
			frame = 6;
		y.x = 13 + (frame % 7) * 65;
		y.y = 63 + (frame % 7) * 65;
	}
	else
	{
		if (sprt->en_dat.state == DEAD || sprt->en_dat.state == DYING)
			frame = 4;
		else if (sprt->en_dat.state == ATTACKING)
			frame = 5;
		y.x = 19 + (frame % 6) * 65;
		y.y = 63 + (frame % 6) * 65;
	}
	return (y);
}

static t_vector_int	get_transp_x_dog(t_sprite *sprt, enum e_compas dir)
{
	t_vector_int	x;

	x.x = 3 + (dir % 8) * 65;
	x.y = 62 + (dir % 8) * 65;
	if (sprt->en_dat.state == DYING || sprt->en_dat.state == DEAD)
	{
		x.x = 6 + (sprt->en_dat.frame % 4) * 65;
		x.y = 63 + (sprt->en_dat.frame % 4) * 65;
	}
	else if (sprt->en_dat.state == ATTACKING)
	{
		x.x = 19 + (sprt->en_dat.frame % 3) * 65;
		x.y = 59 + (sprt->en_dat.frame % 3) * 65;
	}
	return (x);
}

static t_vector_int	get_transp_x_guard(t_sprite *sprt, enum e_compas dir)
{
	t_vector_int	x;

	x.x = 14 + (dir % 8) * 65;
	x.y = 49 + (dir % 8) * 65;
	if (sprt->en_dat.state == DYING || sprt->en_dat.state == DEAD)
	{
		x.x = 13 + (sprt->en_dat.frame % 5) * 65;
		x.y = 63 + (sprt->en_dat.frame % 5) * 65;
	}
	else if (sprt->en_dat.state == ATTACKING)
	{
		x.x = 17 + (sprt->en_dat.frame % 3) * 65;
		x.y = 46 + (sprt->en_dat.frame % 3) * 65;
	}
	return (x);
}

t_vector_int	get_transp_x(t_sprite *sprt, t_vector_double cam_dir)
{
	enum e_compas	dir;

	dir = get_enemy_direction(cam_dir, sprt->en_dat.dir);
	if (sprt->kind == GUARD && sprt->en_dat.state == HURT)
		dir = 7;
	if (sprt->kind == DOG)
		return (get_transp_x_dog(sprt, dir));
	else
		return (get_transp_x_guard(sprt, dir));
}
