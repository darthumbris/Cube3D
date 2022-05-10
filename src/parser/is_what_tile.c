/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_what_tile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 09:36:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 16:17:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

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
			c == '$');
}

bool	is_wall_tile(char c)
{
	return (c == '1' || c == '2' || c == '3' || c == '4' || \
			c == '5' || c == '6' || c == '7' || c == '8' || \
			c == '9' || c == '*' || c == '-');
}

bool	is_empty_tile(char c)
{
	return (c == '0');
}

bool	is_door_tile(char c)
{
	return (c == 'D' || c == 'd');
}
