/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/27 14:23:33 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*get_enemy_texture(t_data *data, t_vector_double cam_dir, t_sprite *sprt)
{
	enum e_compas	dir;
	int				tex;

	if (sprt->kind == DOG)
		return (data->mlx.tex.enmy[1]);
	else if (sprt->kind == GUARD)
	{
		dir = get_enemy_direction(cam_dir, sprt->en_dat.dir);
		if (sprt->en_dat.state == HURT)
			tex = 3 + 5 * 8;
		else if (sprt->en_dat.state == DYING)
			tex = sprt->en_dat.frame % 5 + 5 * 8 + 4;
		else if (sprt->en_dat.state == DEAD)
			tex = 6 * 8;
		else if (sprt->en_dat.state == ATTACK)
			tex = 40 + sprt->en_dat.frame % 3;
		else
			tex = dir + sprt->en_dat.frame * 8;
		return (data->mlx.tex.enmy_sprites[0].tex[tex]);
	}
	return (data->mlx.tex.enmy[0]);
}

static t_transp	get_enemy_transp(t_sprite *sprt, t_vector_double cam_dir)
{
	enum e_compas	dir;
	int				tex;

	dir = get_enemy_direction(cam_dir, sprt->en_dat.dir);
	if (sprt->en_dat.state == HURT)
		tex = 3 + 5 * 8;
	else if (sprt->en_dat.state == DYING)
		tex = sprt->en_dat.frame % 5 + 5 * 8 + 4;
	else if (sprt->en_dat.state == DEAD)
		tex = 6 * 8;
	else if (sprt->en_dat.state == ATTACK)
		tex = 40 + sprt->en_dat.frame % 3;
	else
		tex = dir + sprt->en_dat.frame * 8;
	return (g_guard[tex]);
}

bool	can_draw_line(t_sprite_raycaster *c, t_vector_int pos, mlx_image_t *img)
{
	return (pos.x < (int)img->width \
			&& c->transform.y < c->zbuffer[pos.x]);
}

static void	draw_enemy_sprite_line(t_sprite_raycaster *c, mlx_image_t *i, \
							mlx_texture_t *t, t_vector_int pos, t_transp tr)
{
	uint32_t		clr;
	uint8_t			*fg;
	int				d;
	int				h;

	fg = i->pixels;
	h = (-(int)i->height + c->sprite_height) * 128;
	if (((pos.y) * 256) < h)
		pos.y = -(h / 256);
	if (pos.y < -1)
		pos.y = -1;
	while (++pos.y < c->draw_end.y && pos.y < 600)
	{
		d = (pos.y) * 256 + h;
		c->tex.y = ((d * TEX_SIZE) * c->inverse_sprite_height) / 256;
		if (c->tex.y >= (int)t->height || c->tex.y > tr.end.y)
			break ;
		if (c->tex.y >= 0 && c->tex.y >= tr.start.y)
		{
			clr = (*(int *)(t->pixels + (t->width * c->tex.y + c->tex.x) * 4));
			if (!is_transparent_color(clr))
				*(uint32_t *)(fg + (pos.y * i->width + pos.x) * 4) = clr;
		}
	}
}

void	draw_enemy_sprite(t_sprite_raycaster *c, t_transp tr, mlx_image_t *i, mlx_texture_t *tex)
{
	t_vector_int	pos;

	pos.x = c->draw_start.x - 1;
	if (pos.x < ((-c->sprite_width / 2 + c->sprite_screen_x)))
		pos.x = (-c->sprite_width / 2 + c->sprite_screen_x) - 1;
	while (++pos.x < c->draw_end.x && pos.x < (int)i->width)
	{
		c->tex.x = (int)(256 * (pos.x - (-c->sprite_width_halve + \
		c->sprite_screen_x)) * TEX_SIZE * c->inverse_sprite_width) / 256;
		if (c->tex.x > tr.end.x || c->tex.x > (int)tex->width)
			break ;
		if (can_draw_line(c, pos, i) && c->tex.x >= tr.start.x)
			draw_enemy_sprite_line(c, i, tex, pos, tr);
	}
}

// TODO make it work for the rest of the enemies.
void	draw_enemies(t_data *data, t_sprite *sprt, t_sprite_raycaster *c)
{
	mlx_texture_t		*texture;
	t_transp			transp;

	if (c->transform.y < 0.3)
		return ;
	texture = get_enemy_texture(data, data->cam.dir, sprt);
	if (sprt->kind == GUARD)
	{
		transp = get_enemy_transp(sprt, data->cam.dir);
		draw_enemy_sprite(c, transp, data->mlx.fg, texture);
	}
	else
	{
		printf("other type of enemy not implemented yet\n");
		return ;
	}
}
