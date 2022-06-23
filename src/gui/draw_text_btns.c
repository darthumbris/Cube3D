/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_text_btns.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:56:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 15:31:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_char(t_mlx *mlx, t_vector_int pos, int tex_pos_width[2], \
						double font_scale)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	font = mlx->font->pixels;
	pixel.y = -1;
	menu = mlx->menu_editor->pixels + ((pos.x + \
			(pos.y + (int)font_scale) * mlx->menu_editor->width) * 4);
	while (++pixel.y < 8 * font_scale)
	{
		pixel.x = -1;
		while (++pixel.x < tex_pos_width[1])
		{
			tex.x = pixel.x * (1 / font_scale) + tex_pos_width[0];
			tex.y = pixel.y * (1 / font_scale);
			color = (*(int *)(font + ((tex.y * mlx->font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu += 4;
		}
		if (pixel.x < (int)mlx->menu_editor->width)
			menu += (mlx->menu_editor->width * 4 - (tex_pos_width[1]) * 4);
	}
}

static void	draw_number(t_mlx *mlx, t_vector_int pos, int nbr, \
						double font_scale)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	pixel.y = -1;
	font = mlx->font->pixels;
	menu = mlx->menu_editor->pixels + \
			((pos.x + pos.y * mlx->menu_editor->width) * 4);
	while (++pixel.y < (int)(8 * font_scale))
	{
		pixel.x = -1;
		while (++pixel.x < (int)(12 * font_scale))
		{
			tex.x = pixel.x * (1 / font_scale) + (nbr * 12);
			tex.y = pixel.y * (1 / font_scale) + 8;
			color = (*(int *)(font + ((tex.y * mlx->font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu += 4;
		}
		if (pixel.x < (int)mlx->menu_editor->width)
			menu += (mlx->menu_editor->width * 4 - pixel.x * 4);
	}
}

static void	draw_alpha(t_mlx *mlx, t_vector_int pos, char c, \
						double font_scale)
{
	int				tex_pos_width[2];

	tex_pos_width[1] = 12 * font_scale;
	tex_pos_width[0] = (c - 'a') * 12;
	draw_char(mlx, pos, tex_pos_width, font_scale);
}

static void	alpha_pos_move(t_mlx *mlx, char c, t_vector_int *pos, \
							double font_scale)
{
	draw_alpha(mlx, *pos, c, font_scale);
	if (c == 'l' || c == 'i')
		pos->x += 5 * font_scale;
	else
		pos->x += 8 * font_scale;
	if (c == 'm' || c == 'w')
		pos->x += 2 * font_scale;
}

void	draw_str(t_mlx *mlx, char *str, t_vector_int pos, \
				double font_scale)
{
	int				i;

	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
		{
			alpha_pos_move(mlx, str[i], &pos, font_scale);
			if (str[i + 1] == 'm' || str[i + 1] == 'w')
				pos.x += 2 * font_scale;
			else if (str[i + 1] == 'l' || str[i + 1] == 'i')
				pos.x -= 2 * font_scale;
		}
		else if (ft_isdigit(str[i]))
		{
			draw_number(mlx, pos, str[i] - '0', font_scale);
			pos.x += 10 * font_scale;
		}
		else if (str[i] == '.')
		{
			pos.x -= 2 * font_scale;
			draw_number(mlx, pos, 10, font_scale);
			pos.x += 6 * font_scale;
		}
		else
			pos.x += 4 * font_scale;
	}
}
