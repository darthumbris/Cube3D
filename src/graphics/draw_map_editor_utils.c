/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 10:04:36 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

unsigned int	get_color_tile(int tile)
{
	if (tile == 1)
		return (0x8f8f8fff);
	else if (tile == 2)
		return (0x0000b3ff);
	else if (tile == 3)
		return (0x774e2bff);
	return (0x8f8f8fff);
}
