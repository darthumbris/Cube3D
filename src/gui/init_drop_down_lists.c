/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_drop_down_lists.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:03:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 16:19:37 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_floor_txt_strs(t_ddlst *f, double scale, int y_pos)
{
	uint32_t	i;
	t_rect		rect;

	rect.pos0.x = 3 * scale;
	rect.pos1.x = 88 * scale;
	i = 0;
	while (i < f->elements)
	{
		rect.pos0.y = y_pos + (i * 9) * f->font_scale + 1;
		rect.pos1.y = y_pos + ((i + 1) * 9) * f->font_scale + 1;
		f->btn_lst[i] = new_button(rect, wall_icon_lst[i].name);
		f->btn_lst[i].icon_pos.x = wall_icon_lst[i].x;
		f->btn_lst[i].icon_pos.y = wall_icon_lst[i].y;
		i++;
	}
}

static void	init_obj_txt_strs(t_ddlst *obj, double scale, int y_pos)
{
	uint32_t	i;
	t_rect		rect;

	rect.pos0.x = 3 * scale;
	rect.pos1.x = 88 * scale;
	i = 0;
	while (i < obj->elements)
	{
		rect.pos0.y = y_pos + (i * 9) * obj->font_scale + 1;
		rect.pos1.y = y_pos + ((i + 1) * 9) * obj->font_scale + 1;
		obj->btn_lst[i] = new_button(rect, obj_icon_lst[i].name);
		obj->btn_lst[i].icon_pos.x = obj_icon_lst[i].x;
		obj->btn_lst[i].icon_pos.y = obj_icon_lst[i].y;
		i++;
	}
}

static void	init_buttons_ddlst(t_ddlst *ddlst, double scale, int y_pos)
{
	unsigned int	i;
	t_rect			rect;

	rect.pos0.x = 3 * scale;
	rect.pos1.x = 88 * scale;
	i = 0;
	while (i < ddlst->elements)
	{
		rect.pos0.y = y_pos + (i * 9) * ddlst->font_scale + 1;
		rect.pos1.y = y_pos + ((i + 1) * 9) * ddlst->font_scale + 1;
		ddlst->btn_lst[i] = new_button(rect, ddlst->btn_txt[i]);
		i++;
	}
}

void	init_obj_ddlst(t_ddlst *obj, double scale, double font_scale)
{
	obj->elements = 49;
	obj->height = 9 * font_scale;
	obj->width = 85 * scale;
	obj->pos.x = 3 * scale;
	obj->pos.y = 38 * scale;
	obj->hvr_rct.pos0.x = 3 * scale;
	obj->hvr_rct.pos0.y = 38 * scale;
	obj->hvr_rct.pos1.x = 88 * scale;
	obj->hvr_rct.pos1.y = 46 * scale;
	obj->open_rct = obj->hvr_rct;
	obj->open_rct.pos0.y = 46 * scale;
	obj->open_rct.pos1.y = 176 * scale;
	obj->outline = obj->active.rect;
	obj->outline.pos1.y = obj->active.rect.pos1.y + 9 * font_scale;
	obj->font_scale = font_scale;
	obj->scroll_pos = 0;
	obj->max_visible = 18;
	obj->btn_lst = ft_calloc(obj->elements, sizeof(t_button));
	init_obj_txt_strs(obj, scale, obj->open_rct.pos0.y);
	obj->active = new_button(obj->hvr_rct, obj_icon_lst[0].name);
	obj->active.icon_pos.x = obj->btn_lst[0].icon_pos.x;
	obj->active.icon_pos.y = obj->btn_lst[0].icon_pos.y;
}

void	init_floor_ddlst(t_ddlst *f, double scale, double font_scale)
{
	f->elements = 51;
	f->height = 9 * font_scale;
	f->width = 85 * scale;
	f->pos.x = 3 * scale;
	f->pos.y = 38 * scale;
	f->hvr_rct.pos0.x = 3 * scale;
	f->hvr_rct.pos0.y = 38 * scale;
	f->hvr_rct.pos1.x = 88 * scale;
	f->hvr_rct.pos1.y = 46 * scale;
	f->open_rct = f->hvr_rct;
	f->open_rct.pos0.y = 46 * scale;
	f->open_rct.pos1.y = 176 * scale;
	f->outline = f->active.rect;
	f->outline.pos1.y = f->active.rect.pos1.y + 9 * font_scale;
	f->font_scale = font_scale;
	f->scroll_pos = 0;
	f->max_visible = 18;
	f->btn_lst = ft_calloc(f->elements, sizeof(t_button));
	init_floor_txt_strs(f, scale, f->open_rct.pos0.y);
	f->active = new_button(f->hvr_rct, wall_icon_lst[0].name);
	f->active.icon_pos.x = f->btn_lst[0].icon_pos.x;
	f->active.icon_pos.y = f->btn_lst[0].icon_pos.y;
}

void	init_plane_ddlst(t_ddlst *p, double scale, double font_scale)
{
	p->elements = 3;
	p->height = 7 * scale;
	p->width = 85 * scale;
	p->pos.x = 3 * scale;
	p->pos.y = 13 * scale;
	p->btn_txt = ft_calloc(sizeof(char *), 3);
	p->btn_txt[0] = ft_strdup("plane 0");
	p->btn_txt[1] = ft_strdup("plane 1");
	p->btn_txt[2] = ft_strdup("plane 2");
	p->hvr_rct.pos0.x = 3 * scale;
	p->hvr_rct.pos0.y = 15 * scale;
	p->hvr_rct.pos1.x = 88 * scale;
	p->hvr_rct.pos1.y = 22 * scale;
	p->active = new_button(p->hvr_rct, p->btn_txt[0]);
	p->btn_lst = ft_calloc(sizeof(t_button), 3);
	p->open_rct = p->hvr_rct;
	p->open_rct.pos0.y = 22 * scale;
	p->open_rct.pos1.y = p->hvr_rct.pos1.y + (p->elements * 9 * font_scale) + 1;
	p->outline = p->active.rect;
	p->outline.pos1.y = p->active.rect.pos1.y + 9 * font_scale;
	p->font_scale = font_scale;
	init_buttons_ddlst(p, scale, p->open_rct.pos0.y);
	p->scroll_pos = 0;
	p->max_visible = 3;
}

void	init_dropdown_lists(t_menu *menu, double hud_scale)
{
	init_plane_ddlst(&menu->plane_ddlst, hud_scale, hud_scale * 0.9);
	init_floor_ddlst(&menu->floor_ddlst, hud_scale, hud_scale * 0.8);
	init_obj_ddlst(&menu->obj_ddlst, hud_scale, hud_scale * 0.8);
}
