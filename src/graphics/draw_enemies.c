/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 13:11:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_sprite_line(t_data *data, int x, int y, t_sprite *sprt)
{
	uint8_t		*fg;
	int			d;
	uint32_t	color;

	fg = data->mlx.fg->pixels + ((y * data->floor.width4) + x * 4);
	while (++y < data->spr_cast.draw_end.y && y < data->hud.pos_hud.y)
	{
		d = y * 256 - data->mlx.mlx_handle->height * 128 + \
			data->spr_cast.sprite_height * 128;
		data->spr_cast.tex.y = ((d * data->mlx.tex.texarr[sprt->kind]->height) \
			* data->spr_cast.inverse_sprite_height) / 256;
		if (data->spr_cast.tex.y < (int)data->mlx.tex.texarr[sprt->kind]->\
			height && data->spr_cast.tex.y > sprt->transp_end.y)
		{
			if (sprt->transp_begin.y > 0 && data->spr_cast.tex.y > \
				sprt->transp_begin.y)
				break ;
			color = (*(unsigned int *)(data->mlx.tex.texarr[sprt->kind]->pixels \
			+ (data->mlx.tex.texarr[sprt->kind]->width * data->spr_cast.tex.y * \
			4 + data->spr_cast.tex.x * 4)));
			if (color != 0xff000000)
				*(uint32_t *)fg = color;
		}
		fg += data->floor.width4;
	}
}

void	draw_enemies(t_data *data, int kind, t_sprite *sprt)
{
	int			x;

	x = data->spr_cast.draw_start.x;
	while (x < data->spr_cast.draw_end.x)
	{
		data->spr_cast.tex.x = (int)(256 * \
			(x - (-data->spr_cast.sprite_width_halve + \
			data->spr_cast.sprite_screen_x)) * \
			data->mlx.tex.texarr[kind]->width * \
		data->spr_cast.inverse_sprite_width) / 256;
		if (data->spr_cast.transform.y > 0 && x > 0 && \
			x < data->mlx.mlx_handle->width && \
			data->spr_cast.transform.y < data->spr_cast.zbuffer[x] && \
			data->spr_cast.tex.x > sprt->transp_begin.x && \
			data->spr_cast.tex.x < sprt->transp_end.x)
			draw_sprite_line(data, x, data->spr_cast.draw_start.y, sprt);
		x++;
	}
}
