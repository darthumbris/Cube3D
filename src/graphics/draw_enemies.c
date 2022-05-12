/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_enemies.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 13:09:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 11:34:00 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*get_enemy_texture(t_data *data, int kind)
{
	if (kind == DOG)
		return (data->mlx.tex.texarr[SPRITESHEET_DOG]);
	return (data->mlx.tex.texarr[SPRITESHEET_GUARD]);
}

static int	get_ypos_sheet(t_sprite *sprt)
{
	if (sprt->alive)
		return ((sprt->frame % 5) * 65);
	else if (sprt->kind == DOG)
		return (4 * 65);
	return (5 * 65);
}

static t_vector_int	get_transp_y(t_sprite *sprt)
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

static double	get_angle(t_vector_double dir)
{
	return (atan2(dir.y, dir.x));
}

static enum e_compas	get_enemy_direction(t_vector_double dir_cam, t_vector_double dir_enemy)
{
	const double	angle_cam = get_angle(dir_cam);
	const double	angle_enemy = get_angle(dir_enemy);
	double			dir_sprite;

	dir_sprite = angle_enemy - angle_cam + M_PI_2;
	if (dir_sprite < 0)
		dir_sprite += M_PI * 2;
	else if (dir_sprite > M_PI * 2)
		dir_sprite -= M_PI * 2;
	if (dir_sprite >= M_PI_8 && dir_sprite < (M_PI_4 + M_PI_8))
		return (C_NORTH_EAST);
	else if (dir_sprite >= (M_PI_4 + M_PI_8) && dir_sprite < (M_PI_2 + M_PI_8))
		return (C_NORTH);
	else if (dir_sprite >= (M_PI_2 + M_PI_8) && dir_sprite < (M_PI - M_PI_8))
		return (C_NORTH_WEST);
	else if (dir_sprite >= (M_PI - M_PI_8) && dir_sprite < (M_PI + M_PI_8))
		return (C_WEST);
	else if (dir_sprite >= (M_PI + M_PI_8) && dir_sprite < (M_PI - M_PI_8 + M_PI_2))
		return (C_SOUTH_WEST);
	else if (dir_sprite >= (M_PI - M_PI_8 + M_PI_2) && dir_sprite < (M_PI + M_PI_8 + M_PI_2))
		return (C_SOUTH);
	else if (dir_sprite >= (M_PI + M_PI_8 + M_PI_2) && dir_sprite < (2 * M_PI - M_PI_8))
		return (C_SOUTH_EAST);
	else
		return (C_EAST);
}

static t_vector_int	get_transp_x(t_sprite *sprt, t_vector_double cam_dir)
{
	enum e_compas	dir;
	t_vector_int	x;

	dir = get_enemy_direction(cam_dir, sprt->dir);
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

static int	get_xpos_sheet(t_sprite *sprt, t_vector_double cam_dir)
{
	const int	dir = get_enemy_direction(cam_dir, sprt->dir);

	if (sprt->alive)
		return ((dir % 8) * 65);
	else if (sprt->kind == DOG)
		return (3 * 65);
	return (4 * 65);
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
