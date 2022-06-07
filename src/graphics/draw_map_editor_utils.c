/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_editor_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 09:58:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:19:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

unsigned int	get_color_tile(int tile)
{
	if (tile == 1)
		return (0x8f8f8fff);
	else if (tile == 2)
		return (0x0000b3ff);
	else if (tile == 3)
		return (0x774e2bff);
	return (0x8f8f8fff);
}

static void	draw_button(t_data *data, t_rect rec, uint32_t color)
{
	uint8_t			*menu;
	int				y;
	int				x;

	rec.pos0.x += 2;
	rec.pos0.y += 2;
	rec.pos1.x -= 1;
	rec.pos1.y -= 1;
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

void	draw_rect(t_data *data, t_rect rec, uint32_t color)
{
	uint8_t			*map;
	int				y;
	int				x;

	y = rec.pos0.y;
	map = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)data->mlx.fg->width)
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = color;
		y++;
	}
}

void	draw_rect_outline(t_data *data, t_rect rec, uint32_t c, \
			int thickness)
{
	uint8_t	*menu;
	int		y;
	int		x;
	int		pixels;

	y = rec.pos0.y;
	menu = data->mlx.fg->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		pixels = 0;
		while (pixels < thickness)
		{
			*(uint32_t *)(menu + ((y * data->mlx.fg->width + rec.pos1.x + \
				pixels) * 4)) = c;
			*(uint32_t *)(menu + ((y * data->mlx.fg->width + rec.pos0.x - \
				pixels) * 4)) = c;
			pixels++;
		}
		y++;
	}
	x = rec.pos0.x;
	if (x < 0)
		x = 0;
	while (x < rec.pos1.x && x < (int)data->mlx.fg->width)
	{
		pixels = 0;
		while (pixels < thickness)
		{
			*(uint32_t *)(menu + (((rec.pos0.y + pixels) * \
				data->mlx.fg->width + x) * 4)) = c;
			*(uint32_t *)(menu + (((rec.pos1.y + pixels) * \
				data->mlx.fg->width + x) * 4)) = c;
			pixels++;
		}
		x++;
	}
}

void	draw_buttons(t_data *data)
{
	if (data->menu.enemy_btn.state == HOVER)
		draw_button(data, data->menu.enemy_btn.rect, HOVER_COLOR);
	else if (data->menu.enemy_btn.state == IDLE)
		draw_button(data, data->menu.enemy_btn.rect, 0x000000ff);
	if (data->menu.floor_btn.state == HOVER)
		draw_button(data, data->menu.floor_btn.rect, HOVER_COLOR);
	else if (data->menu.floor_btn.state == IDLE)
		draw_button(data, data->menu.floor_btn.rect, 0x000000ff);
	if (data->menu.obj_btn.state == HOVER)
		draw_button(data, data->menu.obj_btn.rect, HOVER_COLOR);
	else if (data->menu.obj_btn.state == IDLE)
		draw_button(data, data->menu.obj_btn.rect, 0x000000ff);
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
