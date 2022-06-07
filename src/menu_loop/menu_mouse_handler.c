/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 09:54:02 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_mouse_in_rect(int x, int y, t_rect r)
{
	return (x >= r.pos0.x && x <= r.pos1.x && y >= r.pos0.y && y <= r.pos1.y);
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
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	map_pos.x = ((pos.x - data->menu.map_area.pos0.x) / data->menu.grid_size) + data->menu.map_offset.x;
	map_pos.y = ((pos.y - data->menu.map_area.pos0.y) / data->menu.grid_size) + data->menu.map_offset.y;
	if (map_pos.x > 0 && map_pos.y > 0 && \
		map_pos.x < MAX_MAP_SIZE && map_pos.y < MAX_MAP_SIZE && \
		is_mouse_in_rect(pos.x, pos.y, data->menu.map_area))
	{
		data->menu.map[map_pos.y][map_pos.x][0] = 1;
		data->menu.update = true;
	}
	if (set_btn_state(&data->menu.enemy_btn, button, action, pos) || \
		set_btn_state(&data->menu.obj_btn, button, action, pos) || \
		set_btn_state(&data->menu.floor_btn, button, action, pos))
		data->menu.update = true;
}
