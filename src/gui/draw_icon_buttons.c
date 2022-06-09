/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_icon_buttons.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 12:06:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 12:22:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_icon_button(t_data *data, t_vector_int pos, \
		t_vector_int icon, double font_scale)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*atlas;

	pixel.x = 0;
	atlas = data->mlx.wall_icons->pixels;
	while (++pixel.x < 8 * font_scale)
	{
		tex.x = pixel.x * (2 / font_scale) + (icon.x * 16);
		menu = data->mlx.fg->pixels + (((pixel.x + pos.x + \
			(int)(94 * font_scale)) * 4) + \
			(pos.y * data->floor.width4));
		pixel.y = 8 * font_scale - 1;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * (2 / font_scale) + (icon.y * 16);
			*(uint32_t *)menu = (*(int *)(atlas + ((tex.y * \
				data->mlx.wall_icons->width + tex.x) * 4)));
			menu -= data->floor.width4;
		}
	}
}
