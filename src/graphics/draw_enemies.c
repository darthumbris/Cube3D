/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 12:28:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_frames(t_vector_double cam_dir, t_sprite *sprt, int enemy)
{
	enum e_compas	dir;
	int				dir_frames;
	t_sprt_sht_data	sheet;
	int				frames;

	sheet = g_enemy_sprt_data[enemy];
	dir = 0;
	if (sheet.rotation == true)
		dir = get_enemy_direction(cam_dir, sprt->en_dat.dir);
	dir_frames = 1;
	if (sheet.rotation == true)
		dir_frames = 8;
	if (sprt->en_dat.state < ATTACK)
		frames = dir * (sprt->en_dat.frame % sheet.move_frames);
	else
		frames = dir_frames * sheet.move_frames;
	if (sprt->en_dat.state >= HURT)
		frames += sheet.attack_frames;
	if (sprt->en_dat.state >= DYING)
		frames += sheet.hit_frames;
	if (sprt->en_dat.state == DYING)
		frames += sprt->en_dat.frame % sheet.death_frames;
	else if (sprt->en_dat.state == DEAD)
		frames = sheet.total_sprites - 1;
	if (sprt->en_dat.state == ATTACK)
		frames += sprt->en_dat.frame % sheet.attack_frames;
	return (frames);
}

static mlx_texture_t	*get_enemy_texture(t_data *data, \
	t_vector_double cam_dir, t_sprite *sprt, int enemy)
{
	int	frames;

	frames = get_frames(cam_dir, sprt, enemy);
	return (data->mlx.tex.enmy_sprites[enemy].tex[frames]);
}

static t_transp	get_enemy_transp(t_sprite *sprt, t_vector_double cam_dir, \
								int enemy, t_sprite_raycaster *c)
{
	int				frames;

	frames = get_frames(cam_dir, sprt, enemy);
	return (c->tr_lst[enemy][frames]);
}

bool	can_draw_line(t_sprite_raycaster *c, t_vector_int pos, mlx_image_t *img)
{
	return (pos.x < (int)img->width \
			&& c->transform.y < c->zbuffer[pos.x]);
}

// static void	draw_enemy_sprite_line(t_sprite_raycaster *c, mlx_image_t *i,
// 							mlx_texture_t *t, t_vector_int pos, t_transp tr)
// {
// 	uint32_t		clr;
// 	uint8_t			*fg;
// 	int				d;
// 	int				h;

// 	fg = i->pixels;
// 	h = (-(int)i->height + c->sprite_height) * 128;
// 	if (((pos.y) * 256) < h)
// 		pos.y = -(h / 256);
// 	if (pos.y < -1)
// 		pos.y = -1;
// 	while (++pos.y < c->draw_end.y && pos.y < 600)
// 	{
// 		d = (pos.y) * 256 + h;
// 		c->tex.y = ((d * TEX_SIZE) * c->inverse_sprite_height) / 256;
// 		if (c->tex.y >= (int)t->height || c->tex.y > tr.end.y)
// 			break ;
// 		if (c->tex.y >= 0 && c->tex.y >= tr.start.y)
// 		{
// 			clr = (*(int *)(t->pixels + (t->width * c->tex.y + c->tex.x) * 4));
// 			if (!is_transparent_color(clr))
// 				*(uint32_t *)(fg + (pos.y * i->width + pos.x) * 4) = clr;
// 		}
// 	}
// }

// void	draw_enemy_sprite(t_sprite_raycaster *c, t_transp tr, mlx_image_t *i, 
						// mlx_texture_t *tex)
// {
// 	t_vector_int	pos;

// 	pos.x = c->draw_start.x - 1;
// 	if (pos.x < ((-c->sprite_width / 2 + c->sprite_screen_x)))
// 		pos.x = (-c->sprite_width / 2 + c->sprite_screen_x) - 1;
// 	while (++pos.x < c->draw_end.x && pos.x < (int)i->width)
// 	{
// 		c->tex.x = (int)(256 * (pos.x - (-c->sprite_width_halve + 
// 		c->sprite_screen_x)) * TEX_SIZE * c->inverse_sprite_width) / 256;
// 		if (c->tex.x > tr.end.x || c->tex.x > (int)tex->width)
// 			break ;
// 		if (can_draw_line(c, pos, i) && c->tex.x >= tr.start.x)
// 			draw_enemy_sprite_line(c, i, tex, pos, tr);
// 	}
// }

// TODO make it work for the rest of the enemies.
void	draw_enemies(t_data *data, t_sprite *sprt, t_sprite_raycaster *c)
{
	mlx_texture_t		*texture;
	t_transp			transp;

	if (c->transform.y < 0.3)
		return ;
	texture = get_enemy_texture(data, data->cam.dir, sprt, sprt->kind - GUARD);
	transp = get_enemy_transp(sprt, data->cam.dir, sprt->kind - GUARD, c);
	draw_sprite(c, transp, data->mlx.fg, texture);
}
