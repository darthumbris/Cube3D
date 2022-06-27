/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 09:54:57 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/27 15:34:52 by shoogenb      ########   odam.nl         */
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
			|| kind == CAGE4 || kind == PANS1 || kind == PANS2 || \
			kind == STATUE || kind == GUARD);
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

bool	is_transparent_color(uint32_t color)
{
	return (color == 0x880098 || color == 0x8b009b || \
			color == 0x8c009c || !color);
}

static void	draw_sprite_line(t_sprite_raycaster *c, mlx_image_t *i, \
							mlx_texture_t *t, t_vector_int pos, t_transp tr)
{
	uint32_t		clr;
	uint8_t			*fg;
	int				d;
	int				h;

	fg = i->pixels;
	h = (-(int)i->height + c->sprite_height) * 128;
	if (((pos.y - c->move) * 256) < h)
		pos.y = -(h / 256) + c->move;
	if (pos.y < -1)
		pos.y = -1;
	while (++pos.y < c->draw_end.y && pos.y < 600)
	{
		d = (pos.y - c->move) * 256 + h;
		c->tex.y = ((d * TEX_SIZE) * c->inverse_sprite_height) / 256;
		if (c->tex.y >= (int)t->height || c->tex.y > tr.end.y)
			break ;
		if (c->tex.y >= 0)
		{
			clr = (*(int *)(t->pixels + (t->width * c->tex.y + c->tex.x) * 4));
			if (!is_transparent_color(clr))
				*(uint32_t *)(fg + (pos.y * i->width + pos.x) * 4) = clr;
		}
	}
}

//TODO check if this function can be improved.
void	draw_sprite(t_sprite_raycaster *c, t_transp tr, mlx_image_t *i, \
					mlx_texture_t *tex)
{
	t_vector_int	pos;

	if (c->transform.y < 0.3)
		return ;
	pos.x = c->draw_start.x - 1;
	if (pos.x < ((-c->sprite_width / 2 + c->sprite_screen_x)))
		pos.x = (-c->sprite_width / 2 + c->sprite_screen_x) - 1;
	while (++pos.x < c->draw_end.x)
	{
		c->tex.x = (int)(256 * (pos.x - (-c->sprite_width / 2 + \
			c->sprite_screen_x)) * TEX_SIZE * c->inverse_sprite_width) / 256;
		if (tex->width < 128)
			c->tex.x -= tr.start.x;
		if (c->tex.x >= (int)tex->width)
			break ;
		if (can_draw_line(c, pos, i) && c->tex.x >= 0)
		{
			pos.y = c->draw_start.y - 1;
			draw_sprite_line(c, i, tex, pos, tr);
		}
	}
}

void	draw_sprites(t_data *data)
{
	t_sprite_lst	*lst;

	data->spr_cast.inverse_determinant = 1.0 / \
	(data->cam.plane.x * data->cam.dir.y - data->cam.dir.x * data->cam.plane.y);
	sort_sprites(data, &(data->sprite_lst));
	lst = data->sprite_lst;
	while (lst)
	{
		if (lst->sprite_data.dist < RENDER_DIST_S && lst->sprite_data.kind && lst->sprite_data.dist > 0.5)
		{
			set_sprite_variables(data, lst);
			set_draw_pos(lst->sprite_data.kind, &data->spr_cast, data->mlx.fg);
			if (!is_enemy_kind(lst->sprite_data.kind))
			{
				draw_sprite(&data->spr_cast, lst->sprite_data.transp, \
					data->mlx.fg, data->mlx.tex.obj[lst->sprite_data.kind - 1]);
			}
			else
				update_enemies(data, &lst->sprite_data);
		}
		lst = lst->next;
	}
}
