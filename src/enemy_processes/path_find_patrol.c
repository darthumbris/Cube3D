/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_patrol.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 14:36:16 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/16 17:08:24 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	patrol_routine(t_data *data, t_sprite *enemy)
{
	t_vector_double	temp;
	double			speed;
	char			c;

	if (enemy->kind == GUARD)
		speed = GUARD_MOVE_SPEED;
	else
		speed = DOG_MOVE_SPEED;
	temp.x = enemy->map_pos.x + speed * enemy->en_dat.dir.x;
	temp.y = enemy->map_pos.y + speed * enemy->en_dat.dir.y;
	c = data->level.map[(int)(temp.y + 0.5 * enemy->en_dat.dir.y)] \
		[(int)(temp.x + 0.5 * enemy->en_dat.dir.x)];
	if (is_wall_tile(c) || is_door_tile(c) || is_secret_tile(c))
	{
		enemy->en_dat.dir.x = -enemy->en_dat.dir.x;
		enemy->en_dat.dir.y = -enemy->en_dat.dir.y;
		return ;
	}
	enemy->map_pos.x = temp.x;
	enemy->map_pos.y = temp.y;
	enemy->en_dat.counter++;
	if (enemy->en_dat.counter > 50)
		enemy->en_dat.counter = 0;
	if (enemy->en_dat.counter % 7 == 0)
		enemy->en_dat.frame++;
	if ((enemy->kind == DOG && enemy->en_dat.frame > 3) || \
		(enemy->kind == GUARD && enemy->en_dat.frame > 4))
		enemy->en_dat.frame = 0;
}
