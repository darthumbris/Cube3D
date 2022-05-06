/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/04 20:20:41 by pvan-dij      ########   odam.nl         */
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
		if (ft_isdigit(line[i]) || line[i] == ' ')
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
		temp = ft_strlen(upmap[i]);
		if (temp > width)
			width = temp;
		i++;
	}
	data->level.map_w = width;
	data->level.map_h = i;
}

//TODO: check if player start on edge of map if this fails
bool	checks(char **upmap, int i, int j, t_data *data)
{
	return (validchar_space(upmap[i][j]) == false || \
		((upmap[i][j] == '0' || is_player_tile(upmap[i][j]) || \
		is_sprite_tile(upmap[i][j])) \
		&& verifyzero(upmap, i, j, data) == false));
}

bool	norm_loop(t_data *data, char **upmap, int *count)
{
	int	i;
	int	j;
	i = -1;
	while (upmap[++i])
	{
		j = -1;
		while (upmap[i][++j])
		{
			if (checks(upmap, i, j, data))
				return (true);
			if (is_player_tile(upmap[i][j]))
				(*count)++;
			else if (is_sprite_tile(upmap[i][j]))
				data->level.number_of_sprites++;
			else if (is_door_tile(upmap[i][j]))
				data->level.door_count++;
		}
	}
	return (false);
}

char	**parse_map(char **upmap, t_data *data)
{
	int	count;
	int	sprites;

	count = 0;
	sprites = 0;
	if (!upmap || !*upmap)
		return (NULL);
	while (*upmap && ft_isalpha(*(*upmap)))
		upmap++;
	getwidtheight(upmap, data);
	if (norm_loop(data, upmap, &count))
		return (NULL);
	if (count > 1)
		return (NULL);
	return (upmap);
}

//TODO: check multiple start