/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/14 15:56:13 by pvan-dij      ########   odam.nl         */
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

bool	validchar(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (false);
	return (true);
}

bool	validchar_space(char c)
{
	if (c != '1' && c != '0' \
		&& c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ')
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

char	**parse_map(char **upmap, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isalpha(*(*upmap)))
		upmap++;
	getwidtheight(upmap, data);
	while (upmap[i])
	{
		j = 0;
		while (upmap[i][j])
		{
			if (validchar_space(upmap[i][j]) == false || \
				(upmap[i][j] == '0' && verifyzero(upmap, i, j, data) == false))
			{
				return (NULL); //free shit
			}
			j++;
		}
		i++;
	}
	return (upmap);
}
