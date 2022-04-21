/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 09:54:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/21 15:40:26 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_sprite_variables(t_data *data, t_sprite_lst *sprite)
{
	data->spr_cast.pos.x = sprite->sprite_data.map_pos.x - data->cam.pos.x;
	data->spr_cast.pos.y = sprite->sprite_data.map_pos.y - data->cam.pos.y;
	data->spr_cast.transform.x = data->spr_cast.inverse_determinant * \
		(data->cam.dir.y * data->spr_cast.pos.x - \
		data->cam.dir.x * data->spr_cast.pos.y);
	data->spr_cast.transform.y = data->spr_cast.inverse_determinant * \
		(-data->cam.plane.y * data->spr_cast.pos.x + \
		data->cam.plane.x * data->spr_cast.pos.y);
	data->spr_cast.inverse_transform_y = 1.0 / data->spr_cast.transform.y;
	data->spr_cast.sprite_screen_x = (int)(data->floor.halve_width * \
		(1 + data->spr_cast.transform.x * data->spr_cast.inverse_transform_y));
	data->spr_cast.sprite_height = \
		abs((int)(data->mlx.mlx_handle->height * \
		data->spr_cast.inverse_transform_y));
	data->spr_cast.inverse_sprite_height = 1.0 / data->spr_cast.sprite_height;
}

static void	set_draw_start_end(t_data *data)
{
	data->spr_cast.draw_start.y = -(data->spr_cast.sprite_height << 1) + \
		data->floor.halve_height;
	if (data->spr_cast.draw_start.y < 0)
		data->spr_cast.draw_start.y = 0;
	data->spr_cast.draw_end.y = (data->spr_cast.sprite_height << 1) + \
		data->floor.halve_height;
	if (data->spr_cast.draw_end.y >= data->mlx.mlx_handle->height)
		data->spr_cast.draw_end.y = data->mlx.mlx_handle->height - 1;
	data->spr_cast.sprite_width = abs((int)(data->mlx.mlx_handle->height * \
		data->spr_cast.inverse_transform_y));
	data->spr_cast.sprite_width_halve = data->spr_cast.sprite_width / 2;
	data->spr_cast.inverse_sprite_width = 1.0 / data->spr_cast.sprite_width;
	data->spr_cast.draw_start.x = -data->spr_cast.sprite_width_halve + \
		data->spr_cast.sprite_screen_x;
	if (data->spr_cast.draw_start.x < 0)
		data->spr_cast.draw_start.x = 0;
	data->spr_cast.draw_end.x = data->spr_cast.sprite_width_halve + \
		data->spr_cast.sprite_screen_x;
	if (data->spr_cast.draw_end.x >= data->mlx.mlx_handle->width)
		data->spr_cast.draw_end.x = data->mlx.mlx_handle->width - 1;
}

static void	draw_sprite(t_data *data, int kind)
{
	int			x;
	int			y;
	int			d;
	uint8_t		*fg;
	uint32_t	color;

	x = data->spr_cast.draw_start.x;
	while (x < data->spr_cast.draw_end.x)
	{
		data->spr_cast.tex.x = (int)(256 * \
			(x - (-data->spr_cast.sprite_width_halve + \
			data->spr_cast.sprite_screen_x)) * \
			data->mlx.sprites.texarr[kind]->width * \
		data->spr_cast.inverse_sprite_width) / 256;
		if (data->spr_cast.transform.y > 0 && x > 0 && \
			x < data->mlx.mlx_handle->width && \
			data->spr_cast.transform.y < data->spr_cast.zbuffer[x])
		{
			y = data->spr_cast.draw_start.y;
			fg = data->mlx.fg->pixels + ((y * data->floor.width4) + x * 4);
			while (y < data->spr_cast.draw_end.y)
			{
				d = y * 256 - data->mlx.mlx_handle->height * 128 + \
					data->spr_cast.sprite_height * 128;
				data->spr_cast.tex.y = \
					((d * data->mlx.sprites.texarr[kind]->height) * \
					data->spr_cast.inverse_sprite_height) / 256;
				color = 0xff000000;
				if (data->spr_cast.tex.y < \
					(int)data->mlx.sprites.texarr[kind]->height)
					color = (*(unsigned int *) \
					(data->mlx.sprites.texarr[kind]->pixels + \
					(data->mlx.sprites.texarr[kind]->width * \
					data->spr_cast.tex.y * 4 + data->spr_cast.tex.x * 4)));
				if (color != 0xff000000)
					*(uint32_t *)fg = color;
				fg += data->floor.width4;
				y++;
			}
		}
		x++;
	}
}

void	draw_sprites(t_data *data)
{
	t_sprite_lst	*lst;

	lst = data->sprite_lst;
	data->spr_cast.inverse_determinant = 1.0 / \
	(data->cam.plane.x * data->cam.dir.y - data->cam.dir.x * data->cam.plane.y);
	while (lst)
	{
		set_sprite_variables(data, lst);
		set_draw_start_end(data);
		draw_sprite(data, lst->sprite_data.kind);
		lst = lst->next;
	}
}
