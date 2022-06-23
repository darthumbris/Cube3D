/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 14:17:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:31:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_text_drop(t_mlx *mlx, t_vector_int pos, t_ddlst ddlst)
{
	unsigned int	i;
	int				offset;

	i = ddlst.scroll_pos;
	offset = 0;
	while (offset < ddlst.max_visible)
	{
		pos.y = ddlst.btn_lst[offset].rect.pos0.y;
		if (pos.y < ddlst.open_rct.pos1.y)
			draw_str(mlx, ddlst.btn_lst[i].txt, pos, ddlst.font_scale);
		i++;
		offset++;
	}
}

static void	draw_icon_drop(t_mlx *mlx, t_vector_int pos, \
							t_ddlst drop, int active_plane)
{
	unsigned int	i;
	int				offset;
	t_vector_int	pos_icon[2];

	i = drop.scroll_pos;
	offset = 0;
	pos_icon[0] = pos;
	while (offset < drop.max_visible)
	{
		pos_icon[0].y = drop.btn_lst[offset].rect.pos0.y;
		pos_icon[0].x = drop.btn_lst[offset].rect.pos0.x;
		pos_icon[1] = drop.btn_lst[i].icon_pos;
		if (pos_icon[0].y < drop.open_rct.pos1.y)
			draw_icon_button(mlx, pos_icon, active_plane, \
				drop.font_scale);
		i++;
		offset++;
	}
}

void	draw_drop_down_lst(t_mlx *mlx, t_vector_int pos, \
			t_ddlst ddlst, bool icon, int active_plane)
{
	int				x;
	int				y;
	unsigned int	offset;
	t_vector_int	pos_icon[2];

	pos_icon[0] = pos;
	pos_icon[1] = ddlst.active.icon_pos;
	draw_str(mlx, ddlst.active.txt, pos, ddlst.font_scale);
	if (icon)
		draw_icon_button(mlx, pos_icon, active_plane, ddlst.font_scale);
	if (ddlst.active.active == true)
	{
		mlx_get_mouse_pos(mlx->mlx_handle, &x, &y);
		draw_rect(mlx->menu_editor, ddlst.open_rct, HOVER_COLOR);
		draw_text_drop(mlx, pos, ddlst);
		if (icon)
			draw_icon_drop(mlx, pos, ddlst, active_plane);
		if (is_mouse_in_rect(x, y, ddlst.open_rct))
		{
			offset = get_button_mouse_on(x, y, ddlst);
			if (offset >= 0 && offset < ddlst.elements)
				draw_rect_outline(mlx->menu_editor, \
					ddlst.btn_lst[offset].rect, \
					MAP_BORDER_COLOUR, 1 * ddlst.font_scale);
		}
	}
}

void	draw_drop_down_lsts(t_mlx *mlx, t_map_edit *ed)
{
	t_vector_int	pos;
	t_ddlst			plane;
	t_sprt_drop		*sprt;
	t_sp_drop		*sp;
	int				i;

	sprt = &ed->sprt_drops;
	sp = &ed->sp_drops;
	plane = ed->plane_ddlst;
	pos.y = plane.pos.y + 3 * plane.font_scale;
	pos.x = plane.pos.x;
	draw_drop_down_lst(mlx, pos, ed->plane_ddlst, false, ed->active_plane);
	pos.y = sprt->drop[0].pos.y + 1 * sprt->drop[0].font_scale;
	if (plane.active.active == false)
	{
		i = -1;
		while (++i < SPRITE_LSTS)
			if (ed->active_plane == i)
				draw_drop_down_lst(mlx, pos, sprt->drop[i], true, ed->active_plane);
		if (ed->active_plane == 4)
		{
			pos.y = sp->drop[ROTATION].pos.y + 2 * plane.font_scale;
			draw_drop_down_lst(mlx, pos, sp->drop[0], false, ed->active_plane);
			pos.y = sp->drop[DIFFICULTY].pos.y + 2 * plane.font_scale;
			if (sp->drop[ROTATION].active.active == false)
				draw_drop_down_lst(mlx, pos, sp->drop[1], false, ed->active_plane);
		}
	}
}
