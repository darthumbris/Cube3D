/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_buttons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:55:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 08:33:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_button(t_data *data, t_rect rec, uint32_t color)
{
	uint8_t			*menu;
	int				y;
	int				x;

	y = rec.pos0.y;
	menu = data->mlx.menu_editor->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x;
		if (x < 0)
			x = 0;
		while (x < rec.pos1.x && x < (int)data->mlx.fg->width)
		{
			*(uint32_t *)(menu + ((y * data->mlx.fg->width + x) * 4)) = color;
			x++;
		}
		y++;
	}
}

//TODO make sure that this is removed for other menu screens
static void	draw_transparency_btns(t_data *data, t_rect rec, uint32_t c)
{
	uint8_t			*menu;
	uint8_t			*fg;
	int				y;
	int				x;
	uint32_t		fg_c;

	y = rec.pos0.y;
	menu = data->mlx.bg->pixels;
	fg = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x;
		if (x < 0)
			x = 0;
		while (x < rec.pos1.x && x < (int)data->mlx.fg->width)
		{
			fg_c = *(uint32_t *)(fg + (y * data->mlx.fg->width + x) * 4);
			if (fg_c == 0x0000000)
				*(uint32_t *)(menu + ((y * data->mlx.fg->width + x) * 4)) = c;
			x++;
		}
		y++;
	}
}

static void	draw_click_idle(t_data *data, t_button btn)
{
	if (btn.state == HOVER)
		draw_button(data, btn.rect, HOVER_COLOR);
	else if (btn.state == IDLE)
		draw_button(data, btn.rect, 0x00000000);
	if ((btn.state == IDLE || btn.state == HOVER) && btn.active == false)
		draw_transparency_btns(data, btn.rect, 0x4c0000ff);
	else
		draw_transparency_btns(data, btn.rect, 0x850000ff);
}

static void	draw_hover_drop_down(t_data *data)
{
	if (data->menu.plane_ddlst.active.state == HOVER)
		draw_button(data, data->menu.plane_ddlst.hvr_rct, HOVER_COLOR);
	else if (data->menu.plane_ddlst.active.state == IDLE)
	{
		draw_button(data, data->menu.plane_ddlst.hvr_rct, 0x000000ff);
		if (data->menu.plane_ddlst.active.active == false)
		{
			if (data->menu.floor_ddlst.active.state == HOVER)
				draw_button(data, data->menu.floor_ddlst.hvr_rct, HOVER_COLOR);
			else if (data->menu.floor_ddlst.active.state == IDLE)
				draw_button(data, data->menu.floor_ddlst.hvr_rct, 0x000000ff);
		}
	}
}

void	draw_buttons(t_data *data)
{
	draw_click_idle(data, data->menu.enemy_btn);
	draw_click_idle(data, data->menu.floor_btn);
	draw_click_idle(data, data->menu.obj_btn);
	draw_click_idle(data, data->menu.bucket_btn);
	draw_click_idle(data, data->menu.pen_btn);
	draw_click_idle(data, data->menu.area_btn);
	draw_click_idle(data, data->menu.picker_btn);
	draw_click_idle(data, data->menu.load_btn);
	draw_click_idle(data, data->menu.save_btn);
	draw_hover_drop_down(data);
}
