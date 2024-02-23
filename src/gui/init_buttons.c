/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_buttons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:02:25 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:31:09 by shoogenb      ########   odam.nl         */
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

static void	init_top_btns(t_vis_btns *vis, t_rect rect, double scale)
{
	vis->btns[OBJ] = new_button(rect, NULL);
	rect.pos0.x += 91 * scale;
	rect.pos1.x += 91 * scale;
	vis->btns[ENMY] = new_button(rect, NULL);
	rect.pos0.x += 74 * scale;
	rect.pos1.x += 74 * scale;
	vis->btns[FLOOR] = new_button(rect, NULL);
	rect.pos0.x = 2 * scale;
	rect.pos1.x = 16 * scale;
	rect.pos0.y = 224 * scale;
	rect.pos1.y = 238 * scale;
	vis->btns[FLOOR].active = true;
}

static void	init_paint_btns(t_map_edit *editor, t_rect rect, double scale)
{
	t_pnt_btns	*pnt;
	t_file		*file;

	pnt = &editor->pnt_btns;
	file = &editor->file;
	pnt->btns[BUCKET] = new_button(rect, NULL);
	rect.pos0.x += 16 * scale;
	rect.pos1.x += 16 * scale;
	pnt->btns[PEN] = new_button(rect, NULL);
	rect.pos0.x += 16 * scale;
	rect.pos1.x += 16 * scale;
	pnt->btns[AREA] = new_button(rect, NULL);
	rect.pos0.x += 16 * scale;
	rect.pos1.x += 16 * scale;
	pnt->btns[PICKER] = new_button(rect, NULL);
	rect.pos0.x += 20 * scale;
	rect.pos1.x += 20 * scale;
	file->load_btn = new_button(rect, NULL);
	rect.pos0.x += 16 * scale;
	rect.pos1.x += 16 * scale;
	file->save_btn = new_button(rect, NULL);
	pnt->btns[PEN].active = true;
	editor->pen = PEN;
}

void	init_buttons(t_data *data)
{
	t_rect	rect;

	rect.pos0.x = 136 * data->hud.scale;
	rect.pos1.x = 148 * data->hud.scale;
	rect.pos0.y = 1 * data->hud.scale;
	rect.pos1.y = 13 * data->hud.scale;
	init_top_btns(&data->menu.editor.vis_btns, rect, data->hud.scale);
	rect.pos0.x = 2 * data->hud.scale;
	rect.pos1.x = 16 * data->hud.scale;
	rect.pos0.y = 224 * data->hud.scale;
	rect.pos1.y = 238 * data->hud.scale;
	init_paint_btns(&data->menu.editor, rect, data->hud.scale);
}