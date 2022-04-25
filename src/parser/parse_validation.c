/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_validation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:31:50 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/25 16:32:14 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	validchar(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E' \
		&& c != 'L' && c != 'B' && c != 'P' && c != 'D' && c != 'b' && c != 'G')
		return (false);
	return (true);
}

bool	validchar_space(char c)
{
	if (c != '1' && c != '0' \
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ' \
		&& c != 'L' && c != 'B' && c != 'P' && c != 'D' && c != 'b' && c != 'G')
		return (false);
	return (true);
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
