/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst_utils.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:59:00 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 09:02:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_rect(t_data *data, t_rect rec, uint32_t color)
{
	uint8_t			*map;
	int				y;
	int				x;

	y = rec.pos0.y;
	map = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)data->mlx.fg->width)
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = color;
		y++;
	}
}

static void	draw_vertical_line(t_data *data, t_rect rec, uint32_t c, \
								int thickness)
{
	int		y;
	uint8_t	*menu;
	int		pixels;

	y = rec.pos0.y - 1;
	menu = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		pixels = 0;
		while (pixels < thickness)
		{
			*(uint32_t *)(menu + ((y * data->mlx.fg->width + rec.pos1.x + \
				pixels) * 4)) = c;
			*(uint32_t *)(menu + ((y * data->mlx.fg->width + rec.pos0.x - \
				pixels) * 4)) = c;
			pixels++;
		}
		y++;
	}
}

void	draw_rect_outline(t_data *data, t_rect rec, uint32_t c, \
			int thickness)
{
	uint8_t	*menu;
	int		x;
	int		pixels;

	draw_vertical_line(data, rec, c, thickness);
	menu = data->mlx.fg->pixels;
	x = rec.pos0.x;
	if (x < 0)
		x = 0;
	while (x < rec.pos1.x && x < (int)data->mlx.fg->width)
	{
		pixels = -thickness;
		while (pixels < thickness)
		{
			*(uint32_t *)(menu + (((rec.pos0.y + pixels) * \
				data->mlx.fg->width + x) * 4)) = c;
			*(uint32_t *)(menu + (((rec.pos1.y + pixels) * \
				data->mlx.fg->width + x) * 4)) = c;
			pixels++;
		}
		x++;
	}
}
