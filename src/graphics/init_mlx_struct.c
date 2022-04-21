/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/21 16:31:15 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool make_skybox(t_data *data, mlx_image_t *dst, mlx_texture_t *src)
{
	t_vector_double	p;
	t_vector_double	of;

	dst = mlx_new_image(data->mlx.mlx_handle, SCREEN_WIDTH * 3.14, SCREEN_HEIGHT);
	if (!dst)
	return (false);
	p.x = -1;
	while (++p.x < dst->width)
	{
		p.y = -1;
		of.x = ((double)p.x / dst->width) * src->width;
		while (++p.y < dst->height)
		{
			of.y = ((double)p.y / dst->height) * src->height;
			set_pixel(&dst, p.x, p.y, get_pixel(&src, of.x, of.y));
		}
	}
	return (true);
}

static bool	init_textures(t_data *data)
{
	data->mlx.tex.texarr[NORTH] = mlx_load_png(data->level.no_texture_path);
	data->mlx.tex.texarr[EAST] = mlx_load_png(data->level.ea_texture_path);
	data->mlx.tex.texarr[SOUTH] = mlx_load_png(data->level.so_texture_path);
	data->mlx.tex.texarr[WEST] = mlx_load_png(data->level.we_texture_path);
	data->mlx.tex.ce_texture = mlx_load_png("assets/skybox.png");
	if (data->mlx.tex.texarr[NORTH] == NULL || \
		data->mlx.tex.texarr[EAST] == NULL || \
		data->mlx.tex.texarr[SOUTH] == NULL || \
		data->mlx.tex.texarr[WEST] == NULL || \
		data->mlx.tex.ce_texture == NULL)
		return (false);
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
	data->cam.pitch = 0;
	data->caster.ray_dist = 0;
	return (make_skybox(data, &(data->mlx.bg), &(data->mlx.tex.ce_texture)););
}

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
	return (init_textures(data));
}
