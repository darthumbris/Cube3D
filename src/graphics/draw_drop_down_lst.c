/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_drop_down_lst.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/07 14:17:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/07 17:36:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_char(t_data *data, t_vector_int pos, int c, int offset, int width)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	pixel.x = 0;
	font = data->mlx.font->pixels;
	while (++pixel.x < width)
	{
		tex.x = pixel.x * data->hud.inv_scale + (c * 8 + offset);
		menu = data->mlx.fg->pixels + (((pixel.x + pos.x) * 4) + \
			(pos.y) * data->floor.width4);
		pixel.y = 8 * data->hud.scale - 1;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			color = (*(int *)(font + ((tex.y * \
				data->mlx.font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu -= data->floor.width4;
		}
	}
}

static void	draw_number(t_data *data, t_vector_int pos, int nbr)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	pixel.x = 0;
	font = data->mlx.font->pixels;
	while (++pixel.x < 10 * data->hud.scale)
	{
		tex.x = pixel.x * data->hud.inv_scale + (nbr * 9 + 210);
		menu = data->mlx.fg->pixels + (((pixel.x + pos.x) * 4) + \
			(pos.y * data->floor.width4));
		pixel.y = 8 * data->hud.scale - 1;
		while (--pixel.y > 0)
		{
			tex.y = pixel.y * data->hud.inv_scale;
			color = (*(int *)(font + ((tex.y * \
				data->mlx.font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu -= data->floor.width4;
		}
	}
}

static void	draw_alpha(t_data *data, t_vector_int pos, char c)
{
	if (c >= 'a' && c <= 'h')
		draw_char(data, pos, c - 'a', 0, 8 * data->hud.scale);
	else if (c == 'i')
		draw_char(data, pos, c - 'a', 0, 4 * data->hud.scale);
	else if (c == 'j')
		draw_char(data, pos, c - 'a', -4, 7 * data->hud.scale);
	else if (c == 'k' || (c > 'm' && c < 'w'))
		draw_char(data, pos, c - 'a', -5, 8 * data->hud.scale);
	else if (c == 'l')
		draw_char(data, pos, c - 'a', -5, 4 * data->hud.scale);
	else if (c == 'm')
		draw_char(data, pos, c - 'a', -9, 12 * data->hud.scale);
	else if (c == 'w')
		draw_char(data, pos, c - 'a', -5, 12 * data->hud.scale);
	else if (c == 'x')
		draw_char(data, pos, c - 'a', -9, 9 * data->hud.scale);
	else
		draw_char(data, pos, c - 'a', 0, 8 * data->hud.scale);
}

static void	draw_str(t_data *data, char *str, t_vector_int pos)
{
	int				i;

	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
		{
			draw_alpha(data, pos, str[i]);
			if (str[i] == 'i' || str[i] == 'l')
				pos.x += 4 * data->hud.scale;
			else if (str[i] == 'j')
				pos.x += 7 * data->hud.scale;
			else if (str[i] == 'm' || str[i] == 'w')
				pos.x += 12 * data->hud.scale;
			else if (str[i] == 'x')
				pos.x += 9 * data->hud.scale;
			else
				pos.x += 8 * data->hud.scale;
		}
		else if (ft_isdigit(str[i]))
		{
			draw_number(data, pos, str[i] - '0');
			pos.x += 10 * data->hud.scale;
		}
		else
			pos.x += 4 * data->hud.scale;
	}
}

void	draw_drop_down_lst(t_data *data, t_vector_int pos, t_ddlst ddlst)
{
	int				x;
	int				y;
	unsigned int	offset;
	unsigned int	i;

	draw_str(data, ddlst.active.txt, pos);
	if (ddlst.active.active == true)
	{
		mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
		draw_rect(data, ddlst.open_rct, HOVER_COLOR);
		i = 0;
		while (i < ddlst.elements)
		{
			pos.y += 9 * data->hud.scale;
			draw_str(data, ddlst.btn_txt[i], pos);
			i++;
		}
		if (is_mouse_in_rect(x, y, ddlst.open_rct))
		{
			offset = get_button_mouse_on(x, y, ddlst);
			if (offset >= 0 && offset < ddlst.elements)
			{
				draw_rect_outline(data, ddlst.btn_lst[offset].rect, \
					MAP_BORDER_COLOUR, 1 * data->hud.scale);
			}
		}
	}
}

void	draw_drop_down_lsts(t_data *data)
{
	t_vector_int	pos;

	pos.y = data->menu.plane_ddlst.pos.y + 6 * data->hud.scale;
	pos.x = data->menu.plane_ddlst.pos.x;
	draw_drop_down_lst(data, pos, data->menu.plane_ddlst);
	pos.y = data->menu.floor_ddlst.pos.y + 6 * data->hud.scale;
	if (data->menu.plane_ddlst.active.active == false)
		draw_drop_down_lst(data, pos, data->menu.floor_ddlst);
}
