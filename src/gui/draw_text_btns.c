/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_text_btns.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:56:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 11:59:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_char(t_data *data, t_vector_int pos, int tex_pos_width[2], \
						double font_scale)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	font = data->mlx.font->pixels;
	pixel.y = -1;
	menu = data->mlx.fg->pixels + (((pos.x) * 4) + \
			(pos.y) * data->floor.width4);
	while (++pixel.y < 8 * font_scale)
	{
		pixel.x = -1;
		while (++pixel.x < tex_pos_width[1])
		{
			tex.x = pixel.x * (1 / font_scale) + tex_pos_width[0];
			tex.y = pixel.y * (1 / font_scale);
			color = (*(int *)(font + ((tex.y * \
				data->mlx.font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu += 4;
		}
		if (pixel.x < (int)data->mlx.fg->width)
			menu += (data->mlx.fg->width * 4 - (tex_pos_width[1]) * 4);
	}
}

static void	draw_number(t_data *data, t_vector_int pos, int nbr, \
						double font_scale)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	pixel.y = -1;
	font = data->mlx.font->pixels;
	menu = data->mlx.fg->pixels + (pos.x * 4 + \
			(pos.y * data->floor.width4));
	while (++pixel.y < (int)(8 * font_scale))
	{
		pixel.x = -1;
		while (++pixel.x < (int)(9 * font_scale))
		{
			tex.x = pixel.x * (1 / font_scale) + (nbr * 9 + 210);
			tex.y = pixel.y * (1 / font_scale);
			color = (*(int *)(font + ((tex.y * \
				data->mlx.font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu += 4;
		}
		if (pixel.x < (int)data->mlx.fg->width)
			menu += (data->mlx.fg->width * 4 - pixel.x * 4);
	}
}

static void	draw_alpha(t_data *data, t_vector_int pos, char c, \
						double font_scale)
{
	int				tex_pos_width[2];

	tex_pos_width[1] = 8 * font_scale;
	tex_pos_width[0] = (c - 'a') * 8 + 0;
	if (c == 'i' || c == 'l')
		tex_pos_width[1] = 4 * font_scale;
	if (c == 'j')
	{
		tex_pos_width[0] = (c - 'a') * 8 - 4;
		tex_pos_width[1] = 7 * font_scale;
	}
	if (c == 'k' || (c > 'm' && c <= 'w') || c == 'l')
		tex_pos_width[0] = (c - 'a') * 8 - 5;
	if (c == 'm' || c == 'x')
		tex_pos_width[0] = (c - 'a') * 8 - 9;
	if (c == 'm' || c == 'w')
		tex_pos_width[1] = 12 * font_scale;
	if (c == 'x')
		tex_pos_width[1] = 9 * font_scale;
	draw_char(data, pos, tex_pos_width, font_scale);
}

static void	alpha_pos_move(t_data *data, char c, t_vector_int *pos, \
							double font_scale)
{
	draw_alpha(data, *pos, c, font_scale);
	if (c == 'i' || c == 'l')
		pos->x += 4 * font_scale;
	else if (c == 'j')
		pos->x += 7 * font_scale;
	else if (c == 'm' || c == 'w')
		pos->x += 12 * font_scale;
	else if (c == 'x')
		pos->x += 9 * font_scale;
	else
		pos->x += 8 * font_scale;
}

void	draw_str(t_data *data, char *str, t_vector_int pos, \
				double font_scale)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			alpha_pos_move(data, str[i], &pos, font_scale);
		else if (ft_isdigit(str[i]))
		{
			draw_number(data, pos, str[i] - '0', font_scale);
			pos.x += 10 * font_scale;
		}
		else
			pos.x += 4 * font_scale;
		i++;
	}
}
