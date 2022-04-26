/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_what_tile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 09:36:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/26 14:06:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_player_tile(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

bool	is_sprite_tile(char c)
{
	return (c == 'L' || c == 'B' || c == 'P' || c == 'D' \
			|| c == 'b' || c == 'G' || c == 'h');
}

bool	is_wall_tile(char c)
{
	return (c == '1');
}

bool	is_empty_tile(char c)
{
	return (c == '0');
}

bool	is_door_tile(char c)
{
	return (c == 'D' || c == 'h');
}
