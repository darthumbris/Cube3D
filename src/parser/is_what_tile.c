/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_what_tile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 09:36:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 11:28:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_player_tile(uint8_t c)
{
	return (c >= 1 && c <= 4);
}

bool	is_sprite_tile(uint8_t	c)
{
	return (c >= 1 && c <= 69);
}

bool	is_enemy_tile(uint8_t	c)
{
	return (c >= 5 && c <= 184);
}

bool	is_wall_tile(uint8_t c)
{
	return (c >= 1 && c <= 46);
}

bool	is_empty_tile(uint8_t c)
{
	return (c == 0 || (c >= 189 && c <= 225));
}

bool	is_door_tile(uint8_t c)
{
	return (c >= 169 && c <= 188);
}
