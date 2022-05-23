/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/23 12:09:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//name
int	getwidth(char *line)
{
	int	i;
	int	temp;

	temp = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			temp--;
		else if (ft_isdigit(line[i]))
			temp++;
		i++;
	}
	return (temp);
}

//name
void	getwidtheight(char **upmap, t_data *data)
{
	int	i;
	int	temp;
	int	width;

	i = 0;
	width = INT32_MIN;
	while (upmap[i])
	{
		temp = getwidth(upmap[i]);
		if (temp > width)
			width = temp;
		i++;
	}
	data->level.map_w = width;
	data->level.map_h = i;
}

char	**parse_map(char **upmap, t_data *data)
{
	int	e_count;

	e_count = 0;
	if (!upmap || !*upmap)
		return (map_error_msg("Map is empty"));
	while (*upmap && ft_isalpha(*(*upmap)))
	{
		e_count++;
		upmap++;
	}
	if (e_count > 6)
	{
		printf("Map is misconfigured");
		return (NULL);
	}
	getwidtheight(upmap, data);
	if (!check_map_values(upmap, data))
		return (NULL);
	return (upmap);
}
