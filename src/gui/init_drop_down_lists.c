/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_drop_down_lists.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:03:06 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 17:11:54 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_floor_txt_strs(t_ddlst *f)
{
	f->btn_txt = ft_calloc(sizeof(char *), f->elements);
	f->btn_txt[0] = ft_strdup("greybrick1");
	f->btn_txt[1] = ft_strdup("greybrick2");
	f->btn_txt[2] = ft_strdup("greybrick3");
	f->btn_txt[3] = ft_strdup("bluebrick1");
	f->btn_txt[4] = ft_strdup("bluebrick2");
	f->btn_txt[5] = ft_strdup("redbrick");
	f->btn_txt[6] = ft_strdup("mossybrick1");
	f->btn_txt[7] = ft_strdup("mossybrick2");
	f->btn_txt[8] = ft_strdup("mixedbrick");
	f->btn_txt[9] = ft_strdup("whitebrick1");
	f->btn_txt[10] = ft_strdup("whitebrick2");
	f->btn_txt[11] = ft_strdup("crackedbrick");
	f->btn_txt[12] = ft_strdup("messybrick1");
	f->btn_txt[13] = ft_strdup("messybrick2");
	f->btn_txt[14] = ft_strdup("tilebrick1");
	f->btn_txt[15] = ft_strdup("tilebrick2");
	f->btn_txt[16] = ft_strdup("bluecell1");
	f->btn_txt[17] = ft_strdup("bluecell2");
	f->btn_txt[18] = ft_strdup("bluecell3");
	f->btn_txt[19] = ft_strdup("steel");
	f->btn_txt[20] = ft_strdup("steelwsign");
	f->btn_txt[21] = ft_strdup("wood");
	f->btn_txt[22] = ft_strdup("wood eagle");
	f->btn_txt[23] = ft_strdup("wood hitler");
	f->btn_txt[24] = ft_strdup("wood cross");
	f->btn_txt[25] = ft_strdup("wood arch");
	f->btn_txt[26] = ft_strdup("gb eagle");
	f->btn_txt[27] = ft_strdup("gb flag");
	f->btn_txt[28] = ft_strdup("gb hitler");
	f->btn_txt[29] = ft_strdup("gb sign");
	f->btn_txt[30] = ft_strdup("rb cross");
	f->btn_txt[31] = ft_strdup("rb eagle");
	f->btn_txt[32] = ft_strdup("purple1");
	f->btn_txt[33] = ft_strdup("purple2");
	f->btn_txt[34] = ft_strdup("switch1");
	f->btn_txt[35] = ft_strdup("switch2");
	f->btn_txt[36] = ft_strdup("railing1");
	f->btn_txt[37] = ft_strdup("railing2");
	f->btn_txt[38] = ft_strdup("eagle");
	f->btn_txt[39] = ft_strdup("mosaic");
	f->btn_txt[40] = ft_strdup("stone1");
	f->btn_txt[41] = ft_strdup("stone2");
	f->btn_txt[42] = ft_strdup("stone3");
	f->btn_txt[43] = ft_strdup("stone4");
	f->btn_txt[44] = ft_strdup("blue skull");
	f->btn_txt[45] = ft_strdup("blue cross");
	f->btn_txt[46] = ft_strdup("blue line");
	f->btn_txt[47] = ft_strdup("blue sign");
	f->btn_txt[48] = ft_strdup("wb map");
	f->btn_txt[49] = ft_strdup("tb flag");
	f->btn_txt[50] = ft_strdup("laugh hit");
	f->btn_txt[51] = ft_strdup("door1");
	f->btn_txt[52] = ft_strdup("door2");
	f->btn_txt[53] = ft_strdup("door3");
	f->btn_txt[54] = ft_strdup("door4");
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
	f->elements = 55;
	f->height = 9 * font_scale;
	f->width = 85 * scale;
	f->pos.x = 3 * scale;
	f->pos.y = 38 * scale;
	init_floor_txt_strs(f);
	f->hvr_rct.pos0.x = 3 * scale;
	f->hvr_rct.pos0.y = 38 * scale;
	f->hvr_rct.pos1.x = 88 * scale;
	f->hvr_rct.pos1.y = 46 * scale;
	f->active = new_button(f->hvr_rct, f->btn_txt[0]);
	f->btn_lst = ft_calloc(sizeof(t_button), f->elements);
	f->open_rct = f->hvr_rct;
	f->open_rct.pos0.y = 46 * scale;
	f->open_rct.pos1.y = 176 * scale;
	f->outline = f->active.rect;
	f->outline.pos1.y = f->active.rect.pos1.y + 9 * font_scale;
	f->font_scale = font_scale;
	init_buttons_ddlst(f, scale, f->open_rct.pos0.y);
	f->scroll_pos = 0;
	f->max_visible = 18;
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
