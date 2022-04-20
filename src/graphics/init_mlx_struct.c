/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/20 16:26:03 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	init_textures(t_data *data)
{
	data->mlx.tex.texarr[NORTH] = mlx_load_png(data->level.no_texture_path);
	data->mlx.tex.texarr[EAST] = mlx_load_png(data->level.ea_texture_path);
	data->mlx.tex.texarr[SOUTH] = mlx_load_png(data->level.so_texture_path);
	data->mlx.tex.texarr[WEST] = mlx_load_png(data->level.we_texture_path);
	if (data->mlx.tex.texarr[NORTH] == NULL || \
		data->mlx.tex.texarr[EAST] == NULL || \
		data->mlx.tex.texarr[SOUTH] == NULL || \
		data->mlx.tex.texarr[WEST] == NULL)
		return (false);
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
	data->caster.ray_dist = 0;
	return (true);
}

#include <stdio.h>
bool	init_mlx(t_data *data)
{
	data->mlx.mlx_handle = mlx_init
		(SCREEN_WIDTH, SCREEN_HEIGHT, "cube3D", false);
	if (data->mlx.mlx_handle == NULL)
		return (false);
	data->mlx.fg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.fg == NULL)
		return (false);
	data->floor.inverse_width = 1 / (double)data->mlx.mlx_handle->width;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
	data->floor.halve_height = data->mlx.mlx_handle->height / 2;
	data->floor.width4 = data->mlx.mlx_handle->width * 4;
	return (init_textures(data));
}
