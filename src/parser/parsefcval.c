/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsefcval.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:07:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/14 17:14:56 by pvan-dij      ########   odam.nl         */
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
	r = ft_atoi(line++);
	while (*line && *(line - 1) != ',')
		line++;
	g = ft_atoi(line++);
	while (*line && *(line - 1) != ',')
		line++;
	b = ft_atoi(line);
	return ((int []){r, g, b});
}

void	f_store(char *line, t_data *data)
{
	const int		*rgb = getrgbval(line);

	data->level.floor_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
}

void	c_store(char *line, t_data *data)
{
	const int		*rgb = getrgbval(line);

	data->level.ceiling_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
}
