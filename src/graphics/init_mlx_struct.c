/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/25 11:12:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

//temp for now
static bool	init_sprites(t_data *data)
{
	printf("number of sprites: %d\n", data->level.number_of_sprites);
	if (data->level.number_of_sprites == 0)
	{
		printf("true\n");
		return true;
	}
	data->sprite_lst = new_sprite(data->sprite[0]);
	unsigned int i;

	i = 1;
	while (i < data->level.number_of_sprites)
	{
		data->sprite_lst = add_sprite(&(data->sprite_lst), data->sprite[i]);
		i++;
	}
	data->spr_cast.sprite_order = malloc(sizeof(int) * data->level.number_of_sprites);
	data->spr_cast.sprite_distance = malloc(sizeof(double) * data->level.number_of_sprites);
	data->spr_cast.zbuffer = malloc(sizeof(double) * SCREEN_WIDTH);
	data->mlx.sprites.texarr[LAMP] = mlx_load_png(data->level.paths.path[SPRITE_0]);
	if (data->mlx.sprites.texarr[LAMP] == NULL)
		return (false);
	data->mlx.sprites.texarr[BARREL] = mlx_load_png(data->level.paths.path[SPRITE_1]);
	if (data->mlx.sprites.texarr[BARREL] == NULL)
		return (false);
	data->mlx.sprites.texarr[PILLAR] = mlx_load_png(data->level.paths.path[SPRITE_2]);
	if (data->mlx.sprites.texarr[PILLAR] == NULL)
		return (false);
	set_sprites(data);
	sort_sprites(data, &data->sprite_lst);
	return (true);
}

static bool	init_textures(t_data *data)
{
	data->mlx.tex.texarr[NORTH] = mlx_load_png(data->level.paths.path[NORTH]);
	data->mlx.tex.texarr[EAST] = mlx_load_png(data->level.paths.path[EAST]);
	data->mlx.tex.texarr[SOUTH] = mlx_load_png(data->level.paths.path[SOUTH]);
	data->mlx.tex.texarr[WEST] = mlx_load_png(data->level.paths.path[WEST]);
	if (data->mlx.tex.texarr[NORTH] == NULL || \
		data->mlx.tex.texarr[EAST] == NULL || \
		data->mlx.tex.texarr[SOUTH] == NULL || \
		data->mlx.tex.texarr[WEST] == NULL)
		return (false);
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
	data->caster.ray_dist = 0;
	if (data->bonus)
	{
		data->mlx.tex.texarr[FLOOR] = \
			mlx_load_png(data->level.paths.path[FLOOR]);
		data->mlx.tex.texarr[CEILING] = \
			mlx_load_png(data->level.paths.path[CEILING]);
		if (data->mlx.tex.texarr[FLOOR] == NULL || \
		data->mlx.tex.texarr[CEILING] == NULL)
			return (false);
		return (init_sprites(data));
	}
	return (true);
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
	data->floor.inverse_width = 1 / (double)data->mlx.mlx_handle->width;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
	data->floor.halve_height = data->mlx.mlx_handle->height / 2;
	data->floor.halve_width = data->mlx.mlx_handle->width / 2;
	data->floor.width4 = data->mlx.mlx_handle->width * 4;
	return (init_textures(data));
}
