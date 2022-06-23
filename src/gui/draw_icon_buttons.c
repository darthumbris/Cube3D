/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_icon_buttons.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 12:06:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:53:15 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

mlx_texture_t	*get_icon_texture(t_mlx *mlx, int plane)
{
	if (plane == 0)
		return (mlx->wall_icons);
	else if (plane == 1)
		return (mlx->zone_icons);
	else if (plane == 2)
		return (mlx->obj_icons);
	else if (plane == 3)
		return (mlx->item_icons);
	else
		return (mlx->enmy_icons);
}

void	draw_icon_button(t_mlx *mlx, t_vector_int pos_icon[2], \
		int active_plane, double font_scale)
{
	mlx_texture_t	*atlas;
	int				wh[2];

	wh[0] = 16;
	wh[1] = 16;
	atlas = get_icon_texture(mlx, active_plane);
	pos_icon[0].x += 94 * font_scale;
	draw_texture_area
		(mlx->menu_editor, atlas, pos_icon[0], pos_icon[1], wh, font_scale / 2);
}
