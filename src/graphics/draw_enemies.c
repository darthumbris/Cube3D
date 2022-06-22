/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:13:44 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*get_enemy_texture(t_data *data, int kind)
{
	if (kind == DOG)
		return (data->mlx.tex.enmy[1]);
	return (data->mlx.tex.enmy[0]);
}

static void	draw_sprite_line(t_data *dat, t_vector_int pos, t_sprite *sprt, \
	mlx_texture_t	*tex)
{
	uint8_t				*fg;
	int					dist;
	uint32_t			color;
	const t_vector_int	t = get_transp_y(sprt);
	const int			ypos_sheet = get_ypos_sheet(sprt);

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
			if (color != 4287103128 && color != 0xffffffff)
				*(uint32_t *)fg = color;
		}
		fg += dat->floor.width4;
	}
}

//TODO try to use the draw_texture_area here
void	draw_enemies(t_data *data, t_sprite *sprt, t_sprite_raycaster *c)
{
	const t_vector_int	transp_x = get_transp_x(sprt, data->cam.dir);
	mlx_texture_t		*texture;
	int					x;
	const int			xpos_sheet = get_xpos_sheet(sprt, data->cam.dir);

	x = c->draw_start.x - 1;
	texture = get_enemy_texture(data, sprt->kind);
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
