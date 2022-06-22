/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_icon_buttons.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 12:06:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 16:29:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

mlx_texture_t	*get_icon_texture(t_data *data, int plane)
{
	if (plane == 0)
		return (data->mlx.wall_icons);
	else if (plane == 1)
		return (data->mlx.zone_icons);
	else if (plane == 2)
		return (data->mlx.obj_icons);
	else if (plane == 3)
		return (data->mlx.item_icons);
	else
		return (data->mlx.enmy_icons);
}

void	draw_icon_button(t_data *data, t_vector_int pos, \
		t_vector_int icon, double font_scale)
{
	mlx_texture_t	*atlas;
	int				wh[2];

	wh[0] = 16;
	wh[1] = 16;
	atlas = get_icon_texture(data, data->menu.active_plane);
	pos.x += 94 * font_scale;
	draw_texture_area
		(data->mlx.menu_editor, atlas, pos, icon, wh, font_scale / 2);
}
