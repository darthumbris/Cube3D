/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:44:17 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_mouse_in_rect(int x, int y, t_rect r)
{
	return (x >= r.pos0.x && x <= r.pos1.x && y >= r.pos0.y && y <= r.pos1.y);
}

bool	is_hover(t_button *btn, int x, int y)
{
	if (is_mouse_in_rect(x, y, btn->rect))
	{
		btn->state = HOVER;
		return (true);
	}
	else if (btn->state == HOVER)
	{
		btn->state = IDLE;
		return (true);
	}
	return (false);
}

static bool	set_btn_state(t_button *btn, mouse_key_t button, action_t action, \
		t_vector_int pos)
{
	bool	update;

	update = false;
	if (is_mouse_in_rect(pos.x, pos.y, btn->rect))
	{
		btn->state = HOVER;
		if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		{
			btn->state = CLICKED;
			btn->active = !btn->active;
			update = true;
		}
	}
	else if (btn->state != IDLE)
	{
		btn->state = IDLE;
		update = true;
	}
	return (update);
}

int	get_button_mouse_on(int x, int y, t_ddlst drop)
{
	unsigned int	i;

	i = 0;
	while (i < drop.elements)
	{
		if (is_mouse_in_rect(x, y, drop.btn_lst[i].rect))
			return (i);
		i++;
	}
	return (-1);
}

void	set_active_btn(t_ddlst *ddlst, t_data *data, t_vector_int pos, mouse_key_t button)
{
	int				offset;

	if (is_mouse_in_rect(pos.x, pos.y, ddlst->open_rct))
	{
		offset = get_button_mouse_on(pos.x, pos.y, *ddlst);
		if (offset == -1)
			return ;
		if (button == MLX_MOUSE_BUTTON_LEFT)
		{
			if (data->menu.plane_ddlst.active.active == true)
			{
				data->menu.active_plane = offset;
				data->menu.active_sprite = 1;
				data->menu.floor_ddlst.active = data->menu.floor_ddlst.btn_lst[0];
				data->menu.floor_ddlst.active.rect = data->menu.floor_ddlst.hvr_rct;
			}
			else if (data->menu.floor_ddlst.active.active == true)
				data->menu.active_sprite = 1 + offset;
			ddlst->active.active = false;
			ddlst->active = ddlst->btn_lst[offset];
			ddlst->active.rect = ddlst->hvr_rct;
		}
	}
}

void	change_state_ddlst(t_data *data, mouse_key_t button, action_t action, t_vector_int pos)
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

void	menu_mouse_handler(mouse_key_t button, action_t action, \
		modifier_key_t mods, void *param)
{
	t_vector_int	pos;
	t_vector_int	map_pos;
	t_data			*data;

	(void)mods;
	data = (t_data *)param;
	if (data->menu.menu_level != 2)
		return ;
	data->menu.update = true;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	map_pos.x = ((pos.x - data->menu.map_area.pos0.x) / data->menu.grid_size) \
				+ data->menu.map_offset.x;
	map_pos.y = ((pos.y - data->menu.map_area.pos0.y) / data->menu.grid_size) \
				+ data->menu.map_offset.y;
	if (map_pos.x > 0 && map_pos.y > 0 && \
		map_pos.x < MAX_MAP_SIZE && map_pos.y < MAX_MAP_SIZE && \
		is_mouse_in_rect(pos.x, pos.y, data->menu.map_area))
	{
		if (button == MLX_MOUSE_BUTTON_LEFT)
			data->menu.map[map_pos.y][map_pos.x][data->menu.active_plane] = data->menu.active_sprite;
		else if (button == MLX_MOUSE_BUTTON_RIGHT)
			data->menu.map[map_pos.y][map_pos.x][data->menu.active_plane] = 0;
	}
	if (set_btn_state(&data->menu.enemy_btn, button, action, pos) || \
		set_btn_state(&data->menu.obj_btn, button, action, pos) || \
		set_btn_state(&data->menu.floor_btn, button, action, pos))
		NULL ;
	change_state_ddlst(data, button, action, pos);
	if (data->menu.plane_ddlst.active.active == true)
		set_active_btn(&data->menu.plane_ddlst, data, pos, button);
	else if (data->menu.floor_ddlst.active.active == true)
		set_active_btn(&data->menu.floor_ddlst, data, pos, button);
}
