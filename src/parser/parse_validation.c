/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:31:50 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/20 09:45:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	validchar(uint8_t c)
{
	return ((is_wall_tile(c) || is_empty_tile(c)) || is_door_tile(c));
}

//checks wether 0 is valid. if there are non digits around it, it is not
bool	verifyzero(uint8_t	***map, int i, int j, t_data *data)
{
	if (i + 1 > data->level.map_h || i - 1 < 0 \
		|| j + 1 > data->level.map_w || j - 1 < 0)
		return (false);
	if (!validchar(map[i][j + 1][0]) || !validchar(map[i][j - 1][0]) || \
		!validchar(map[i + 1][j][0]) || !validchar(map[i - 1][j][0]))
		return (false);
	return (true);
}

//checks wether 0 is valid. if there are non digits around it, it is not
bool	verifyspace(uint8_t	***map, int i, int j, t_data *data)
{
	if (i + 1 > data->level.map_h || i - 1 < 0 \
		|| j + 1 > data->level.map_w || j - 1 < 0)
		return (false);
	if (!is_wall_tile(map[i][j + 1][0]) || !is_wall_tile(map[i][j - 1][0]) || \
		!is_wall_tile(map[i + 1][j][0]) || !is_wall_tile(map[i - 1][j][0]))
		return (false);
	return (true);
}
