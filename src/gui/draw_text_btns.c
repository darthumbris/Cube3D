/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_text_btns.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:56:43 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/14 13:15:39 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_char(t_data *data, t_vector_int pos, int tex_pos_width[2], \
						double font_scale, mlx_image_t *img)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	font = data->mlx.font->pixels;
	pixel.y = -1;
	menu = img->pixels + (((pos.x) * 4) + \
			(pos.y) * img->width * 4);
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
		if (pixel.x < (int)img->width)
			menu += (img->width * 4 - (tex_pos_width[1]) * 4);
	}
}

static void	draw_number(t_data *data, t_vector_int pos, int nbr, \
						double font_scale, mlx_image_t *img)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*menu;
	uint8_t			*font;
	uint32_t		color;

	pixel.y = -1;
	font = data->mlx.font->pixels;
	menu = img->pixels + (pos.x * 4 + \
			(pos.y * img->width * 4));
	while (++pixel.y < (int)(8 * font_scale))
	{
		pixel.x = -1;
		while (++pixel.x < (int)(12 * font_scale))
		{
			tex.x = pixel.x * (1 / font_scale) + (nbr * 12);
			tex.y = pixel.y * (1 / font_scale) + 8;
			color = (*(int *)(font + ((tex.y * \
				data->mlx.font->width + tex.x) * 4)));
			if (color == 4278190080)
				*(uint32_t *)menu = color;
			menu += 4;
		}
		if (pixel.x < (int)img->width)
			menu += (img->width * 4 - pixel.x * 4);
	}
}

static void	draw_alpha(t_data *data, t_vector_int pos, char c, \
						double font_scale, mlx_image_t *img)
{
	int				tex_pos_width[2];

	tex_pos_width[1] = 12 * font_scale;
	tex_pos_width[0] = (c - 'a') * 12;
	draw_char(data, pos, tex_pos_width, font_scale, img);
}

static void	alpha_pos_move(t_data *data, char c, t_vector_int *pos, \
							double font_scale, mlx_image_t *img)
{
	draw_alpha(data, *pos, c, font_scale, img);
	if (c == 'l' || c == 'i')
		pos->x += 5 * font_scale;
	else
		pos->x += 8 * font_scale;
	if (c == 'm' || c == 'w')
		pos->x += 2 * font_scale;
}

void	draw_str(t_data *data, char *str, t_vector_int pos, \
				double font_scale, mlx_image_t *img)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			alpha_pos_move(data, str[i], &pos, font_scale, img);
			if (str[i + 1] == 'm' || str[i + 1] == 'w')
				pos.x += 2 * font_scale;
			else if (str[i + 1] == 'l' || str[i + 1] == 'i')
				pos.x -= 2 * font_scale;
		}
		else if (ft_isdigit(str[i]))
		{
			draw_number(data, pos, str[i] - '0', font_scale, img);
			pos.x += 10 * font_scale;
		}
		else
			pos.x += 4 * font_scale;
		i++;
	}
}
