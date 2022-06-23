/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_btn_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:58:53 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:54:17 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	set_active_btn(t_ddlst *ddlst, t_map_edit *editor, t_vector_int pos, \
						mouse_key_t button)
{
	int				offset;

	if (is_mouse_in_rect(pos.x, pos.y, ddlst->open_rct))
	{
		offset = get_button_mouse_on(pos.x, pos.y, *ddlst);
		if (offset == -1)
			return ;
		if (button == MLX_MOUSE_BUTTON_LEFT)
		{
			if (editor->plane_ddlst.active.active == true)
			{
				editor->active_plane = offset;
				editor->active_sprite = 1;
			}
			else if (ddlst->active.active)
				editor->active_sprite = 1 + offset + ddlst->scroll_pos;
			ddlst->active.active = false;
			ddlst->active = ddlst->btn_lst[offset + ddlst->scroll_pos];
			ddlst->active.rect = ddlst->hvr_rct;
		}
	}
}

static void	change_scroll_pos(t_ddlst *drop, double y, t_vector_int pos)
{
	int	max_scroll;

	if (is_mouse_in_rect(pos.x, pos.y, drop->open_rct) && \
		drop->active.active == true)
	{
		if (y < 0)
			drop->scroll_pos++;
		else
			drop->scroll_pos--;
	}
	if (drop->scroll_pos < 0)
		drop->scroll_pos = 0;
	max_scroll = (int)drop->elements - drop->max_visible;
	if (drop->scroll_pos > max_scroll)
		drop->scroll_pos = max_scroll;
}

void	scroll_function_btn(double x, double y, void *param)
{
	t_vector_int	pos;
	t_data			*data;
	t_map_edit		*editor;
	t_sprt_drop		*sprt;

	(void)x;
	data = (t_data *)param;
	editor = &data->menu.editor;
	sprt = &editor->sprt_drops;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	if (editor->active_plane == 0)
		change_scroll_pos(&sprt->wall_ddlst, y, pos);
	else if (editor->active_plane == 1)
		change_scroll_pos(&sprt->zone_ddlst, y, pos);
	else if (editor->active_plane == 2)
		change_scroll_pos(&sprt->decor_ddlst, y, pos);
	else if (editor->active_plane == 3)
		change_scroll_pos(&sprt->item_ddlst, y, pos);
	else
		change_scroll_pos(&sprt->enemy_ddlst, y, pos);
	data->menu.update = true;
}

void	change_state_ddlst(t_map_edit *editor, mouse_key_t button, action_t action, \
							t_vector_int pos)
{
	t_sprt_drop	*sprt;
	t_sp_drop	*sp;

	sprt = &editor->sprt_drops;
	sp = &editor->sp_drops;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (!is_mouse_in_rect(pos.x, pos.y, editor->plane_ddlst.open_rct))
			editor->plane_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sp->rotate_ddlst.open_rct))
			sp->rotate_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sp->diff_ddlst.open_rct))
			sp->diff_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sprt->wall_ddlst.open_rct))
			sprt->wall_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sprt->decor_ddlst.open_rct))
			sprt->decor_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sprt->enemy_ddlst.open_rct))
			sprt->enemy_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sprt->item_ddlst.open_rct))
			sprt->item_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, sprt->zone_ddlst.open_rct))
			sprt->zone_ddlst.active.active = false;
	}
	set_btn_state(&editor->plane_ddlst.active, button, action, pos);
	if (editor->plane_ddlst.active.active == false)
	{
		set_btn_state(&sprt->wall_ddlst.active, button, action, pos);
		set_btn_state(&sprt->decor_ddlst.active, button, action, pos);
		set_btn_state(&sprt->enemy_ddlst.active, button, action, pos);
		set_btn_state(&sprt->item_ddlst.active, button, action, pos);
		set_btn_state(&sprt->zone_ddlst.active, button, action, pos);
		if (editor->active_plane == 4)
		{
			set_btn_state(&sp->rotate_ddlst.active, button, action, pos);
			set_btn_state(&sp->diff_ddlst.active, button, action, pos);
		}
	}
}

void	deactivate_other_paint_btns(t_pnt_btns *pnt, int activated)
{
	if (activated == 0)
	{
		pnt->area_btn.active = false;
		pnt->pen_btn.active = false;
		pnt->picker_btn.active = false;
	}
	else if (activated == 1)
	{
		pnt->area_btn.active = false;
		pnt->bucket_btn.active = false;
		pnt->picker_btn.active = false;
	}
	else if (activated == 2)
	{
		pnt->bucket_btn.active = false;
		pnt->pen_btn.active = false;
		pnt->picker_btn.active = false;
	}
	else if (activated == 3)
	{
		pnt->bucket_btn.active = false;
		pnt->pen_btn.active = false;
		pnt->area_btn.active = false;
	}
}

static void	set_btn_state_vis(mouse_key_t button, \
			action_t action, t_vector_int pos, t_vis_btns *vis)
{
	set_btn_state(&vis->enemy_btn, button, action, pos);
	set_btn_state(&vis->obj_btn, button, action, pos);
	set_btn_state(&vis->floor_btn, button, action, pos);
}

static void	set_btn_state_pnt(mouse_key_t button, \
			action_t action, t_vector_int pos, t_pnt_btns *pnt)
{
	if (set_btn_state(&pnt->bucket_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, 0);
	else if (set_btn_state(&pnt->pen_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, 1);
	else if (set_btn_state(&pnt->area_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, 2);
	else if (set_btn_state(&pnt->picker_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, 3);
}

static void	set_active_drop(t_map_edit *editor, mouse_key_t button, t_vector_int pos)
{
	t_sprt_drop	*sprt;
	t_sp_drop	*sp;
	int			active;

	sprt = &editor->sprt_drops;
	sp = &editor->sp_drops;
	active = editor->active_plane;
	if (editor->plane_ddlst.active.active == true)
		set_active_btn(&editor->plane_ddlst, editor, pos, button);
	if (sprt->wall_ddlst.active.active == true && active == 0)
		set_active_btn(&sprt->wall_ddlst, editor, pos, button);
	if (sprt->zone_ddlst.active.active == true && active == 1)
		set_active_btn(&sprt->zone_ddlst, editor, pos, button);
	else if (sprt->decor_ddlst.active.active == true && active == 2)
		set_active_btn(&sprt->decor_ddlst, editor, pos, button);
	else if (sprt->enemy_ddlst.active.active == true && active == 4)
		set_active_btn(&sprt->enemy_ddlst, editor, pos, button);
	else if (sprt->item_ddlst.active.active == true && active == 3)
		set_active_btn(&sprt->item_ddlst, editor, pos, button);
	else if (sp->rotate_ddlst.active.active == true)
		set_active_btn(&sp->rotate_ddlst, editor, pos, button);
	else if (sp->diff_ddlst.active.active == true)
		set_active_btn(&sp->diff_ddlst, editor, pos, button);
}

void	check_btns_clicked(t_data *data, mouse_key_t button, \
			action_t action, t_vector_int pos)
{
	t_map_edit	*editor;

	editor = &data->menu.editor;
	set_btn_state_vis(button, action, pos, &editor->vis_btns);
	if (editor->file.save_btn.active == false)
		set_btn_state(&editor->file.save_btn, button, action, pos);
	if (editor->file.save_btn.active == true)
		save_map(data);
	set_btn_state_pnt(button, action, pos, &editor->pnt_btns);
	change_state_ddlst(editor, button, action, pos);
	set_active_drop(editor, button, pos);
}
