/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 16:53:57 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*get_enemy_texture(t_data *data, int kind)
{
	if (kind == DOG)
		return (data->mlx.tex.texarr[SPRITESHEET_DOG]);
	return (data->mlx.tex.texarr[SPRITESHEET_GUARD]);
}

t_vector_int	get_y_pos_sheet(t_sprite *sprt)
{
	t_vector_int	y;

	if (sprt->kind == GUARD)
	{
		if (sprt->alive)
		{
			y.x = 15 + (sprt->frame % 5) * 65;
			y.y = 63 + (sprt->frame % 5) * 65;
		}
		else
		{
			y.x = 50 + 5 * 65;
			y.y = 63 + 5 * 65;
		}
	}
	else
	{
		if (sprt->alive)
		{
			y.x = 26 + (sprt->frame % 5) * 65;
			y.y = 63 + (sprt->frame % 5) * 65;
		}
		else
		{
			y.x = 50 + 4 * 65;
			y.y = 63 + 4 * 65;
		}
	}
	return (y);
}

static void	draw_sprite_line(t_data *data, t_vector_int pos, t_sprite *sprt, \
	mlx_texture_t	*texture)
{
	uint8_t				*fg;
	int					d;
	uint32_t			color;
	const t_vector_int	transp = get_y_pos_sheet(sprt);

	fg = data->mlx.fg->pixels + ((pos.y * data->floor.width4) + pos.x * 4);
	while (++pos.y < data->spr_cast.draw_end.y && pos.y < data->hud.pos_hud.y)
	{
		d = pos.y * 256 - data->mlx.mlx_handle->height * 128 + \
			data->spr_cast.sprite_height * 128;
		data->spr_cast.tex.y = ((d * texture->height / 7) \
			* data->spr_cast.inverse_sprite_height) / 256;
		if (sprt->alive)
			data->spr_cast.tex.y += (sprt->frame % 5) * 65;
		else if (sprt->kind == GUARD)
			data->spr_cast.tex.y += 5 * 65;
		else
			data->spr_cast.tex.y += 4 * 65;
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

static enum e_compas	get_enemy_direction(t_vector_double dir)
{
	if (dir.y > 0.38)
	{
		if (dir.x > -0.38 && dir.x < 0.38)
			return (C_NORTH);
		else if (dir.x < 0)
			return (C_NORTH_WEST);
		else
			return (C_NORTH_EAST);
	}
	else if (dir.y < -0.38)
	{
		if (dir.x > -0.38 && dir.x < 0.38 && dir.y < 0)
			return (C_SOUTH);
		else if (dir.x < 0)
			return (C_SOUTH_WEST);
		else
			return (C_SOUTH_EAST);
	}
	else if (dir.y < 0.38 && dir.y > -0.38 && dir.x < 0)
		return (C_WEST);
	else
		return (C_EAST);
}

static t_vector_int	get_texture_x(t_sprite *sprt)
{
	enum e_compas	dir;
	t_vector_int	x;

	dir = get_enemy_direction(sprt->dir);
	if (sprt->kind == DOG)
	{
		if (sprt->alive)
		{
			x.x = 2 + (dir % 8) * 65;
			x.y = 63 + (dir % 8) * 65;
		}
		else
		{
			x.x = 6 + 3 * 65;
			x.y = 63 + 3 * 65;
		}
	}
	else
	{
		if (sprt->alive)
		{
			x.x = 13 + (dir % 8) * 65;
			x.y = 63 + (dir % 8) * 65;
		}
		else
		{
			x.x = 14 + 4 * 65;
			x.y = 63 + 4 * 65;
		}
	}
	return (x);
}

void	draw_enemies(t_data *data, t_sprite *sprt)
{
	t_vector_int	transp_x;
	mlx_texture_t	*texture;
	int				x;
	enum e_compas	dir;

	dir = get_enemy_direction(sprt->dir);
	x = data->spr_cast.draw_start.x;
	transp_x = get_texture_x(sprt);
	texture = get_enemy_texture(data, sprt->kind);
	while (x < data->spr_cast.draw_end.x)
	{
		data->spr_cast.tex.x = (int)(256 * \
			(x - (-data->spr_cast.sprite_width_halve + \
			data->spr_cast.sprite_screen_x)) * \
			(texture->width / 8) * \
		data->spr_cast.inverse_sprite_width) / 256;
		if (sprt->alive)
			data->spr_cast.tex.x += (dir % 8) * 65;
		else if (sprt->kind == DOG)
			data->spr_cast.tex.x += 3 * 65;
		else
			data->spr_cast.tex.x += 4 * 65;
		if (data->spr_cast.transform.y > 0 && x > 0 && \
			x < data->mlx.mlx_handle->width && \
			data->spr_cast.transform.y < data->spr_cast.zbuffer[x])
			draw_sprite_line(data, (t_vector_int){x, data->spr_cast.draw_start.y}, sprt, texture);
		x++;
	}
}
