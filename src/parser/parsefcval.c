/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsefcval.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:07:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 17:24:17 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//stores floor and ceiling rgb values, 

int	*getrgbval(char *line)
{
	int	r;
	int	g;
	int	b;

	line += 1;
	while (*line == ' ')
		line++;
	if (!*line || ft_strlen(line) < 5)
		return (NULL);
	r = ft_atoi(line++);
	while (*line && *(line - 1) != ',')
		line++;
	if (!*line)
		return (NULL);
	g = ft_atoi(line++);
	while (*line && *(line - 1) != ',')
		line++;
	if (!*line)
		return (NULL);
	b = ft_atoi(line);
	return ((int []){r, g, b});
}

void	f_store(char *line, t_data *data)
{
	const int		*rgb = getrgbval(line);

	if (!rgb)
	{
		data->level.floor_color = -1;
		return ;
	}
	data->level.floor_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
}

void	c_store(char *line, t_data *data)
{
	const int		*rgb = getrgbval(line);

	if (!rgb)
	{
		data->level.ceiling_color = -1;
		return ;
	}
	data->level.ceiling_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
}
