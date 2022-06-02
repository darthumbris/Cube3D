/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_mouse_handler.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/31 08:58:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/31 10:02:21 by shoogenb      ########   odam.nl         */
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
	t_data			*data;

	(void)mods;
	data = (t_data *)param;
	if (data->menu.menu_level != 2)
		return ;
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	printf("mouse: %d,%d\n", pos.x, pos.y);
	if (set_btn_state(&data->menu.enemy_btn, button, action, pos) || \
		set_btn_state(&data->menu.obj_btn, button, action, pos) || \
		set_btn_state(&data->menu.floor_btn, button, action, pos))
		data->menu.update = true;
}
