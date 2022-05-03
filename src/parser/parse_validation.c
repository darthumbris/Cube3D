/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:31:50 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/03 16:09:57 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	validchar(char c)
{
	return ((is_player_tile(c) || is_sprite_tile(c) || is_wall_tile(c) || \
			is_empty_tile(c)) || is_finish_tile(c) || is_door_tile(c));
}

bool	validchar_space(char c)
{
	return (!(!validchar(c) && c != ' '));
}

//checks wether 0 is valid. if there are non digits around it, it is not
bool	verifyzero(char **upmap, int i, int j, t_data *data)
{
	if (i + 1 > data->level.map_h || i - 1 < 0 \
		|| j + 1 > (int)ft_strlen(upmap[i]) || j - 1 < 0)
		return (false);
	if (!validchar(upmap[i][j + 1]) || !validchar(upmap[i][j - 1]) || \
		!validchar(upmap[i + 1][j]) || !validchar(upmap[i - 1][j]))
		return (false);
	return (true);
}
