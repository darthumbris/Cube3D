/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_btn_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:58:53 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/14 12:17:04 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	set_active_btn(t_ddlst *ddlst, t_menu *menu, t_vector_int pos, \
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
			if (menu->plane_ddlst.active.active == true)
			{
				menu->active_plane = offset;
				menu->active_sprite = 1;
			}
			else if (ddlst->active.active)
				menu->active_sprite = 1 + offset + ddlst->scroll_pos;
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

	(void)x;
	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	if (data->menu.active_plane == 0)
		change_scroll_pos(&data->menu.wall_ddlst, y, pos);
	else if (data->menu.active_plane == 1)
		change_scroll_pos(&data->menu.zone_ddlst, y, pos);
	else if (data->menu.active_plane == 2)
		change_scroll_pos(&data->menu.decor_ddlst, y, pos);
	else if (data->menu.active_plane == 3)
		change_scroll_pos(&data->menu.item_ddlst, y, pos);
	else
		change_scroll_pos(&data->menu.enemy_ddlst, y, pos);
}

void	change_state_ddlst(t_data *data, mouse_key_t button, action_t action, \
							t_vector_int pos)
{
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.plane_ddlst.open_rct))
			data->menu.plane_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.rotate_ddlst.open_rct))
			data->menu.rotate_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.wall_ddlst.open_rct))
			data->menu.wall_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.decor_ddlst.open_rct))
			data->menu.decor_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.enemy_ddlst.open_rct))
			data->menu.enemy_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.item_ddlst.open_rct))
			data->menu.item_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.zone_ddlst.open_rct))
			data->menu.zone_ddlst.active.active = false;
	}
	set_btn_state(&data->menu.plane_ddlst.active, button, action, pos);
	if (data->menu.plane_ddlst.active.active == false)
	{
		set_btn_state(&data->menu.wall_ddlst.active, button, action, pos);
		set_btn_state(&data->menu.decor_ddlst.active, button, action, pos);
		set_btn_state(&data->menu.enemy_ddlst.active, button, action, pos);
		set_btn_state(&data->menu.item_ddlst.active, button, action, pos);
		set_btn_state(&data->menu.zone_ddlst.active, button, action, pos);
		if (data->menu.active_plane == 4 || data->menu.active_plane == 0)
			set_btn_state(&data->menu.rotate_ddlst.active, button, action, pos);
	}
}

void	deactivate_other_paint_btns(t_data *data, int activated)
{
	if (activated == 0)
	{
		data->menu.area_btn.active = false;
		data->menu.pen_btn.active = false;
		data->menu.picker_btn.active = false;
	}
	else if (activated == 1)
	{
		data->menu.area_btn.active = false;
		data->menu.bucket_btn.active = false;
		data->menu.picker_btn.active = false;
	}
	else if (activated == 2)
	{
		data->menu.bucket_btn.active = false;
		data->menu.pen_btn.active = false;
		data->menu.picker_btn.active = false;
	}
	else if (activated == 3)
	{
		data->menu.bucket_btn.active = false;
		data->menu.pen_btn.active = false;
		data->menu.area_btn.active = false;
	}
}

void	check_btns_clicked(t_data *data, mouse_key_t button, \
			action_t action, t_vector_int pos)
{
	set_btn_state(&data->menu.enemy_btn, button, action, pos);
	set_btn_state(&data->menu.obj_btn, button, action, pos);
	set_btn_state(&data->menu.floor_btn, button, action, pos);
	if (data->menu.save_btn.active == false)
		set_btn_state(&data->menu.save_btn, button, action, pos);
	if (data->menu.save_btn.active == true)
		save_map(data);
	if (set_btn_state(&data->menu.bucket_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(data, 0);
	else if (set_btn_state(&data->menu.pen_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(data, 1);
	else if (set_btn_state(&data->menu.area_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(data, 2);
	else if (set_btn_state(&data->menu.picker_btn, button, action, pos) == 2)
		deactivate_other_paint_btns(data, 3);
	change_state_ddlst(data, button, action, pos);
	if (data->menu.plane_ddlst.active.active == true)
		set_active_btn(&data->menu.plane_ddlst, &data->menu, pos, button);
	if (data->menu.wall_ddlst.active.active == true && data->menu.active_plane == 0)
		set_active_btn(&data->menu.wall_ddlst, &data->menu, pos, button);
	if (data->menu.zone_ddlst.active.active == true && data->menu.active_plane == 1)
		set_active_btn(&data->menu.zone_ddlst, &data->menu, pos, button);
	else if (data->menu.decor_ddlst.active.active == true && data->menu.active_plane == 2)
		set_active_btn(&data->menu.decor_ddlst, &data->menu, pos, button);
	else if (data->menu.enemy_ddlst.active.active == true && data->menu.active_plane == 4)
		set_active_btn(&data->menu.enemy_ddlst, &data->menu, pos, button);
	else if (data->menu.item_ddlst.active.active == true && data->menu.active_plane == 3)
		set_active_btn(&data->menu.item_ddlst, &data->menu, pos, button);
	else if (data->menu.rotate_ddlst.active.active == true)
		set_active_btn(&data->menu.rotate_ddlst, &data->menu, pos, button);
}
