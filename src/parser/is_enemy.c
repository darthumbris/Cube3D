/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_enemy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:27:14 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 12:44:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_dog_tile(char c)
{
	return (c == 'c' || c == '(' || c == ')' || c == '#' || c == '%');
}

bool	is_guard_tile(char c)
{
	return (c == 'G' || c == '[' || c == ']' || c == '@' || c == '!');
}

bool	is_enemy_tile(char c)
{
	return (c == 'G' || c == 'c' || c == '[' || c == ']' || \
			c == '@' || c == '!' || c == '(' || c == ')' || \
			c == '#' || c == '%');
}

bool	is_block_patrol_tile(char c)
{
	return (is_wall_kind_tile(c) || c == 'B' || c == 'P' || c == 't' \
			|| c == 'f' || c == 'w' || c == 'p' || c == 'T' || c == 's' \
			|| c == 'l' || c == 'g' || c == 'o' || c == 'a' || c == 'A');
}
