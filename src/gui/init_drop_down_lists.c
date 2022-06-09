/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_drop_down_lists.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:03:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 12:26:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static const t_icon	wall_icon_lst[51] = \
	{
		{"greybrick1",0,0,"WALL001.png"},
		{"greybrick2",0,1,"WALL002.png"},
		{"greybrick3",0,2,"WALL003.png"},
		{"gbrick eagle",0,3,"WALL004.png"},
		{"gbrick flag",0,4,"WALL005.png"},
		{"gbrick hit",0,5,"WALL006.png"},
		{"gbrick sign",0,6,"WALL030.png"},
		{"steel door1",0,7,"WALL011.png"},
		{"steel door2",0,8,"WALL012.png"},
		{"bluebrick1",1,0,"WALL007.png"},
		{"bluebrick2",1,1,"WALL023.png"},
		{"bbrick sign",1,2,"WALL032.png"},
		{"prison cell",1,3,"WALL020.png"},
		{"blue line",1,4,"WALL051.png"},
		{"blue cross",1,5,"WALL052.png"},
		{"blue skull",1,6,"WALL053.png"},
		{"mossybrick1",1,7,"WALL028.png"},
		{"mossybrick2",1,8,"WALL029.png"},
		{"wood",2,0,"WALL028.png"},
		{"wood eagle",2,1,"WALL019.png"},
		{"wood cross",2,2,"WALL041.png"},
		{"wood hit",2,3,"WALL049.png"},
		{"wood arch",2,4,"WALL050.png"},
		{"purple1",2,5,"WALL059.png"},
		{"purple2",2,6,"WALL060.png"},
		{"messybrick1",2,7,"WALL021.png"},
		{"messybrick2",2,8,"WALL022.png"},
		{"steel wall",3,0,"WALL024.png"},
		{"steel sign",3,1,"WALL025.png"},
		{"tilebrick1",3,2,"WALL040.png"},
		{"tilebrick2",3,3,"WALL042.png"},
		{"tile flag",3,4,"WALL041.png"},
		{"stone1",3,5,"WALL043.png"},
		{"stone2",3,6,"WALL044.png"},
		{"stone3",3,7,"WALL054.png"},
		{"railing",3,8,"WALL017.png"},
		{"whitebrick1",4,0,"WALL034.png"},
		{"wbrick hole",4,1,"WALL035.png"},
		{"wbrick crack",4,2,"WALL036.png"},
		{"wbrick hit,4",4,3,"WALL037.png"},
		{"wbrick map",4,4,"WALL038.png"},
		{"mosiac",4,5,"WALL047.png"},
		{"door1",4,6,"WALL014.png"},
		{"door2",4,7,"WALL015.png"},
		{"door3",4,8,"WALL016.png"},
		{"redbrick",5,0,"WALL008.png"},
		{"rbrick eagle",5,1,"WALL009.png"},
		{"rbrick cross",5,2,"WALL010.png"},
		{"mixedbrick",5,3,"WALL039.png"},
		{"switch",5,4,"WALL061.png"},
		{"door4",5,5,"WALL018.png"}
	};

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
}
