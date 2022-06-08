/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_buttons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:02:25 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:05:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_button	new_button(t_rect rect, char *txt)
{
	t_button	btn;

	btn.rect = rect;
	btn.active = false;
	btn.state = IDLE;
	btn.txt = txt;
	return (btn);
}

static void	init_top_btns(t_data *data, t_rect rect)
{
	data->menu.obj_btn = new_button(rect, NULL);
	rect.pos0.x += 91 * data->hud.scale;
	rect.pos1.x += 91 * data->hud.scale;
	data->menu.enemy_btn = new_button(rect, NULL);
	rect.pos0.x += 74 * data->hud.scale;
	rect.pos1.x += 74 * data->hud.scale;
	data->menu.floor_btn = new_button(rect, NULL);
	rect.pos0.x = 2 * data->hud.scale;
	rect.pos1.x = 16 * data->hud.scale;
	rect.pos0.y = 224 * data->hud.scale;
	rect.pos1.y = 238 * data->hud.scale;
}

static void	init_paint_btns(t_data *data, t_rect rect)
{
	data->menu.bucket_btn = new_button(rect, NULL);
	rect.pos0.x += 16 * data->hud.scale;
	rect.pos1.x += 16 * data->hud.scale;
	data->menu.pen_btn = new_button(rect, NULL);
	rect.pos0.x += 16 * data->hud.scale;
	rect.pos1.x += 16 * data->hud.scale;
	data->menu.area_btn = new_button(rect, NULL);
	rect.pos0.x += 16 * data->hud.scale;
	rect.pos1.x += 16 * data->hud.scale;
	data->menu.picker_btn = new_button(rect, NULL);
	rect.pos0.x += 20 * data->hud.scale;
	rect.pos1.x += 20 * data->hud.scale;
	data->menu.load_btn = new_button(rect, NULL);
	rect.pos0.x += 16 * data->hud.scale;
	rect.pos1.x += 16 * data->hud.scale;
	data->menu.save_btn = new_button(rect, NULL);
	data->menu.pen_btn.active = true;
	data->menu.pen = PEN;
}

void	init_buttons(t_data *data)
{
	t_rect	rect;

	rect.pos0.x = 136 * data->hud.scale;
	rect.pos1.x = 148 * data->hud.scale;
	rect.pos0.y = 1 * data->hud.scale;
	rect.pos1.y = 13 * data->hud.scale;
	init_top_btns(data, rect);
	rect.pos0.x = 2 * data->hud.scale;
	rect.pos1.x = 16 * data->hud.scale;
	rect.pos0.y = 224 * data->hud.scale;
	rect.pos1.y = 238 * data->hud.scale;
	init_paint_btns(data, rect);
}
