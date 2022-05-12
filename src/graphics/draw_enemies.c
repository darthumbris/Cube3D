/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 14:00:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*get_enemy_texture(t_data *data, int kind)
{
	if (kind == DOG)
		return (data->mlx.tex.texarr[SPRITESHEET_DOG]);
	return (data->mlx.tex.texarr[SPRITESHEET_GUARD]);
}

static void	draw_sprite_line(t_data *data, t_vector_int pos, t_sprite *sprt, \
	mlx_texture_t	*texture)
{
	uint8_t				*fg;
	int					dist;
	uint32_t			color;
	const t_vector_int	transp = get_transp_y(sprt);
	const int			ypos_sheet = get_ypos_sheet(sprt);

	fg = data->mlx.fg->pixels + ((pos.y * data->floor.width4) + pos.x * 4);
	while (++pos.y < data->spr_cast.draw_end.y && pos.y < data->hud.pos_hud.y)
	{
		dist = pos.y * 256 - data->mlx.mlx_handle->height * 128 + \
			data->spr_cast.sprite_height * 128;
		data->spr_cast.tex.y = ((dist * texture->height / 7) \
			* data->spr_cast.inverse_sprite_height) / 256;
		data->spr_cast.tex.y += ypos_sheet;
		if (data->spr_cast.tex.y < (int)texture->height && data->spr_cast.tex.y \
			> transp.x)
		{
			if (transp.y > 0 && data->spr_cast.tex.y > transp.y)
				break ;
			color = (*(unsigned int *)(texture->pixels + (texture->width * \
			data->spr_cast.tex.y * 4 + data->spr_cast.tex.x * 4)));
			if (color != 4287103128 && color != 0xffffffff)
				*(uint32_t *)fg = color;
		}
		fg += data->floor.width4;
	}
}

void	draw_enemies(t_data *data, t_sprite *sprt)
{
	const t_vector_int	transp_x = get_transp_x(sprt, data->cam.dir);
	mlx_texture_t		*texture;
	int					x;
	const int			xpos_sheet = get_xpos_sheet(sprt, data->cam.dir);

	x = data->spr_cast.draw_start.x;
	texture = get_enemy_texture(data, sprt->kind);
	while (++x < data->spr_cast.draw_end.x)
	{
		data->spr_cast.tex.x = (int)(256 * \
			(x - (-data->spr_cast.sprite_width_halve + \
			data->spr_cast.sprite_screen_x)) * \
			(texture->width / 8) * \
		data->spr_cast.inverse_sprite_width) / 256;
		data->spr_cast.tex.x += xpos_sheet;
		if (data->spr_cast.transform.y > 0 && x > 0 && \
			x < data->mlx.mlx_handle->width && data->spr_cast.transform.y \
			< data->spr_cast.zbuffer[x] && data->spr_cast.tex.x > transp_x.x \
			&& data->spr_cast.tex.x < transp_x.y)
			draw_sprite_line(data, (t_vector_int){x, \
				data->spr_cast.draw_start.y}, sprt, texture);
	}
}
