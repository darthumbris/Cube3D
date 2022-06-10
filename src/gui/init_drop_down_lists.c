/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_drop_down_lists.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:03:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/10 13:36:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_btn_lst(t_ddlst *drop, double scale, int y_pos, \
						const t_icon icon_lst[])
{
	uint32_t	i;
	t_rect		rect;

	rect.pos0.x = 3 * scale;
	rect.pos1.x = 88 * scale;
	i = 0;
	while (i < drop->elements)
	{
		rect.pos0.y = y_pos + (i * 9) * drop->font_scale + 1;
		rect.pos1.y = y_pos + ((i + 1) * 9) * drop->font_scale + 1;
		drop->btn_lst[i] = new_button(rect, icon_lst[i].name);
		drop->btn_lst[i].icon_pos.x = icon_lst[i].x;
		drop->btn_lst[i].icon_pos.y = icon_lst[i].y;
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

static void	init_sprite_ddlst(t_ddlst *drop, double scale, \
								const t_icon icon_lst[], int size)
{
	const double	font_scale = scale * 0.8;

	drop->elements = size;
	drop->height = 9 * font_scale;
	drop->width = 85 * scale;
	drop->pos.x = 3 * scale;
	drop->pos.y = 38 * scale;
	drop->hvr_rct.pos0.x = 3 * scale;
	drop->hvr_rct.pos0.y = 38 * scale;
	drop->hvr_rct.pos1.x = 88 * scale;
	drop->hvr_rct.pos1.y = 46 * scale;
	drop->open_rct = drop->hvr_rct;
	drop->open_rct.pos0.y = 46 * scale;
	drop->open_rct.pos1.y = 176 * scale;
	drop->outline = drop->active.rect;
	drop->outline.pos1.y = drop->active.rect.pos1.y + 9 * font_scale;
	drop->font_scale = font_scale;
	drop->scroll_pos = 0;
	drop->max_visible = 18;
	drop->btn_lst = ft_calloc(drop->elements, sizeof(t_button));
	init_btn_lst(drop, scale, drop->open_rct.pos0.y, icon_lst);
	drop->active = new_button(drop->hvr_rct, icon_lst[0].name);
	drop->active.icon_pos.x = drop->btn_lst[0].icon_pos.x;
	drop->active.icon_pos.y = drop->btn_lst[0].icon_pos.y;
}

void	init_plane_ddlst(t_ddlst *p, double scale, double font_scale)
{
	p->elements = 5;
	p->height = 7 * scale;
	p->width = 85 * scale;
	p->pos.x = 3 * scale;
	p->pos.y = 13 * scale;
	p->btn_txt = ft_calloc(sizeof(char *), p->elements);
	p->btn_txt[0] = ft_strdup("plane 0 walls");
	p->btn_txt[1] = ft_strdup("plane 0 floor");
	p->btn_txt[2] = ft_strdup("plane 1 decor");
	p->btn_txt[3] = ft_strdup("plane 1 items");
	p->btn_txt[4] = ft_strdup("plane 2 enemies");
	p->hvr_rct.pos0.x = 3 * scale;
	p->hvr_rct.pos0.y = 15 * scale;
	p->hvr_rct.pos1.x = 88 * scale;
	p->hvr_rct.pos1.y = 22 * scale;
	p->active = new_button(p->hvr_rct, p->btn_txt[0]);
	p->btn_lst = ft_calloc(sizeof(t_button), p->elements);
	p->open_rct = p->hvr_rct;
	p->open_rct.pos0.y = 22 * scale;
	p->open_rct.pos1.y = p->hvr_rct.pos1.y + (p->elements * 9 * font_scale) + 1;
	p->outline = p->active.rect;
	p->outline.pos1.y = p->active.rect.pos1.y + 9 * font_scale;
	p->font_scale = font_scale;
	init_buttons_ddlst(p, scale, p->open_rct.pos0.y);
	p->scroll_pos = 0;
	p->max_visible = 5;
}

void	init_dropdown_lists(t_menu *menu, double hud_scale)
{
	init_plane_ddlst(&menu->plane_ddlst, hud_scale, hud_scale * 0.75);
	init_sprite_ddlst(&menu->wall_ddlst, hud_scale, wall_icon_lst, 51);
	init_sprite_ddlst(&menu->decor_ddlst, hud_scale, obj_icon_lst, 49);
	init_sprite_ddlst(&menu->enemy_ddlst, hud_scale, enemy_icon_lst, 23);
}
