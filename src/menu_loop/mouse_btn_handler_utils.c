/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_btn_handler_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 16:00:38 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 09:05:46 by shoogenb      ########   odam.nl         */
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

int	set_btn_state(t_button *btn, mouse_key_t button, action_t action, \
		t_vector_int pos)
{
	int	update;

	update = 0;
	if (is_mouse_in_rect(pos.x, pos.y, btn->rect))
	{
		btn->state = HOVER;
		update = 1;
		if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		{
			btn->state = CLICKED;
			btn->active = !btn->active;
			update = 2;
		}
	}
	else if (btn->state != IDLE)
	{
		btn->state = IDLE;
		update = 1;
	}
	return (update);
}

int	get_button_mouse_on(int x, int y, t_ddlst drop)
{
	int	diff;
	int	pos;

	if (is_mouse_in_rect(x, y, drop.open_rct))
	{
		diff = drop.open_rct.pos1.y - y;
		pos = drop.max_visible - diff / (9 * drop.font_scale);
		return (pos);
	}
	return (-1);
}
