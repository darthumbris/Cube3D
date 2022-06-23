/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst_utils.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:59:00 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 12:56:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_rect(mlx_image_t *menu_img, t_rect rec, uint32_t color)
{
	uint8_t			*map;
	int				y;
	int				x;

	y = rec.pos0.y - 1;
	map = menu_img->pixels;
	if (y < -1)
		y = -1;
	while (++y < rec.pos1.y && y < (int)menu_img->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)menu_img->width)
			*(uint32_t *)(map + ((y * menu_img->width + x) * 4)) = color;
	}
}

static void	draw_vertical_line(mlx_image_t *menu_img, t_rect rec, uint32_t c, \
								int thickness)
{
	int		y;
	uint8_t	*menu;
	int		pixels;

	y = rec.pos0.y - 2;
	menu = menu_img->pixels;
	if (y < -1)
		y = -1;
	while (++y < rec.pos1.y && y < (int)menu_img->height)
	{
		pixels = 0;
		while (pixels < thickness)
		{
			*(uint32_t *)(menu + ((y * menu_img->width + rec.pos1.x + \
				pixels) * 4)) = c;
			*(uint32_t *)(menu + ((y * menu_img->width + rec.pos0.x - \
				pixels) * 4)) = c;
			pixels++;
		}
	}
}

void	draw_rect_outline(mlx_image_t *menu_img, t_rect rec, uint32_t c, \
			int thickness)
{
	uint8_t	*menu;
	int		x;
	int		pixels;

	draw_vertical_line(menu_img, rec, c, thickness);
	menu = menu_img->pixels;
	x = rec.pos0.x - 1;
	if (x < -1)
		x = -1;
	while (++x < rec.pos1.x && x < (int)menu_img->width)
	{
		pixels = -thickness - 1;
		while (++pixels < thickness)
		{
			*(uint32_t *)(menu + (((rec.pos0.y + pixels) * \
				menu_img->width + x) * 4)) = c;
			*(uint32_t *)(menu + (((rec.pos1.y + pixels) * \
				menu_img->width + x) * 4)) = c;
		}
	}
}
