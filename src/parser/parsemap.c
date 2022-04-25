/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/25 10:43:37 by shoogenb      ########   odam.nl         */
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

bool	playerposcheck(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

bool	sprite_check(char c)
{
	return (c == 'L' || c == 'B' || c == 'P');
}

//TODO: check if player start on edge of map if this fails
bool	checks(char **upmap, int i, int j, t_data *data)
{
	return (validchar_space(upmap[i][j]) == false || \
		((upmap[i][j] == '0' || playerposcheck(upmap[i][j]) || \
		sprite_check(upmap[i][j])) \
		&& verifyzero(upmap, i, j, data) == false));
}

char	**parse_map(char **upmap, t_data *data)
{
	int	i;
	int	j;
	int	count;
	int	sprites;

	count = 0;
	sprites = 0;
	if (!upmap || !*upmap)
		return (NULL);
	while (*upmap && ft_isalpha(*(*upmap)))
		upmap++;
	getwidtheight(upmap, data);
	i = -1;
	while (upmap[++i])
	{
		j = -1;
		while (upmap[i][++j])
		{
			if (checks(upmap, i, j, data))
			{
				printf("fails this at: %d, %d with char: %c\n", i, j, upmap[i][j]);
				return (NULL);
			}
			if (playerposcheck(upmap[i][j]))
				count++;
			if (sprite_check(upmap[i][j]))
				sprites++;
		}
	}
	if (count > 1)
		return (NULL);
	data->level.number_of_sprites = sprites;
	return (upmap);
}

//TODO: check multiple start