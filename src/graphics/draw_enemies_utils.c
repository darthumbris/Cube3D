/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 13:56:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 17:21:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static enum e_compas	get_enemy_direction(t_vector_double dir_cam, \
						t_vector_double dir_enemy)
{
	double			dir_sprite;

	dir_sprite = atan2(dir_enemy.y, dir_enemy.x) - \
		atan2(dir_cam.y, dir_cam.x) + M_PI_2;
	if (dir_sprite < 0)
		dir_sprite += M_PI * 2;
	else if (dir_sprite > M_PI * 2)
		dir_sprite -= M_PI * 2;
	if (dir_sprite >= M_PI_8 && dir_sprite < (M_PI_4 + M_PI_8))
		return (C_NORTH_EAST);
	else if (dir_sprite >= (M_PI_4 + M_PI_8) && dir_sprite < (M_PI_2 + M_PI_8))
		return (C_NORTH);
	else if (dir_sprite >= (M_PI_2 + M_PI_8) && dir_sprite < (M_PI - M_PI_8))
		return (C_NORTH_WEST);
	else if (dir_sprite >= (M_PI - M_PI_8) && dir_sprite < (M_PI + M_PI_8))
		return (C_WEST);
	else if (dir_sprite >= (M_PI + M_PI_8) && dir_sprite < (M_PI32 - M_PI_8))
		return (C_SOUTH_WEST);
	else if (dir_sprite >= (M_PI32 - M_PI_8) && dir_sprite < (M_PI32 + M_PI_8))
		return (C_SOUTH);
	else if (dir_sprite >= (M_PI32 + M_PI_8) && dir_sprite < M_PI15_8)
		return (C_SOUTH_EAST);
	else
		return (C_EAST);
}

int	get_ypos_sheet(t_sprite *sprt)
{
	if (sprt->state == ALIVE)
		return ((sprt->frame % 5) * 65);
	else if ((sprt->state == DYING || sprt->state == DEAD) && sprt->kind == DOG)
		return (4 * 65);
	else if ((sprt->state == DYING || sprt->state == DEAD) && \
		sprt->kind == GUARD)
		return (5 * 65);
	else if (sprt->kind == DOG)
		return (5 * 65);
	return (6 * 65);
}

t_vector_int	get_transp_y(t_sprite *sprt)
{
	t_vector_int	y;
	int				frame;

	frame = sprt->frame;
	if (sprt->kind == GUARD)
	{
		if (sprt->state == DEAD || sprt->state == DYING)
			frame = 5;
		else if (sprt->state == ATTACKING)
			frame = 6;
		y.x = 13 + (frame % 7) * 65;
		y.y = 63 + (frame % 7) * 65;
	}
	else
	{
		if (sprt->state == DEAD || sprt->state == DYING)
			frame = 4;
		else if (sprt->state == ATTACKING)
			frame = 5;
		y.x = 19 + (frame % 6) * 65;
		y.y = 63 + (frame % 6) * 65;
	}
	return (y);
}

t_vector_int	get_transp_x(t_sprite *sprt, t_vector_double cam_dir)
{
	enum e_compas	dir;
	t_vector_int	x;

	dir = get_enemy_direction(cam_dir, sprt->dir);
	if (sprt->kind == DOG)
	{
		x.x = 3 + (dir % 8) * 65;
		x.y = 62 + (dir % 8) * 65;
		if (sprt->state == DYING || sprt->state == DEAD)
		{
			x.x = 6 + (sprt->frame % 4) * 65;
			x.y = 63 + (sprt->frame % 4) * 65;
		}
		else if (sprt->state == ATTACKING)
		{
			x.x = 19 + (sprt->frame % 3) * 65;
			x.y = 59 + (sprt->frame % 3) * 65;
		}
	}
	else
	{
		x.x = 14 + (dir % 8) * 65;
		x.y = 49 + (dir % 8) * 65;
		if (sprt->state == DYING || sprt->state == DEAD)
		{
			x.x = 13 + (sprt->frame % 5) * 65;
			x.y = 63 + (sprt->frame % 5) * 65;
		}
		else if (sprt->state == ATTACKING)
		{
			x.x = 17 + (sprt->frame % 3) * 65;
			x.y = 46 + (sprt->frame % 3) * 65;
		}
	}
	return (x);
}

int	get_xpos_sheet(t_sprite *sprt, t_vector_double cam_dir)
{
	const int	dir = get_enemy_direction(cam_dir, sprt->dir);

	if (sprt->state == ALIVE)
		return ((dir % 8) * 65);
	else if (sprt->state == DYING && sprt->kind == GUARD)
		return (sprt->frame % 5 * 65);
	else if (sprt->state == DYING && sprt->kind == DOG)
		return (sprt->frame % 4 * 65);
	else if (sprt->state == ATTACKING)
		return (sprt->frame % 3 * 65);
	else if (sprt->kind == DOG)
		return (3 * 65);
	return (4 * 65);
}
