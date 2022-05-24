/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:04:35 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/24 13:43:36 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	error_msg(char *msg)
{
	printf("Error: %s\n", msg);
	return (false);
}

static bool	playerposcheck(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

static bool	checks(char **upmap, int i, int j, t_data *data)
{
	if (validchar_space(upmap[i][j]) == false || \
		((upmap[i][j] == '0' || playerposcheck(upmap[i][j])) && \
			verifyzero(upmap, i, j, data) == false))
		return (true);
	return (false);
}

bool	check_map_values(char **upmap, t_data *data)
{
	int	i;
	int	j;
	int	p_count;

	i = -1;
	p_count = 0;
	while (upmap[++i])
	{
		j = -1;
		while (upmap[i][++j])
		{
			if (checks(upmap, i, j, data))
				return (false);
			if (playerposcheck(upmap[i][j]))
				p_count++;
		}
	}
	if (p_count != 1)
		return (false);
	return (true);
}
