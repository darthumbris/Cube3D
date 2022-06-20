/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   special_tiles.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 16:43:19 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 11:26:39 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_finish_tile(char c)
{
	return (c == '*');
}

bool	is_item(int kind)
{
	return (kind >= AMMO && kind <= GOLD_KEY);
}

bool	is_nonblocking_kind(int kind)
{
	return (kind == LAMP_G || kind == LAMP_R || (kind >= 2 && kind <= 9)
		|| is_enemy_kind(kind) || kind == BLOOD_PUDDLE || kind == VINES || \
		kind == PANS1 || kind == PANS2 || kind == PUDDLE_WTR || \
		kind == CHANDELIER || is_item(kind));
}

bool	is_secret_tile(uint8_t c)
{
	return (c >= 250 && c <= 253);
}

bool	is_wall_kind_tile(uint8_t c)
{
	return (is_wall_tile(c) || is_door_tile(c));
}
