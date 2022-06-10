/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 17:13:54 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/10 14:13:48 by shoogenb      ########   odam.nl         */
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

bool	checks(char **upmap, int i, int j, t_data *data)
{
	return (((upmap[i][j] == '0' || is_player_tile(upmap[i][j]) || \
		is_sprite_tile(upmap[i][j]) || is_door_tile(upmap[i][j]) || \
		is_secret_tile(upmap[i][j])) \
		&& verifyzero(upmap, i, j, data) == false && \
		verifyspace(upmap, i, j, data) == false));
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
			else if (is_secret_tile(upmap[i][j]))
				data->level.secret_count++;
		}
	}
	return (false);
}

char	**parse_map(char **upmap, t_data *data)
{
	int	p_count;
	int	e_count;

	p_count = 0;
	e_count = 0;
	if (!upmap || !*upmap)
		return (map_error_msg("Map is empty"));
	while (*upmap && ft_isalpha(*(*upmap)))
	{
		e_count++;
		upmap++;
	}
	if (e_count > 6 && !data->bonus)
		return (map_error_msg("Map is misconfigured"));
	getwidtheight(upmap, data);
	if (data->level.map_w < 3 || data->level.map_h < 3)
		map_error_msg("Map is misconfigured");
	if (norm_loop(data, upmap, &p_count))
		return (map_error_msg("Map is misconfigured"));
	if (p_count != 1)
		return (map_error_msg("Player is misconfigured"));
	return (upmap);
}
