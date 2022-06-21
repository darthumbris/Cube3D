/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 09:54:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/21 16:46:51 by shoogenb      ########   odam.nl         */
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

static bool	ceiling_sprite(int kind)
{
	return (kind == LAMP_G || kind == LAMP_R || kind == CHANDELIER || \
			kind == ORB || kind == CAGE1 || kind == CAGE2 || kind == CAGE3 \
			|| kind == CAGE4 || kind == PANS1 || kind == PANS2);
}

static void	set_draw_pos(int kind, t_sprite_raycaster *c, mlx_image_t *img)
{
	if (ceiling_sprite(kind))
		c->move = 0;
	else
		c->move = (int)((5 * TEX_SIZE) * c->inverse_transform_y);
	c->draw_start.y = (-(c->sprite_height << 1) + (img->height / 2)) + c->move;
	if (c->draw_start.y < 0)
		c->draw_start.y = 0;
	c->draw_end.y = ((c->sprite_height << 1) + (img->height / 2)) + c->move;
	if (c->draw_end.y >= (int)img->height)
		c->draw_end.y = img->height - 1;
	c->sprite_width = abs((int)(img->height * \
		c->inverse_transform_y));
	c->sprite_width_halve = c->sprite_width / 2;
	c->inverse_sprite_width = 1.0 / c->sprite_width;
	c->draw_start.x = -c->sprite_width_halve + c->sprite_screen_x;
	if (c->draw_start.x < 0)
		c->draw_start.x = 0;
	c->draw_end.x = c->sprite_width_halve + c->sprite_screen_x;
	if (c->draw_end.x >= (int)img->width)
		c->draw_end.x = img->width - 1;
}

static bool	in_sprite_area(t_sprite_raycaster *c, t_vector_int pos, mlx_image_t *img)
{
	return (c->transform.y > 0 && pos.x > 0 && pos.x < (int)img->width \
			&& c->transform.y < c->zbuffer[pos.x]);
}

static bool	in_color_area(t_vector_int texp, mlx_texture_t *tex)
{
	return (texp.x >= 0 && texp.x < (int)tex->width);
}

static void	draw_sprite(t_sprite_raycaster *c, t_sprite *sprt, mlx_image_t *i, mlx_texture_t *tex)
{
	int				d;
	uint8_t			*fg;
	uint32_t		color;
	t_vector_int	pos;
	t_vector_int	t;

	pos.y = c->draw_start.y - 1;
	fg = i->pixels + (((pos.y + 1) * i->width + c->draw_start.x) * 4);
	while (++pos.y < c->draw_end.y)
	{
		d = (pos.y - c->move) * 256 - i->height * 128 + c->sprite_height * 128;
		t.y = ((d * TEX_SIZE) * c->inverse_sprite_height) / 256;
		pos.x = c->draw_start.x - 1;
		if (t.y > sprt->transp_end.y)
			break ;
		while (++pos.x < c->draw_end.x && t.y < (int)tex->height && t.y >= 0)
		{
			t.x = (int)(256 * (pos.x - (-c->sprite_width_halve + \
			c->sprite_screen_x)) * TEX_SIZE * c->inverse_sprite_width) / 256;
			if (sprt->transp_begin.x > 0 && t.x < sprt->transp_end.x)
				t.x -= sprt->transp_begin.x;
			if (t.x > sprt->transp_end.x)
				break ;
			if (in_sprite_area(c, pos, i) && in_color_area(t, tex))
			{
				color = (*(uint32_t *)(tex->pixels + \
					((tex->width * t.y + t.x) * 4)));
				if (color != 0x880098 && color != 0x8b009b)
					*(uint32_t *)fg = color;
			}
			fg += 4;
		}
		if (pos.x < (int)i->width)
			fg += ((i->width - (pos.x - c->draw_start.x)) * 4);
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
			set_draw_pos(lst->sprite_data.kind, &data->spr_cast, data->mlx.fg);
			if (!is_enemy_kind(lst->sprite_data.kind))
				draw_sprite(&data->spr_cast, &lst->sprite_data, data->mlx.fg, \
					data->mlx.tex.obj[lst->sprite_data.kind - 1]);
			else
				update_enemies(data, &lst->sprite_data);
		}
		i++;
		lst = lst->next;
	}
}
