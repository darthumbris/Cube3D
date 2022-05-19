/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/19 16:51:37 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//temp for now
static bool	init_sprites(t_data *data)
{
	unsigned int	i;

	if (data->level.number_of_sprites == 0)
		return (true);
	data->sprite_lst = new_sprite(data->sprite[0]);
	i = 1;
	while (i < data->level.number_of_sprites)
	{
		add_sprite(&(data->sprite_lst), data->sprite[i]);
		i++;
	}
	sort_sprites(data, &data->sprite_lst);
	return (check_needed_textures_loaded(data));
}

static bool	init_textures(t_data *data)
{
	int	i;
	int	textures_to_load;

	if (data->bonus)
		textures_to_load = data->number_of_textures;
	else
		textures_to_load = SOUTH;
	i = 0;
	while (i <= textures_to_load)
	{
		if (data->level.paths.path[i])
			data->mlx.tex.texarr[i] = mlx_load_png(data->level.paths.path[i]);
		else
			data->mlx.tex.texarr[i] = NULL;
		i++;
	}
	data->caster.ray_dist = 0;
	if (data->bonus)
		return (init_sprites(data));
	return (true);
}

bool	init_mlx(t_data *data)
{
	if (SCREEN_WIDTH < 320 || SCREEN_HEIGHT < 240)
		return (false);
	data->mlx.mlx_handle = mlx_init
		(SCREEN_WIDTH, SCREEN_HEIGHT, "cube3D", false);
	if (data->mlx.mlx_handle == NULL)
		return (false);
	data->mlx.fg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.bg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.fg == NULL || data->mlx.bg == NULL)
		return (false);
	data->floor.inverse_width = 1 / (double)data->mlx.mlx_handle->width;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
	data->floor.halve_height = data->mlx.mlx_handle->height / 2;
	data->floor.halve_width = data->mlx.mlx_handle->width / 2;
	data->floor.width4 = data->mlx.mlx_handle->width * 4;
	data->spr_cast.zbuffer = malloc(sizeof(double) * SCREEN_WIDTH);
	if (!data->spr_cast.zbuffer)
		return (false);
	return (init_textures(data));
}
