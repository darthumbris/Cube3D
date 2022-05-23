/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsefcval.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:07:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/23 13:09:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_color_value(char *line, int *color, bool last)
{
	int	i;

	i = 0;
	*color = -1;
	while (ft_isdigit(line[i]))
		i++;
	if (i > 3 || i == 0)
		return ;
	if (i == 3 && ft_atoi(line) > 255)
		return ;
	if (last && (line[i] != '\n' && line[i] != '\0'))
		return ;
	if (!last && line[i] != ',')
		return ;
	*color = ft_atoi(line);
}

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
	set_color_value(line, &r, false);
	while (*line && *(line - 1) != ',')
		line++;
	if (!*line)
		return (NULL);
	set_color_value(line, &g, false);
	while (*line && ft_isdigit(*line))
		line++;
	line++;
	if (!*line)
		return (NULL);
	set_color_value(line, &b, true);
	if (r == -1 || b == -1 || g == -1)
		return (NULL);
	return ((int []){r, g, b});
}

void	color_store(char *line, t_data *data, int kind)
{
	const int		*rgb = getrgbval(line);

	if (!rgb)
	{
		if (kind == 0)
			data->level.floor_color = -1;
		else
			data->level.ceiling_color = -1;
		data->level.colors_error = true;
		return ;
	}
	if (kind == 0)
		data->level.floor_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
	else
		data->level.ceiling_color = \
			(rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + (255);
}
