/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_lst.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 14:53:55 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 15:49:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_wall_lst(int tile)
{
	return (tile >= 1 && tile <= 188);
}

bool	is_zone_lst(int tile)
{
	return (tile >= 189 && tile <= 225);
}

bool	is_decor_lst(int tile)
{
	return (tile >= 1 && tile <= 49);
}

bool	is_item_lst(int tile)
{
	return (tile >= 50 && tile <= 69);
}

bool	is_movable_lst(int tile)
{
	return (tile >= 1 && tile <= 250);
}
