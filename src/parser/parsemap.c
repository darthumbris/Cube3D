/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/21 17:09:06 by shoogenb      ########   odam.nl         */
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

bool	checks(uint8_t	***map, int i, int j, t_data *data)
{
	return (((is_empty_tile(map[i][j][0]) || is_door_tile(map[i][j][0])) \
		&& verifyzero(map, i, j, data) == false && \
		verifyspace(map, i, j, data) == false));
}

bool	norm_loop(t_data *data, uint8_t	***map, int *count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->level.map_h)
	{
		j = -1;
		while (++j < data->level.map_w)
		{
			if (checks(map, i, j, data))
				return (true);
			if (is_player_tile(map[i][j][2]))
				(*count)++;
			else if (is_sprite_tile(map[i][j][2] || is_sprite_tile(map[i][j][1])))
				data->level.number_of_sprites++;
			else if (is_door_tile(map[i][j][0]))
				data->level.door_count++;
			else if (is_secret_tile(map[i][j][2]))
				data->level.secret_count++;
		}
	}
	return ((*count) == 1);
}

bool	parse_map(uint8_t	***map, t_data *data)
{
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	if (!map)
		return (error_msg("Map is empty"));
	if (norm_loop(data, map, &p_count))
		return (error_msg("Map is misconfigured"));
	if (p_count != 1)
		return (error_msg("Player is misconfigured"));
	return (true);
}
