/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/27 13:35:45 by shoogenb      ########   odam.nl         */
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

static bool	in_sprite_area(t_sprite_raycaster *c, t_vector_int pos, mlx_image_t *img)
{
	return (pos.x > 0 && pos.x < (int)img->width \
			&& c->transform.y < c->zbuffer[pos.x]);
}

static bool	in_color_area(t_vector_int texp, mlx_texture_t *tex, t_transp tr)
{
	return (texp.x >= 0 && texp.x < (int)tex->width && \
			texp.y >= tr.start.y && texp.y <= tr.end.y);
}

void	draw_enemy_sprite(t_sprite_raycaster *c, t_transp tr, mlx_image_t *i, mlx_texture_t *tex)
{
	int				d;
	uint8_t			*fg;
	uint32_t		color;
	t_vector_int	pos;
	t_vector_int	t;

	pos.x = c->draw_start.x - 1;
	fg = i->pixels;
	while (++pos.x < c->draw_end.x && pos.x < (int)i->width)
	{
		t.x = (int)(256 * (pos.x - (-c->sprite_width_halve + \
		c->sprite_screen_x)) * TEX_SIZE * c->inverse_sprite_width) / 256;
		if (t.x > tr.end.x)
			break ;
		if (in_sprite_area(c, pos, i) && t.x >= tr.start.x)
		{
			pos.y = c->draw_start.y - 1;
			while (++pos.y < c->draw_end.y && pos.y < 600)
			{
				d = pos.y * 256 - i->height * 128 + c->sprite_height * 128;
				t.y = (d * TEX_SIZE * c->inverse_sprite_height) / 256;
				if (t.y > tr.end.y)
					break ;
				if (in_color_area(t, tex, tr))
				{
					color = (*(uint32_t *)(tex->pixels + (tex->width * t.y + t.x) * 4));
					if (color != 0x880098 && color != 0x8b009b && color != 0x8c009c && color)
						*(uint32_t *)(fg + (pos.y * i->width + pos.x) * 4) = color;
				}
			}
		}
	}
}

//TODO use the draw_sprite and all the different sprites 
// instead of the sheet. makes it easier to do all the transp checks etc.
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
