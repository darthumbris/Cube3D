/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 14:17:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 14:20:44 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_text_drop(t_data *data, t_vector_int pos, t_ddlst ddlst)
{
	unsigned int	i;
	int				offset;

	i = ddlst.scroll_pos;
	offset = 0;
	while (offset < ddlst.max_visible)
	{
		pos.y = ddlst.btn_lst[offset].rect.pos0.y;
		if (pos.y < ddlst.open_rct.pos1.y)
			draw_str(data, ddlst.btn_lst[i].txt, pos, ddlst.font_scale);
		i++;
		offset++;
	}
}

static void	draw_icon_drop(t_data *data, t_vector_int pos, t_ddlst drop)
{
	unsigned int	i;
	int				offset;

	i = drop.scroll_pos;
	offset = 0;
	while (offset < drop.max_visible)
	{
		pos.y = drop.btn_lst[offset].rect.pos0.y;
		if (pos.y < drop.open_rct.pos1.y)
			draw_icon_button(data, pos, drop.btn_lst[i].icon_pos, \
				drop.font_scale);
		i++;
		offset++;
	}
}

void	draw_drop_down_lst(t_data *data, t_vector_int pos, \
			t_ddlst ddlst, bool icon)
{
	int				x;
	int				y;
	unsigned int	offset;

	draw_str(data, ddlst.active.txt, pos, ddlst.font_scale);
	if (icon)
		draw_icon_button(data, pos, ddlst.active.icon_pos, ddlst.font_scale);
	if (ddlst.active.active == true)
	{
		mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
		draw_rect(data, ddlst.open_rct, HOVER_COLOR);
		draw_text_drop(data, pos, ddlst);
		if (icon)
			draw_icon_drop(data, pos, ddlst);
		if (is_mouse_in_rect(x, y, ddlst.open_rct))
		{
			offset = get_button_mouse_on(x, y, ddlst);
			if (offset >= 0 && offset < ddlst.elements)
			{
				draw_rect_outline(data, ddlst.btn_lst[offset].rect, \
					MAP_BORDER_COLOUR, 1 * ddlst.font_scale);
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
	floor = data->menu.wall_ddlst;
	pos.y = plane.pos.y + 3 * plane.font_scale;
	pos.x = plane.pos.x;
	draw_drop_down_lst(data, pos, data->menu.plane_ddlst, false);
	pos.y = floor.pos.y + 2 * floor.font_scale;
	if (plane.active.active == false)
	{
		if (data->menu.active_plane == 0)
			draw_drop_down_lst(data, pos, data->menu.wall_ddlst, true);
		else if (data->menu.active_plane == 1)
			draw_drop_down_lst(data, pos, data->menu.zone_ddlst, true);
		else if (data->menu.active_plane == 2)
			draw_drop_down_lst(data, pos, data->menu.decor_ddlst, true);
		else if (data->menu.active_plane == 3)
			draw_drop_down_lst(data, pos, data->menu.item_ddlst, true);
		else
			draw_drop_down_lst(data, pos, data->menu.enemy_ddlst, true);
	}
}
