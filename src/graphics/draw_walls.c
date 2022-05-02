/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:12:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/02 15:13:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

uint8_t	*get_pixels(t_data *data, char c)
{
	if (!data->bonus)
		return (data->mlx.tex.texarr[data->caster.side]->pixels);
	else if (c == 'D')
		return (data->mlx.tex.texarr[SPRITE_3]->pixels);
	else if (c == 'h')
		return (data->mlx.tex.texarr[SPRITE_6]->pixels);
	else
		return (data->mlx.tex.texarr[c - '1' + WALL_1]->pixels);
}

int	get_width(t_data *data, char c)
{
	if (!data->bonus)
		return (data->mlx.tex.texarr[data->caster.side]->width);
	else if (c == 'D')
		return (data->mlx.tex.texarr[SPRITE_3]->width);
	else if (c == 'h')
		return (data->mlx.tex.texarr[SPRITE_6]->width);
	else
		return (data->mlx.tex.texarr[c - '1' + WALL_1]->width);
}

int	get_height(t_data *data, char c)
{
	if (!data->bonus)
		return (data->mlx.tex.texarr[data->caster.side]->height);
	else if (c == 'D')
		return (data->mlx.tex.texarr[SPRITE_3]->height);
	else if (c == 'h')
		return (data->mlx.tex.texarr[SPRITE_6]->height);
	else
		return (data->mlx.tex.texarr[c - '1' + WALL_1]->height);
}

void	draw_walls(t_data *data)
{
	int				y;
	uint8_t			*pix[2];
	const char		c = data->level.map[data->caster.map_pos.y] \
		[data->caster.map_pos.x];
	const int		width = get_width(data, c);
	const double	step = (get_height(data, c) / \
		(double)data->caster.line_height);

	y = data->caster.draw_start;
	data->caster.tex_x = (int)(data->caster.wall_x * \
		(double)(width - 1));
	data->caster.tex_y = (y - data->floor.halve_height + \
		(data->caster.line_height >> 1)) * step;
	pix[0] = get_pixels(data, data->level.map[data->caster.map_pos.y] \
		[data->caster.map_pos.x]);
	pix[1] = data->mlx.fg->pixels + ((y * data->floor.width4) + data->floor.x4);
	while (y < data->caster.draw_end)
	{
		*(uint32_t *)pix[1] = (*(int *)(pix[0] + \
		(((int)data->caster.tex_y * width + data->caster.tex_x) << 2)));
		pix[1] += data->floor.width4;
		data->caster.tex_y += step;
		y++;
	}
}
