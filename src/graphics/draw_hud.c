/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/29 13:20:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	init_hud(t_data *data)
{
	int		i;
	char	*center;
	char	*left;
	char	*right;

	center = ft_strdup("assets/hud/face_center_0.png");
	left = ft_strdup("assets/hud/face_left_0.png");
	right = ft_strdup("assets/hud/face_right_0.png");
	i = 0;
	while (i < 4)
	{
		data->mlx.faces_center[i] = mlx_load_png(center);
		data->mlx.faces_left[i] = mlx_load_png(left);
		data->mlx.faces_right[i] = mlx_load_png(right);
		center[ft_strlen(center) - 5] += 1;
		left[ft_strlen(left) - 5] += 1;
		right[ft_strlen(right) - 5] += 1;
		i++;
	}
	data->mlx.hud_texture = mlx_load_png("assets/hud/hud.png");
	data->mlx.numbers = mlx_load_png("assets/hud/numbers.png");
	data->mlx.hud = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.hud_scale = (SCREEN_WIDTH / data->mlx.hud_texture->width);
	data->mlx.inv_hud_scale = 1.0 / data->mlx.hud_scale;
}

void	draw_single_nbr(t_data *data, int nbr, int x_pos)
{
	int				x;
	int				y;
	uint8_t			*hud;
	uint8_t			*pixels;

	pixels = data->mlx.numbers->pixels;
	if (nbr < 0)
		return ;
	x = 0;
	while (x < 32)
	{
		y = 0;
		hud = data->mlx.hud->pixels + (((x + x_pos) * 4) + \
			(data->mlx.mlx_handle->height - 94) * data->floor.width4);
		while (y < 64)
		{
			*(uint32_t *)hud = (*(int *)(pixels + \
				((y * data->mlx.numbers->width + x + ((nbr % 10) * 36)) * 4)));
			hud += data->floor.width4;
			y++;
		}
		x++;
	}
}

void	draw_score(t_data *data, int nbr)
{
	if (nbr > 9999)
		draw_single_nbr(data, nbr / 10000, 55 * data->mlx.hud_scale);
	if (nbr > 999)
		draw_single_nbr(data, nbr / 1000, 63 * data->mlx.hud_scale);
	if (nbr > 99)
		draw_single_nbr(data, nbr / 100, 71 * data->mlx.hud_scale);
	if (nbr > 9)
		draw_single_nbr(data, nbr / 10, 79 * data->mlx.hud_scale);
	draw_single_nbr(data, nbr, 87 * data->mlx.hud_scale);
}

void	draw_numbers(t_data *data)
{
	draw_single_nbr(data, data->level.level_number, 24 * data->mlx.hud_scale);
	draw_score(data, data->player.score);
	draw_single_nbr(data, data->player.lives, 112 * data->mlx.hud_scale);
	if (data->player.health > 99)
		draw_single_nbr(data, data->player.health / 100, 168 * data->mlx.hud_scale);
	if (data->player.health > 9)
		draw_single_nbr(data, data->player.health / 10, 176 * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.health, 736);
	if (data->player.ammo > 9)
		draw_single_nbr(data, data->player.ammo / 10, 216 * data->mlx.hud_scale);
	draw_single_nbr(data, data->player.ammo, 224 * data->mlx.hud_scale);
}

/*
//TODO make this draw the hud to scale using the hud.png. 
	Also needs to be updated
//TODO the minimap can be put in the right corner of the hud
*/

void	draw_hud(t_data *data)
{
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*pixels;
	uint8_t			*hud;

	pixel.x = 0;
	pixels = data->mlx.hud_texture->pixels;
	while (pixel.x < data->mlx.mlx_handle->width)
	{
		tex.x = pixel.x * data->mlx.inv_hud_scale;
		hud = data->mlx.hud->pixels + (((data->mlx.mlx_handle->height - 1) * \
			data->mlx.mlx_handle->width * 4 + (pixel.x * 4)));
		pixel.y = data->mlx.mlx_handle->height - \
			data->mlx.hud_texture->height / data->mlx.inv_hud_scale;
		while (pixel.y < data->mlx.mlx_handle->height)
		{
			tex.y = ((data->mlx.mlx_handle->height - 1) - pixel.y) * \
				data->mlx.inv_hud_scale;
			*(uint32_t *)hud = (*(int *)(pixels + \
				((tex.y * data->mlx.hud_texture->width + tex.x) * 4)));
			hud -= data->mlx.mlx_handle->width * 4;
			pixel.y++;
		}
		pixel.x++;
	}
}
