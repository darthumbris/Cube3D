/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/21 17:08:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

//temp for now
static bool	init_sprites(t_data *data)
{
	printf("number of sprites: %d\n", data->level.number_of_sprites);
	data->level.number_of_sprites = 4;
	data->sprite = malloc(sizeof(t_sprite) * data->level.number_of_sprites);
	data->sprite[0].map_pos.x = 29 + 5.5; //after setting in the parser make all those places in map 0
	data->sprite[0].map_pos.y = 50.5;
	data->sprite[0].kind = LAMP;
	data->sprite[1].map_pos.x = 29 + 5.5;
	data->sprite[1].map_pos.y = 45.5;
	data->sprite[1].kind = LAMP;
	data->sprite[2].map_pos.x = 29 + 5.5;
	data->sprite[2].map_pos.y = 54.5;
	data->sprite[2].kind = LAMP;
	data->sprite[3].map_pos.x = 29 + 5.5;
	data->sprite[3].map_pos.y = 54.5;
	data->sprite[3].kind = BARREL;
	data->sprite_lst = new_sprite(data->sprite[0]);
	data->sprite_lst = add_sprite(&(data->sprite_lst), data->sprite[1]);
	data->sprite_lst = add_sprite(&(data->sprite_lst), data->sprite[2]);
	data->sprite_lst = add_sprite(&(data->sprite_lst), data->sprite[3]);
	data->spr_cast.sprite_order = malloc(sizeof(int) * data->level.number_of_sprites);
	data->spr_cast.sprite_distance = malloc(sizeof(double) * data->level.number_of_sprites);
	data->spr_cast.zbuffer = malloc(sizeof(double) * SCREEN_WIDTH);
	data->mlx.sprites.texarr[2] = mlx_load_png(data->level.paths.path[SPRITE_0]);
	if (data->mlx.sprites.texarr[2] == NULL)
		return (false);
	data->mlx.sprites.texarr[BARREL] = mlx_load_png(data->level.paths.path[SPRITE_1]);
	if (data->mlx.sprites.texarr[BARREL] == NULL)
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
		{
			printf("ok\n");
		return (false);
		}
	data->cam.pos.x = data->player.pos.x + 0.5;
	data->cam.pos.y = data->player.pos.y + 0.5;
	data->caster.ray_dist = 0;
	return (init_sprites(data));
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
