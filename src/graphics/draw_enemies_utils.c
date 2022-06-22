/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/12 13:56:45 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:13:21 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

enum e_compas	get_enemy_direction(t_vector_double dir_cam, \
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
	if (is_enemy_movable(sprt->en_dat.state))
		return ((sprt->en_dat.frame % 5) * 65);
	else if (is_guard(sprt->kind) && sprt->en_dat.state == HURT)
		return (5 * 65);
	else if ((sprt->en_dat.state == DYING || sprt->en_dat.state == DEAD) && \
		sprt->kind == DOG)
		return (4 * 65);
	else if ((sprt->en_dat.state == DYING || sprt->en_dat.state == DEAD) && \
		sprt->kind == GUARD)
		return (5 * 65);
	else if (sprt->kind == DOG)
		return (5 * 65);
	return (6 * 65);
}

int	get_xpos_sheet(t_sprite *sprt, t_vector_double cam_dir)
{
	const int	dir = get_enemy_direction(cam_dir, sprt->en_dat.dir);

	if (is_enemy_movable(sprt->en_dat.state))
		return ((dir % 8) * 65);
	else if (is_guard(sprt->kind) && sprt->en_dat.state == HURT)
		return (7 * 65);
	else if (sprt->en_dat.state == DYING && sprt->kind == GUARD)
		return (sprt->en_dat.frame % 5 * 65);
	else if (sprt->en_dat.state == DYING && sprt->kind == DOG)
		return (sprt->en_dat.frame % 4 * 65);
	else if (sprt->en_dat.state == ATTACK)
		return (sprt->en_dat.frame % 3 * 65);
	else if (sprt->kind == DOG)
		return (3 * 65);
	return (4 * 65);
}
