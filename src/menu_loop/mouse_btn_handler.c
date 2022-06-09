/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_btn_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:58:53 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 11:47:39 by shoogenb      ########   odam.nl         */
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
				menu->floor_ddlst.active = menu->floor_ddlst.btn_lst[0];
				menu->floor_ddlst.active.rect = menu->floor_ddlst.hvr_rct;
			}
			else if (menu->floor_ddlst.active.active == true)
				menu->active_sprite = 1 + offset + ddlst->scroll_pos;
			ddlst->active.active = false;
			ddlst->active = ddlst->btn_lst[offset + ddlst->scroll_pos];
			ddlst->active.rect = ddlst->hvr_rct;
		}
	}
}

//TODO make the how far it can scroll not hardcoded
void	scroll_function_btn(double x, double y, void *param)
{
	t_vector_int	pos;
	t_data			*data;
	int				max_scroll;

	(void)x;
	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	if (is_mouse_in_rect(pos.x, pos.y, data->menu.floor_ddlst.open_rct) && \
		data->menu.floor_ddlst.active.active == true)
	{
		if (y < 0)
			data->menu.floor_ddlst.scroll_pos++;
		else
			data->menu.floor_ddlst.scroll_pos--;
	}
	if (data->menu.floor_ddlst.scroll_pos < 0)
		data->menu.floor_ddlst.scroll_pos = 0;
	max_scroll = (int)data->menu.floor_ddlst.elements - \
					data->menu.floor_ddlst.max_visible;
	if (data->menu.floor_ddlst.scroll_pos > max_scroll)
		data->menu.floor_ddlst.scroll_pos = max_scroll;
}

void	change_state_ddlst(t_data *data, mouse_key_t button, action_t action, \
							t_vector_int pos)
{
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.plane_ddlst.open_rct))
			data->menu.plane_ddlst.active.active = false;
		if (!is_mouse_in_rect(pos.x, pos.y, data->menu.floor_ddlst.open_rct))
			data->menu.floor_ddlst.active.active = false;
	}
	if (data->menu.floor_ddlst.active.active == false)
		set_btn_state(&data->menu.plane_ddlst.active, button, action, pos);
	if (data->menu.plane_ddlst.active.active == false)
		set_btn_state(&data->menu.floor_ddlst.active, button, action, pos);
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
	else if (data->menu.floor_ddlst.active.active == true)
		set_active_btn(&data->menu.floor_ddlst, &data->menu, pos, button);
}
