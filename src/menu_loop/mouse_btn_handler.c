/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_btn_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:58:53 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:06:49 by shoogenb      ########   odam.nl         */
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
	int				i;

	(void)x;
	data = (t_data *)param;
	editor = &data->menu.editor;
	sprt = &editor->sprt_drops;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	i = -1;
	while (++i < SPRITE_LSTS)
	{
		if (editor->active_plane == i)
			change_scroll_pos(&sprt->drop[i], y, pos);
	}
	data->menu.update = true;
}

void	change_state_ddlst(t_map_edit *editor, mouse_key_t button, action_t action, \
							t_vector_int pos)
{
	t_sprt_drop	*sprt;
	t_sp_drop	*sp;
	int			i;

	sprt = &editor->sprt_drops;
	sp = &editor->sp_drops;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (!is_mouse_in_rect(pos.x, pos.y, editor->plane_ddlst.open_rct))
			editor->plane_ddlst.active.active = false;
		i = -1;
		while (++i < SPRITE_LSTS)
		{
			if (!is_mouse_in_rect(pos.x, pos.y, sprt->drop[i].open_rct))
				sprt->drop[i].active.active = false;
			if (i < SPECIAL_LSTS && !is_mouse_in_rect(pos.x, pos.y, sp->drop[i].open_rct))
				sp->drop[i].active.active = false;
		}
	}
	set_btn_state(&editor->plane_ddlst.active, button, action, pos);
	if (editor->plane_ddlst.active.active == false)
	{
		i = -1;
		while (++i < SPRITE_LSTS)
		{
			set_btn_state(&sprt->drop[i].active, button, action, pos);
			if (editor->active_plane == 4 && i < SPECIAL_LSTS)
				set_btn_state(&sp->drop[i].active, button, action, pos);
		}
	}
}

void	deactivate_other_paint_btns(t_pnt_btns *pnt, int activated)
{
	int	i;

	i = -1;
	while (++i < PNT_BTNS)
	{
		if (i != activated)
			pnt->btns[i].active = false;
	}
}

static void	set_btn_state_vis(mouse_key_t button, \
			action_t action, t_vector_int pos, t_vis_btns *vis)
{
	int	i;

	i = -1;
	while (++i < DIS_BTNS)
		set_btn_state(&vis->btns[i], button, action, pos);
}

static void	set_btn_state_pnt(mouse_key_t button, \
			action_t action, t_vector_int pos, t_pnt_btns *pnt)
{
	if (set_btn_state(&pnt->btns[BUCKET], button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, BUCKET);
	else if (set_btn_state(&pnt->btns[PEN], button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, PEN);
	else if (set_btn_state(&pnt->btns[AREA], button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, AREA);
	else if (set_btn_state(&pnt->btns[PICKER], button, action, pos) == 2)
		deactivate_other_paint_btns(pnt, PICKER);
}

static void	set_active_drop(t_map_edit *editor, mouse_key_t button, t_vector_int pos)
{
	t_sprt_drop	*sprt;
	t_sp_drop	*sp;
	int			active;
	int			i;

	sprt = &editor->sprt_drops;
	sp = &editor->sp_drops;
	active = editor->active_plane;
	if (editor->plane_ddlst.active.active == true)
		set_active_btn(&editor->plane_ddlst, editor, pos, button);
	i = -1;
	while (++i < SPRITE_LSTS)
	{
		if (sprt->drop[i].active.active && active == i)
			set_active_btn(&sprt->drop[i], editor, pos, button);
	}
	if (sp->drop[ROTATION].active.active == true)
		set_active_btn(&sp->drop[ROTATION], editor, pos, button);
	else if (sp->drop[DIFFICULTY].active.active == true)
		set_active_btn(&sp->drop[DIFFICULTY], editor, pos, button);
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
