/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 17:06:11 by shoogenb      ########   odam.nl         */
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
			tex = 7 + 5 * 8;
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

static void	draw_sprite_line(t_data *dat, t_vector_int pos, t_sprite *sprt, \
	mlx_texture_t	*tex)
{
	uint8_t				*fg;
	int					dist;
	uint32_t			color;
	t_vector_int		t;
	int					ypos_sheet;

	if (sprt->kind == DOG)
	{
		t = get_transp_y(sprt);
		ypos_sheet = get_ypos_sheet(sprt);
	}
	else
	{
		t.x = 128 - tex->height - 1;
		t.y = t.x - tex->height;
		ypos_sheet = 0;
	}
	fg = dat->mlx.fg->pixels + ((pos.y * dat->floor.width4) + pos.x * 4);
	while (++pos.y < dat->spr_cast.draw_end.y && pos.y < dat->hud.pos_hud.y)
	{
		dist = pos.y * 256 - dat->mlx.mlx_handle->height * 128 + \
			dat->spr_cast.sprite_height * 128;
		dat->spr_cast.tex.y = ((dist * tex->height / 7) \
			* dat->spr_cast.inverse_sprite_height) / 256;
		dat->spr_cast.tex.y += ypos_sheet;
		if (dat->spr_cast.tex.y < (int)tex->height && dat->spr_cast.tex.y > t.x)
		{
			if (t.y > 0 && dat->spr_cast.tex.y > t.y)
				break ;
			color = (*(unsigned int *)(tex->pixels + (tex->width * \
			dat->spr_cast.tex.y * 4 + dat->spr_cast.tex.x * 4)));
			if (color != 0x880098 && color != 0x8b009b)
				*(uint32_t *)fg = color;
		}
		fg += dat->floor.width4;
	}
}

//TODO try to use the draw_texture_area here
//TODO use the draw_sprite and all the different sprites 
// instead of the sheet. makes it easier to do all the transp checks etc.
// TODO make it work for the rest of the enemies.
void	draw_enemies(t_data *data, t_sprite *sprt, t_sprite_raycaster *c)
{
	t_vector_int		transp_x;
	mlx_texture_t		*texture;
	int					x;
	int					xpos_sheet;
	t_transp			transp;

	x = c->draw_start.x - 1;
	texture = get_enemy_texture(data, data->cam.dir, sprt);
	if (sprt->kind == DOG)
	{
		transp_x = get_transp_x(sprt, data->cam.dir);
		xpos_sheet = get_xpos_sheet(sprt, data->cam.dir);
	}
	else if (sprt->kind == GUARD)
	{
		transp.start.x = (128 - texture->width) / 2 - 1;
		transp.end.x = 127 - transp.start.x;
		transp.start.y = 5;
		transp.end.y = 127;
		if (transp.start.x < 0)
			transp.start.x = 0;
		if (transp.start.y < 0)
			transp.start.y = 0;
		draw_sprite(&data->spr_cast, &transp, data->mlx.fg, texture);
	}
	else
	{
		printf("other type of enemy not implemented yet\n");
		return ;
	}
	if (sprt->kind == DOG)
	{
		while (++x < c->draw_end.x)
		{
			c->tex.x = (int)(256 * (x - (-c->sprite_width_halve + \
				c->sprite_screen_x)) * (texture->width / 8) * \
				c->inverse_sprite_width) / 256;
			c->tex.x += xpos_sheet;
			if (c->transform.y > 0 && x > 0 && \
				x < data->mlx.mlx_handle->width && c->transform.y \
				< c->zbuffer[x] && c->tex.x > transp_x.x \
				&& c->tex.x < transp_x.y)
				draw_sprite_line(data, (t_vector_int){x, \
					c->draw_start.y}, sprt, texture);
		}
	}
}
