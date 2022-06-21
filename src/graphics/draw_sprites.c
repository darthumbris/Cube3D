/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 09:54:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/21 13:32:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO: make this more readable
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
	data->spr_cast.move_screen = 0;
	data->spr_cast.draw_start.y = (-(data->spr_cast.sprite_height << 1) + \
		data->floor.halve_height);
	if (data->spr_cast.draw_start.y < 0)
		data->spr_cast.draw_start.y = 0;
	data->spr_cast.draw_end.y = ((data->spr_cast.sprite_height << 1) + \
		data->floor.halve_height);
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

//TODO change it so it does it in a similar way as draw texture function
//TODO try to do it so the sprites don't need to be 128 x 128?
static void	draw_sprite(t_sprite_raycaster *c, t_sprite *sprt, mlx_image_t *img, mlx_texture_t *tex)
{
	int				d;
	uint8_t			*fg;
	uint32_t		color;
	t_vector_int	pos;
	t_vector_int	texp;

	pos.y = c->draw_start.y - 1;
	fg = img->pixels + (((pos.y + 1) * img->width + c->draw_start.x) * 4);
	while (++pos.y < c->draw_end.y)
	{
		d = pos.y * 256 - (int)img->height * 128 + c->sprite_height * 128;
		texp.y = ((d * tex->height) * c->inverse_sprite_height) / 256;
		pos.x = c->draw_start.x - 1;
		while (++pos.x < c->draw_end.x)
		{
			texp.x = (int)(256 * (pos.x - (-c->sprite_width_halve + \
			c->sprite_screen_x)) * tex->width * c->inverse_sprite_width) / 256;
			if (c->transform.y > 0 && pos.x > 0 && pos.x < (int)img->width \
			&& c->transform.y < c->zbuffer[pos.x] && texp.x > \
			sprt->transp_begin.x && texp.x < sprt->transp_end.x && \
			texp.y < (int)tex->height && texp.y > 0)
			{
				color = (*(uint32_t *)(tex->pixels + ((tex->width * \
					texp.y + texp.x) * 4)));
				if (color != 0xff000000)
					*(uint32_t *)fg = color;
			}
			fg += 4;
		}
		if (pos.x < (int)img->width)
			fg += ((img->width - (c->draw_end.x - c->draw_start.x)) * 4);
	}
}

void	draw_sprites(t_data *data)
{
	t_sprite_lst	*lst;
	int				i;

	data->spr_cast.inverse_determinant = 1.0 / \
	(data->cam.plane.x * data->cam.dir.y - data->cam.dir.x * data->cam.plane.y);
	sort_sprites(data, &(data->sprite_lst));
	lst = data->sprite_lst;
	i = 0;
	while (lst)
	{
		if (lst->sprite_data.dist < RENDER_DIST_S && lst->sprite_data.kind)
		{
			set_sprite_variables(data, lst);
			set_draw_start_end(data);
			if (!is_enemy_kind(lst->sprite_data.kind))
				draw_sprite(&data->spr_cast, &lst->sprite_data, data->mlx.fg, data->mlx.tex.obj[lst->sprite_data.kind - 1]);
			// else
			// 	update_enemies(data, &lst->sprite_data);
		}
		i++;
		lst = lst->next;
	}
}
