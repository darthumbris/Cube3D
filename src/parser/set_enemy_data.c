/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_enemy_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:05:05 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 16:06:42 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
GW,[,GUARD_WEST
GE,],GUARD_EAST
GS,@,GUARD_SOUTH
GN,!,GUARD_NORTH
*/
static	t_vector_double	get_direction_enemy(char c)
{
	if (c == '[' || c == 'G' || c == 'c' || c == '(')
		return ((t_vector_double){-1.0, 0.0});
	else if (c == ']' || c == ')')
		return ((t_vector_double){+1.0, 0.0});
	else if (c == '@' || c == '#')
		return ((t_vector_double){0.0, +1.0});
	else
		return ((t_vector_double){0.0, -1.0});
}

void	set_enemy_data(t_sprite *sprite, char **map, t_vector_int pos, \
							t_data *data)
{
	sprite->en_dat.player_detected = false;
	sprite->en_dat.state = ALIVE;
	if (sprite->kind == GUARD)
	{
		sprite->en_dat.health = 25;
		sprite->en_dat.speed = GUARD_MOVE_SPEED;
	}
	else if (sprite->kind == DOG)
	{
		sprite->en_dat.health = 1;
		sprite->en_dat.speed = DOG_MOVE_SPEED;
	}
	sprite->en_dat.dir = get_direction_enemy(map[pos.y][pos.x]);
	if (is_enemy_patrol(data, sprite))
		sprite->en_dat.state = PATROLLING;
	sprite->en_dat.frame = 0;
	sprite->en_dat.counter = 0;
	sprite->en_dat.last_attack = 0;
}
