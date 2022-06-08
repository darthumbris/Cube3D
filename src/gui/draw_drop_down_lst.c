/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 14:17:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 16:35:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_text_drop(t_data *data, t_vector_int pos, t_ddlst ddlst, \
							int y_pos)
{
	unsigned int	i;

	i = 0;
	while (i < ddlst.elements)
	{
		pos.y = y_pos + 9 * ddlst.font_scale * (i + 1);
		if (pos.y < ddlst.open_rct.pos1.y)
			draw_str(data, ddlst.btn_txt[i], pos, ddlst.font_scale);
		i++;
	}
}

void	draw_drop_down_lst(t_data *data, t_vector_int pos, t_ddlst ddlst, \
			int y_pos)
{
	int				x;
	int				y;
	unsigned int	offset;

	draw_str(data, ddlst.active.txt, pos, ddlst.font_scale);
	if (ddlst.active.active == true)
	{
		mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
		draw_rect(data, ddlst.open_rct, HOVER_COLOR);
		draw_text_drop(data, pos, ddlst, y_pos);
		if (is_mouse_in_rect(x, y, ddlst.open_rct))
		{
			offset = get_button_mouse_on(x, y, ddlst);
			if (offset >= 0 && offset < ddlst.elements)
			{
				draw_rect_outline(data, ddlst.btn_lst[offset].rect, \
					MAP_BORDER_COLOUR, 1 * data->hud.scale);
			}
		}
	}
}

void	draw_drop_down_lsts(t_data *data)
{
	t_vector_int	pos;
	t_ddlst			plane;
	t_ddlst			floor;

	plane = data->menu.plane_ddlst;
	floor = data->menu.floor_ddlst;
	pos.y = plane.pos.y + 9 * plane.font_scale;
	pos.x = plane.pos.x;
	draw_drop_down_lst(data, pos, data->menu.plane_ddlst, pos.y);
	pos.y = floor.pos.y + 9 * floor.font_scale;
	if (plane.active.active == false)
		draw_drop_down_lst(data, pos, data->menu.floor_ddlst, pos.y);
}
