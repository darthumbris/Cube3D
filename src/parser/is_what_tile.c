/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_what_tile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 09:36:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 15:51:33 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_player_tile(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

bool	is_sprite_tile(char c)
{
	return (c == 'L' || c == 'B' || c == 'P' \
			|| c == 'b' || c == 'G' || c == 'c' || \
			c == 't' || c == 'w' || c == 'f' || c == 'C' || \
			c == 'p' || c == 'T' || c == 's' || \
			c == 'l' || c == 'g' || c == 'o' || c == 'a' || \
			c == 'A' || c == 'e' || c == 'F' || c == 'i' || \
			c == 'I' || c == 'j' || c == 'J' || c == 'k' || \
			c == 'K' || c == 'm' || c == '+' || c == '&' || \
			c == '$' || is_enemy_tile(c));
}

bool	is_wall_tile(uint8_t c)
{
	return (c >= 1 && c <= 45);
}

bool	is_empty_tile(char c)
{
	return (c == '0');
}

bool	is_door_tile(uint8_t c)
{
	return (c >= 169 && c <= 188);
}
