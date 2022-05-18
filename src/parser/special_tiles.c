/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   special_tiles.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 16:43:19 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 15:41:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_finish_tile(char c)
{
	return (c == '*');
}

bool	is_item(int kind)
{
	return (kind >= STIMULANT && kind <= TREASURE_2);
}

bool	is_nonblocking_kind(int kind)
{
	return (kind == LAMP || kind == GUARD || kind == DOG || kind == BONES || \
		kind == CHANDELIER || is_item(kind) || kind == BONES_2 || \
		kind == DEAD_GUARD || kind == PUDDLE);
}

bool	is_secret_tile(char c)
{
	return (c == '<' || c == '{' || c == '^' || c == '_');
}

bool	is_wall_kind_tile(char c)
{
	return (is_wall_tile(c) || is_door_tile(c) || is_secret_tile(c));
}
